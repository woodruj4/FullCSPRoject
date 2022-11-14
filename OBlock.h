#pragma once
//Love Sosa
#include <iostream>
#include <vector>
#include "Block.h"
using namespace std;
class OBlock
{
private:
	vector<vector<int>> r0 = {
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	};
public:
	vector<vector<int>> getBlock(int);
};

