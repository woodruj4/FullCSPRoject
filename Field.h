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
	int rState = 0;
	int fdX = 0;
	int fdY = 2;
	int score = 0;
public:
	Field(Block);
	~Field() { cout << "Field Destoryed" << endl; }

	int getScore() { return score; }
	int getValue(int, int);
	Block getBlock() { return tBlock; }
	int getfdX() { return fdX; }
	int getfdY() { return fdY; }
	bool getsFlag() { return sFlag; }
	bool getlFlag() { return lFlag; }
	
	void setBlock(Block);
	void setValue(int, int, int);
	void setlFlag(bool val) { lFlag = val; }
	void setXState(int);
	void setRState(int);
	void setfdX(int val) { fdX = val; }
	void setfdY(int val) { fdY = val; }

	//Reset Functions
	void fullReset();
	void resetField();
	void resetFlags();
	void resetBlock();

	//Debug/Printing functions
	friend ostream& operator<<(ostream& os, Field f);

	//Member functions related to the game
	void checkYPos();
	void checkXPos();
	void setYPos();
	void setXPos();
	void setRot(vector<vector<int>>);
	void setCoords();
	void checkTetris();
	
};

