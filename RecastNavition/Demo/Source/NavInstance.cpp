#include "NavInstance.h"
#include "DetourCommon.h"
NavInstance::NavInstance()
	:geom(NULL)
	,sample(NULL)
	,ctx(BuildContext::GetShareCTX())
{
	m_filter.setIncludeFlags((nvAreaIndex)0xffff);
	m_filter.setExcludeFlags(0);
}

NavInstance::~NavInstance()
{
	Clear();
}

void NavInstance::Clear()
{
	if (sample != NULL)
	{
		delete sample;
		sample = NULL;
	}

	if (geom != NULL)
	{
		delete geom;
		geom = NULL;
	}

}

bool NavInstance::SaveNavMesh(const std::string outPath)
{
	if (sample && !outPath.empty()) {
		//TODO save exception
		sample->saveAll(outPath.c_str());
		return true;
	}
	else {
		ctx->log(RC_LOG_ERROR, "Save tilecache Failed! Sample is Null. Or tileCacheFileName is Empty.");
		return false;
	}
}

bool NavInstance::BuildNavMeshAndSave(const std::string inPath, const std::string outPath)
{
	bool buildSuccess = BuildNavMesh(inPath);
	if (buildSuccess)
	{
		return SaveNavMesh(outPath);
	}
	return false;
}

bool NavInstance::BuildNavMesh(const std::string inPath)
{
	//TODO
	Clear();

	geom = new InputGeom;
	if (!geom->load(ctx, inPath) || geom == NULL)
	{
		if (geom != NULL)
		{
			delete geom;
			geom = NULL;
		}

		ctx->log(RC_LOG_ERROR, "Can not Load Gset File:%s", inPath.c_str());
		return false;
	}

	sample = new MyTempObstacles();
	sample->setContext(ctx);

	//tool == null TODO
	sample->handleMeshChanged(geom);

#ifdef _DEBUG 
	const float* bmin = 0;
	const float* bmax = 0;
	bmin = geom->getNavMeshBoundsMin();
	bmax = geom->getNavMeshBoundsMax();

	ctx->log(RC_LOG_PROGRESS, "Verts: %.1fk  Tris: %.1fk",
		geom->getMesh()->getVertCount() / 1000.0f,
		geom->getMesh()->getTriCount() / 1000.0f);
#endif

	//build
	sample->handleSettings();

	if (sample->handleBuild())
	{
#ifdef _DEBUG 
		ctx->log(RC_LOG_PROGRESS, "Build Success: %s", m_gsetName.c_str());
#endif
	}
	else {
#ifdef _DEBUG 
		ctx->log(RC_LOG_ERROR, "HandleBuild Failed!");
#endif
	}

	return true;
}

bool NavInstance::LoadNavMesh(const std::string inPath)
{
	//TODO
	Clear();
	sample = new MyTempObstacles();
	sample->setContext(ctx);

	return sample->loadAll(inPath.c_str());
}

bool NavInstance::SamplePosition(const float* vec, SamplePosOut* out, nvAreaIndex area, const float* halfExtents)
{
	dtPolyRef ref;
	m_filter.setIncludeFlags(area);
	dtStatus status = sample->getNavMeshQuery()->findNearestPoly(vec, halfExtents == NULL ? m_halfExtents : halfExtents, &m_filter, &ref, out->pos);
	if (status == DT_SUCCESS)
	{
		if (ref != 0)
		{
			out->hit = true;
			if (sample->getNavMesh()->getPolyArea(ref, &out->area) == DT_SUCCESS)
				out->polyRef = ref;
			else
				out->polyRef = 0;
		}
		else {
			out->hit = false;
#if _DEBUG
			ctx->log(rcLogCategory::RC_LOG_WARNING, "SamplePosition->findNearestPoly->nearestRef is 0");
#endif
		}
	}
	else
	{
		out->hit = false;
#if _DEBUG
		ctx->log(rcLogCategory::RC_LOG_WARNING, "SamplePosition->findNearestPoly->return is not DT_SUCCESS.");
#endif
	}
	return out->hit;
}

