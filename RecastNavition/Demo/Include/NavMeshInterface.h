//#ifndef NAVMESHINTERFACE_H
//#define NAVMESHINTERFACE_H
//
//#include "InterfaceTypes.h"
//
//
//#if defined(WIN32)
//
//#pragma message("Exporting NavMesh dll...")
//
//#if defined(EXPORT_DLL)
//#ifdef __cplusplus
//#define _NAVMESH_API extern "C" __declspec(dllexport)
//#else
//#define _NAVMESH_API __declspec(dllexport)
//#endif
//#else
//#define _NAVMESH_API
//#endif /*EXPORT_DLL*/
//
//#else /*linux*/
//
//#ifdef __cplusplus
//#define _NAVMESH_API extern "C"
//#else
//#define _NAVMESH_API
//#endif
//
//#endif
//
//_NAVMESH_API void LoadNavMesh(int mapid, int threadid, const char* filename);
//
//_NAVMESH_API int BeginNavMesh(int mapid, int threadid);
//_NAVMESH_API void EndNavMesh(int instanceid);
//
//_NAVMESH_API nvAreaMask SetAreaMask(int instanceid, nvAreaMask mask);
//
//_NAVMESH_API int SetStraightPathOptions(int instanceid, int option);
//
//_NAVMESH_API void SetPolyPickExt(int instanceid, float x, float y, float z);
//
//_NAVMESH_API bool SamplePosition(int instanceid, const float* vec, SamplePosOut* ret);
//
//
//_NAVMESH_API bool FindStraightPath(int instanceid, const float* startPos, const float* endPos, FindPathOut* ret);
//_NAVMESH_API bool FindStraightPath_fast(int instanceid, nvPolyRef startRef, const float* startPos, nvPolyRef endRef, const float* endPos, FindPathOut* ret);
//
//
//_NAVMESH_API bool Raycast(int instanceid, const float* startPos, const float* endPos, RayCastOut* ret);
//_NAVMESH_API bool Raycast_fast(int instanceid, nvPolyRef startRef, const float* startPos, const float* endPos, RayCastOut* ret);
//
//_NAVMESH_API bool FindDistanceToWall(int instanceid, const float* startPos, float maxRadius, DisToWallOut* ret);
//_NAVMESH_API bool FindDistanceToWall_fast(int instanceid, nvPolyRef startRef, const float* startPos, float maxRadius, DisToWallOut* ret);
//
//
//_NAVMESH_API void setAgentObstacleAvoidanceParams(int instanceid, int idx, const dtObstacleAvoidanceParams* params);
//_NAVMESH_API bool getAgentObstacleAvoidanceParams(int instanceid, int idx, dtObstacleAvoidanceParams* params);
//
//_NAVMESH_API void setAgentQueryFilter(int instanceid, int idx, unsigned short flags);
//_NAVMESH_API bool getAgentQueryFilter(int instanceid, int idx, unsigned short* flags);
//
//_NAVMESH_API void setAgentQueryAreaCost(int instanceid, int idx, unsigned char adx, float cost);
//_NAVMESH_API bool getAgentQueryAreaCost(int instanceid, int idx, unsigned char adx, float* cost);
//
//_NAVMESH_API int addAgent(int instanceid, const float* pos, const dtCrowdAgentParams* params);
//_NAVMESH_API void removeAgent(int instanceid, int idx);
//
//_NAVMESH_API bool hasAgentAtIndex(int instanceid, int idx);
//_NAVMESH_API int agentCount(int instanceid, bool filterActive);
//
//_NAVMESH_API void setAgentParams(int instanceid, int idx, const dtCrowdAgentParams* params);
//_NAVMESH_API bool getAgentParams(int instanceid, int idx, dtCrowdAgentParams* params);
//
//_NAVMESH_API void requestAgentMoveTarget(int instanceid, int idx, const float* pos);
//_NAVMESH_API void requestAgentMoveVelocity(int instanceid, int idx, const float* pos);
//
//_NAVMESH_API bool getAgentTargetInfo(int instanceid, int idx, AgentTargetOut* ret);
//_NAVMESH_API bool getAgentCurrentInfo(int instanceid, int idx, AgentCurrentOut* ret);
//
//_NAVMESH_API void handleUpdate(int instanceid, float dt);
//
//_NAVMESH_API void LogErrs(int instanceid, const char* str);
//
//_NAVMESH_API void LogWarnings(int instanceid, const char* str);
//
//#endif