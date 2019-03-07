#include <iostream>
#include "NavInstance.h"
int main()
{

	NavInstance ins;

	ins.BuildNavMeshAndSave("C:\\Users\\zhangjun1\\Desktop\\test\\1026.gset", "C:\\Users\\zhangjun1\\Desktop\\test\\out\\1026.bin");

	bool m = ins.LoadNavMesh("C:\\Users\\zhangjun1\\Desktop\\test\\out\\1026.bin");
	float startPos[3]{ 0 ,0 , 0 };
	float extent[3]{ 100 ,100 , 100 };
	SamplePosOut endPoly;
	bool n = ins.SamplePosition(startPos, &endPoly, (nvAreaIndex)0xffff);
	int a = 0;
	return 0;
}