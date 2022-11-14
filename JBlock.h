#pragma once
#include <iostream>
#include <vector>
#include "Block.h"
using namespace std;
class JBlock: public Block
{
private:
	vector<vector<int>> r0 = {
		{0,0,0,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,1,1,0}
	};
	vector<vector<int>> r1 = {
		{0,0,0,0},
		{1,0,0,0},
		{1,1,1,0},
		{0,0,0,0}
	};
	vector<vector<int>> r2 = {
		{0,1,1,0},
		{0,1,0,0},
		{0,1,0,0},
		{0,0,0,0}
	};
	vector<vector<int>> r3 = {
		{0,0,0,0},
		{0,1,1,1},
		{0,0,0,1},
		{0,0,0,0}
	};
public:
	~JBlock() { cout << "JBlock destroyed" << endl; }
	vector<vector<int>> getBlock(int);
};