bool NavInstance::FindStraightPath(nvPolyRef startRef, const float* startPos, nvPolyRef endRef, const float* endPos, FindPathOut* ret, nvAreaIndex area, const float* halfExtents)
{
	m_filter.setIncludeFlags(area);
	sample->getNavMeshQuery()->findPath(startRef, endRef, startPos, endPos, &m_filter, m_polys, &m_npolys, MAX_POLYS);
	m_nstraightPath = 0;
	if (m_npolys)
	{
		// In case of partial path, make sure the end point is clamped to the last polygon.
		float epos[3];
		dtVcopy(epos, endPos);
		if (m_polys[m_npolys - 1] != endRef) {
			ret->status = PathStatus::PathPartial;
			sample->getNavMeshQuery()->closestPointOnPoly(m_polys[m_npolys - 1], endPos, epos, 0);
		}
		else
		{
			ret->status = PathStatus::PathComplete;
		}

		dtStatus status = sample->getNavMeshQuery()->findStraightPath(startPos, epos, m_polys, m_npolys,
			m_straightPath, m_straightPathFlags,
			m_straightPathPolys, &m_nstraightPath, MAX_POLYS, m_straightPathOptions);
		if (status == DT_SUCCESS)
		{
			ret->npos = m_nstraightPath;
			ret->path = m_straightPath;
		}
		else
		{
			ret->status = PathStatus::PathInvalid;
			ret->npos = 0;
		}
	}
	return ret->status != PathStatus::PathInvalid;
}

bool NavInstance::Raycast(nvPolyRef startRef, const float* startPos, const float* endPos, RayCastOut* ret, nvAreaIndex area, const float* halfExtents)
{
	float t = 0;
	m_npolys = 0;
	m_filter.setIncludeFlags(area);
	dtStatus status = sample->getNavMeshQuery()->raycast(startRef, startPos, endPos, &m_filter, &t, ret->normal, m_polys, &m_npolys, MAX_POLYS);
	if (status == DT_SUCCESS)
	{
		if (t > 1)
		{
			// No hit
			dtVcopy(ret->pos, endPos);
			ret->hit = false;
		}
		else
		{
			// Hit
			dtVlerp(ret->pos, startPos, endPos, t);
			ret->hit = true;
		}
		// Adjust height.
		if (m_npolys > 0)
		{
			float h = 0;
			sample->getNavMeshQuery()->getPolyHeight(m_polys[m_npolys - 1], ret->pos, &h);
			ret->pos[1] = h;

			ret->polyRef = m_polys[m_npolys - 1];

			nvAreaIndex area;
			if (sample->getNavMesh()->getPolyArea(ret->polyRef, &area) == DT_SUCCESS)
			{
				ret->area = area;
			}
			else
			{
				ret->area = 0;
			}
		}
	}
	else
	{
		dtVcopy(ret->pos, endPos);
		ret->hit = false;
		ret->polyRef = 0;
		ret->area = 0;
#if _DEBUG
		ctx->log(rcLogCategory::RC_LOG_WARNING, "raycast->raycast->return is not DT_SUCCESS.");
#endif
	}

	return ret->hit;
}

bool NavInstance::FindDistanceToWall(nvPolyRef startRef, const float* startPos, float maxRadius, DisToWallOut* ret, nvAreaIndex area, const float* halfExtents)
{
	float distance = 0.0f;
	m_filter.setIncludeFlags(area);
	dtStatus status = sample->getNavMeshQuery()->findDistanceToWall(startRef, startPos, maxRadius, &m_filter, &distance, ret->pos, ret->normal);
	if (status == DT_SUCCESS)
	{
		ret->hit = distance > 0.0f && distance <= maxRadius;
		ret->distance = distance;
	}
	else {
		ret->hit = false;
		ret->distance = maxRadius;
	}
	return ret->hit;
}
