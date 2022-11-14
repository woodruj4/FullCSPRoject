#pragma once
#include <iostream>
#include <vector>

using namespace std;
class Block
{
private:
	int x = 8;
	int y = 0;
	int r = 0; //0-3 determines the orientation
	vector<vector<int>> bCoords; //Block Coordinates
	vector<vector<int>> cBlock; //Current Block
public:
	Block();
	~Block() { cout << "Block destroyed" << endl; }

	vector<vector<int>> getBlock() { return cBlock; }
	int getX() { return x; }
	int getY() { return y; }
	int getR() { return r; }
	int getCoords(int r, int c);

	void setBlock(vector<vector<int>>);
	void setX(int val) { x = val; }
	void setY(int val) { y = val; }
	void setR(int val) { r = val; }
	void setCoords();
	
	friend ostream& operator<<(ostream& os, Block b);
};

