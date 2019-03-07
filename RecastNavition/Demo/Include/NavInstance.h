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
	float m_polyPickExt[3];

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

	bool BuildNavMesh(const std::string inPath);
	bool SaveNavMesh(const std::string outPath);


	bool BuildNavMeshAndSave(const std::string inPath, const std::string outPath);
	void Clear();

private:
	// Explicitly disabled copy constructor and copy assignment operator.
	NavInstance(const NavInstance&);
	NavInstance& operator=(const NavInstance&);
};

#endif