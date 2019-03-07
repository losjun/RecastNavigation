#include <iostream>
#include "NavInstance.h"
int main()
{

	NavInstance ins;

	ins.BuildNavMeshAndSave("C:\\Users\\zhangjun1\\Desktop\\test\\1026.gset", "C:\\Users\\zhangjun1\\Desktop\\test\\out\\1026.bin");

	return 0;
}