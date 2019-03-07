#ifndef NAVINSTANCE_H
#define NAVINSTANCE_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "MyTempObstacles.h"
#include "InputGeom.h"
#include "InterfaceTypes.h"
#include "DetourNavMeshQuery.h"
#include "DetourCrowd.h"

/*
 * ½Ó¿ÚÀà
 */

class NavInstance
{
private:
	float m_halfExtents[3] = {0.01, 0.01, 0.01};

	static const int MAX_POLYS = 256;
	static const int MAX_SMOOTH = 2048;

	int m_straightPathOptions;
	dtPolyRef m_polys[MAX_POLYS];
	int m_npolys;
	float m_straightPath[MAX_POLYS * 3];
	unsigned char m_straightPathFlags[MAX_POLYS];
	dtPolyRef m_straightPathPolys[MAX_POLYS];
	int m_nstraightPath;

	InputGeom* geom;
	MyTempObstacles* sample;
	BuildContext* ctx;
	dtQueryFilter m_filter; // Only affect navMesh query method

	std::string m_gsetName;
public:
	NavInstance();
	~NavInstance();

	//gset file path
	bool BuildNavMesh(const std::string inPath);
	bool SaveNavMesh(const std::string outPath);

	//gset file path  
	//save path
	bool BuildNavMeshAndSave(const std::string inPath, const std::string outPath);
	//bin file
	bool LoadNavMesh(const std::string inPath);

	bool SamplePosition(const float* vec, SamplePosOut* out, nvAreaIndex area = 1, const float* halfExtents = NULL);

	bool FindStraightPath(nvPolyRef startRef, const float* startPos, nvPolyRef endRef, const float* endPos, FindPathOut* ret, nvAreaIndex area = 1, const float* halfExtents = NULL);

	bool Raycast(nvPolyRef startRef, const float* startPos, const float* endPos, RayCastOut* ret, nvAreaIndex area = 1, const float* halfExtents = NULL);

	bool FindDistanceToWall(nvPolyRef startRef, const float* startPos, float maxRadius, DisToWallOut* ret, nvAreaIndex area = 1, const float* halfExtents = NULL);
private:
	// Explicitly disabled copy constructor and copy assignment operator.
	NavInstance(const NavInstance&);
	NavInstance& operator=(const NavInstance&);

	void Clear();
};

#endif