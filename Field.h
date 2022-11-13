#pragma once
#include <iostream>
#include <vector>
#include "Block.h"
using namespace std;
class Field
{
private:
	vector<vector<int>> mField;
	Block tBlock;
	bool vFlag = false;	//Vertical Flag
	bool hFlag = false;	//Horizontal Flag
	bool lFlag = false;	//Lose Flag
	bool sFlag = false;	//Set Flag
	int xState = 0;
	int fdX = 0;
	int fdY = 0;
public:
	Field(Block);

	void setBlock(Block);
	void setValue(int, int, int);
	void setXState(int);
	void setfdX(int val) {
		fdX = val;
	}
	void setfdY(int val) {
		fdY = val;
	}

	void resetField();
	void printField();
	void printBlock();

	void checkYPos();
	void checkXPos();
	void setYPos();
	void setXPos();

	void checkTetris();

	int getValue(int, int);
	int getfdX() { return fdX;  }
	int getfdY() { return fdY;  }
	void setCoords();

	bool getsFlag() { return sFlag; }
	bool getlFlag() { return lFlag; }
	void resetFlags();
	void resetBlock();
};

