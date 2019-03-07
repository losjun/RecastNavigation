#include "NavInstance.h"

NavInstance::NavInstance()
	:geom(NULL)
	,sample(NULL)
	,ctx(BuildContext::GetShareCTX())
{
	
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
	Clear();

	geom = new InputGeom;
	if (!geom->load(ctx, inPath) || geom == NULL)
	{
		if (geom != NULL)
		{
			delete geom;
			geom = NULL;
		}

		ctx->log(RC_LOG_ERROR, "Can not Load Gset File:%s", outPath.c_str());
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