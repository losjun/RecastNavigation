#ifndef INTERFACETYPES_H
#define INTERFACETYPES_H

#include "DetourObstacleAvoidance.h"
#include "DetourCrowd.h"

typedef int nvAreaMask;
typedef unsigned char nvAreaIndex;

#if defined(DT_POLYREF64)
#error "If You must use DT_POLYREF64. Please **change the types of both dtPolyRef & dtTileRef**"
#else

typedef unsigned int nvPolyRef; // the same with dtPolyRef (defined in DetourNavMesh.h)

#endif


struct SamplePosOut
{
	bool hit;
	nvAreaIndex area;
	float pos[3];
	nvPolyRef polyRef;
};

enum PathStatus : int
{
	PathComplete = 0,
	PathPartial,
	PathInvalid
};

struct FindPathOut
{
	PathStatus status;
	const float* path; // size is 3*npos
	int npos;
};

struct RayCastOut
{
	bool hit;
	nvAreaIndex area;
	nvPolyRef polyRef;
	float pos[3];
	float normal[3];
};

struct DisToWallOut
{
	bool hit;
	float distance;
	float pos[3];
	float normal[3];
};

struct AgentTargetOut
{
	unsigned char targetState;			///< State of the movement request.
	nvPolyRef targetRef;				///< Target polyref of the movement request.
	float targetPos[3];					///< Target position of the movement request (or velocity in case of DT_CROWDAGENT_TARGET_VELOCITY).
	const float* straightPath; // cornerVerts[DT_CROWDAGENT_MAX_CORNERS * 3];
	int npos; // ncorners;
};

struct AgentCurrentOut
{
	float pos[3];		///< The current agent position. [(x, y, z)]
	float vel[3];		///< The actual velocity of the agent. The change from nvel -> vel is constrained by max acceleration. [(x, y, z)]
};

#endif