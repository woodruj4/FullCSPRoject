#pragma once
#include <iostream>
#include <vector>
using namespace std;
class ZBlock
{
private:
	vector<vector<int>> r0 = {
		{0,0,0,0},
		{0,1,0,0},
		{0,1,1,0},
		{0,0,1,0}
	};
	vector<vector<int>> r1 = {
		{0,0,0,0},
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0}
	};

public:
	~ZBlock() { cout << "ZBlock destroyed" << endl; }
	vector<vector<int>> getBlock(int);
};

