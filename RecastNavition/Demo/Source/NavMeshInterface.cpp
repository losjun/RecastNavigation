//#include "NavMeshInterface.h"
//#include "MyTempObstacles.h"
//
//#include <map>
//#include <climits>
//#include <stdexcept>
//#include <cassert>
//
//using namespace std;
//
//static map<int, MyTempObstacles*> s_instance_map;
//
//#define NV_EXCEPTION_BEGIN try
//
//#if defined(DEBUG)
//
//#define NV_EXCEPTION_END catch (const std::exception& e){ \
//	ConsoleContext::LogErrWithShare(e.what(), \
//		ConsoleContext::ConsoleKey \
//		); \
//	throw; \
//}
//
//#else
//
//#define NV_EXCEPTION_END catch (const std::exception& e){ \
//	ConsoleContext::LogErrWithShare(e.what(), \
//		ConsoleContext::LogFileKey \
//		); \
//	throw; \
//}
//
//#endif
//
///// <summary>
///// 使用Cantor pairing function进行NxN->N的双射
///// </summary>
//static inline int calcInstanceId(int a, int b)
//{
//	return (a + b)*(a + b + 1) / 2 + b;
//}
//
//void LoadNavMesh(int mapid, int threadid, const char* filename)
//{
//	int id = calcInstanceId(mapid, threadid);
//	if (s_instance_map.find(id) == s_instance_map.end())
//	{
//		MyTempObstacles* instance = new MyTempObstacles();
//
//		//std::string path = std::string(filename);
//		//int errorCount = instance->load_gset_tileCache_init_navQuery(path + ".gset", path + ".bin");
//		//if (errorCount == 0)
//		//{
//		//	instance->setAreaMask(USHRT_MAX);
//		//	instance->SetPolyPickExt(1.0f, 4.0f, 1.0f);
//		//	s_instance_map[id] = instance;
//		//}
//	}
//}
//
//
//int BeginNavMesh(int mapid, int threadid)
//{
//	int id = calcInstanceId(mapid, threadid);
//	return id;
//}
//
//void EndNavMesh(int instanceid)
//{
//	//C4100
//}
//
//nvAreaMask SetAreaMask(int instanceid, nvAreaMask mask)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->setAreaMask(mask);
//}
//NV_EXCEPTION_END
//
//int SetStraightPathOptions(int instanceid, int option)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->SetStraightPathOptions(option);
//}
//NV_EXCEPTION_END
//
//void SetPolyPickExt(int instanceid, float x, float y, float z)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->SetPolyPickExt(x, y, z);
//}
//NV_EXCEPTION_END
//
//bool SamplePosition(int instanceid, const float* vec, SamplePosOut* out)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->SamplePosition(vec, out);
//}
//NV_EXCEPTION_END
//
//bool FindStraightPath(int instanceid, const float* startPos, const float* endPos, FindPathOut* ret)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//
//	SamplePosOut startPoly, endPoly;
//	if (instance->SamplePosition(startPos, &startPoly))
//	{
//		instance->SamplePosition(endPos, &endPoly);
//
//		return FindStraightPath_fast(instanceid, startPoly.polyRef, startPos, endPoly.polyRef, endPos, ret);
//	}
//	return false;
//}
//NV_EXCEPTION_END
//
//bool FindStraightPath_fast(int instanceid, nvPolyRef startRef, const float* startPos, nvPolyRef endRef, const float* endPos, FindPathOut* ret)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//
//	return instance->findStraightPath(startRef, startPos, endRef, endPos, ret);
//}
//NV_EXCEPTION_END
//
//bool Raycast(int instanceid, const float* startPos, const float* endPos, RayCastOut* ret)
//NV_EXCEPTION_BEGIN
//{
//#if defined(DEBUG)
//	LogScopeDump scope(*ConsoleContext::GetSharedConsoleContext(ConsoleContext::ConsoleKey));
//#endif
//
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//
//	SamplePosOut startPoly;
//	if (instance->SamplePosition(startPos, &startPoly))
//	{
//		return Raycast_fast(instanceid, startPoly.polyRef, startPos, endPos, ret);
//	}
//	return false;
//}
//NV_EXCEPTION_END
//
//bool Raycast_fast(int instanceid, nvPolyRef startRef, const float* startPos, const float* endPos, RayCastOut* ret)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//
//	return instance->raycast(startRef, startPos, endPos, ret);
//}
//NV_EXCEPTION_END
//
//bool FindDistanceToWall(int instanceid, const float* startPos, float maxRadius, DisToWallOut* ret)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//
//	SamplePosOut startPoly;
//	if (instance->SamplePosition(startPos, &startPoly))
//	{
//		return FindDistanceToWall_fast(instanceid, startPoly.polyRef, startPos, maxRadius, ret);
//	}
//	return false;
//}
//NV_EXCEPTION_END
//
//bool FindDistanceToWall_fast(int instanceid, nvPolyRef startRef, const float* startPos, float maxRadius, DisToWallOut* ret)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//
//	return instance->findDistanceToWall(startRef, startPos, maxRadius, ret);
//}
//NV_EXCEPTION_END
//
//
//void setAgentObstacleAvoidanceParams(int instanceid, int idx, const dtObstacleAvoidanceParams* params)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->setAgentObstacleAvoidanceParams(idx, params);
//}
//NV_EXCEPTION_END
//
//bool getAgentObstacleAvoidanceParams(int instanceid, int idx, dtObstacleAvoidanceParams* params)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->getAgentObstacleAvoidanceParams(idx, params);
//}
//NV_EXCEPTION_END
//
//
//void setAgentQueryFilter(int instanceid, int idx, int flags)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->setAgentQueryFilter(idx, flags);
//}
//NV_EXCEPTION_END
//
//bool getAgentQueryFilter(int instanceid, int idx, int* flags)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->getAgentQueryFilter(idx, flags);
//}
//NV_EXCEPTION_END
//
//void setAgentQueryAreaCost(int instanceid, int idx, unsigned char adx, float cost)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->setAgentQueryAreaCost(idx, adx, cost);
//}
//NV_EXCEPTION_END
//
//bool getAgentQueryAreaCost(int instanceid, int idx, unsigned char adx, float* cost)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->getAgentQueryAreaCost(idx, adx, cost);
//}
//NV_EXCEPTION_END
//
//int addAgent(int instanceid, const float* pos, const dtCrowdAgentParams* params)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->addAgent(pos, params);
//}
//NV_EXCEPTION_END
//
//void removeAgent(int instanceid, int idx)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->removeAgent(idx);
//}
//NV_EXCEPTION_END
//
//bool hasAgentAtIndex(int instanceid, int idx)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->hasAgentAtIndex(idx);
//}
//NV_EXCEPTION_END
//
//int agentCount(int instanceid, bool filterActive)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->agentCount(filterActive);
//}
//NV_EXCEPTION_END
//
//
//void setAgentParams(int instanceid, int idx, const dtCrowdAgentParams* params)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->setAgentParams(idx, params);
//}
//NV_EXCEPTION_END
//
//bool getAgentParams(int instanceid, int idx, dtCrowdAgentParams* params)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->getAgentParams(idx, params);
//}
//NV_EXCEPTION_END
//
//void requestAgentMoveTarget(int instanceid, int idx, const float* pos)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->requestAgentMoveTarget(idx, pos);
//}
//NV_EXCEPTION_END
//
//void requestAgentMoveVelocity(int instanceid, int idx, const float* pos)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->requestAgentMoveVelocity(idx, pos);
//}
//NV_EXCEPTION_END
//
//
//bool getAgentTargetInfo(int instanceid, int idx, AgentTargetOut* ret)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->getAgentTargetInfo(idx, ret);
//}
//NV_EXCEPTION_END
//
//bool getAgentCurrentInfo(int instanceid, int idx, AgentCurrentOut* ret)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	return instance->getAgentCurrentInfo(idx, ret);
//}
//NV_EXCEPTION_END
//
//void handleUpdate(int instanceid, float dt)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->handleUpdate(dt);
//}
//NV_EXCEPTION_END
//
//void LogErrs(int instanceid, const char* str)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->LogErr(str);
//}
//NV_EXCEPTION_END
//
//void LogWarnings(int instanceid, const char* str)
//NV_EXCEPTION_BEGIN
//{
//	TempObsProcess* instance = s_instance_map.at(instanceid);
//	instance->LogWarn(str);
//}
//
//NV_EXCEPTION_END
