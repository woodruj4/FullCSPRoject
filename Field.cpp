#include "Field.h"

Field::Field(Block cBlock) {
	mField.resize(20, vector<int>(20, 0)); 
	tBlock = cBlock;
}

int Field::getValue(int x, int y) {
	return mField[y][x];
}

void Field::setValue(int x, int y, int val) {
	mField[y][x] = val;
}

void Field::setBlock(Block cBlock) {
	tBlock = cBlock;
}

void Field::setXState(int xState) {
	this->xState = xState;
}
void Field::setRState(int rState) {
	this->rState = rState;
}

void Field::resetField(){
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (mField[i][j] == 1) {
				mField[i][j] = 0;
			}
		}
	}
}

void Field::fullReset() {
	vFlag = false;	//Vertical Flag
	hFlag = false;	//Horizontal Flag
	lFlag = false;	//Lose Flag
	sFlag = false;	//Set Flag
	xState = 0;
	rState = 0;
	fdX = 0;
	fdY = 2;
	score = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			mField[i][j] = 0;
		}
	}
}

ostream& operator <<(ostream& os, Field f) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			os << f.mField[i][j];
		}
		os << endl;
	}
	return os;
}

void Field::checkYPos() {
	int cX; int cY;
	for (int i = 0; i < 4; i++) {
		cX = tBlock.getCoords(0,i);
		
		cY = tBlock.getCoords(1,i);
		//cout << cX << " " << cY << endl;
		//Error Handling for cY
		if (cY + 1 > 19) {
			vFlag = true;
			break;
		}
		else if (mField[cY + 1][cX] == 2) {
			vFlag = true; //Cannot Move, need to set the block
			if (cY < 4) {
				lFlag = true;
			}
			break;
		}
	}
}

void Field::checkXPos() {
	if (xState == 0) {
		for (int i = 0; i < 4; i++) {
			if (tBlock.getCoords(0,i) - 1 < 5) {
				hFlag = true;
				break;
			}
			else if (mField[tBlock.getCoords(1,i)][tBlock.getCoords(0, i) - 1] == 2) {
				hFlag = true;
				break;
			}
		}
	}
	else if (xState == 1) {
		for (int i = 0; i < 4; i++) {
			if (tBlock.getCoords(0, i) + 1 > 15) {
				hFlag = true;
				break;
			}
			else if (mField[tBlock.getCoords(1, i)][tBlock.getCoords(0, i)+1] == 2) {
				hFlag = true;
				break;
			}
		}
	}
}

void Field::setYPos() {
	if (vFlag) {
		for (int i = 0; i < 4; i++) {
			mField[tBlock.getCoords(1, i)][tBlock.getCoords(0, i)] = 2;
		}
		sFlag = true;
		score += 10;
	}
	//Code for moving the block
	else {
		for (int i = 0; i < 4; i++) {
			mField[tBlock.getCoords(1, i)][tBlock.getCoords(0, i)] = 1;
		}
		//Changes y-coord of the block
		tBlock.setY(tBlock.getY()+1);
	}
}

void Field::setXPos() {
	if (hFlag == false && xState == 0) {
		tBlock.setX(tBlock.getX() - 1);
	}
	else if (hFlag == false && xState == 1) {
		tBlock.setX(tBlock.getX() + 1);
	}
}

void Field::setRot(vector<vector<int>> b) {
	
	if (!hFlag && rState == 1) {
		tBlock.setBlock(b);
		if (tBlock.getR() + 1 > 3) {
			tBlock.setR(0);
		}
		else {
			tBlock.setR(tBlock.getR() + 1);
		}
		
	}
}

void Field::checkTetris() {
	int count = 0;
	bool isComp = false;
	int ind = 0;
	for (int i = 19; i > -1; i--) {
		count = 0;
		for (int j = 5; j < 15; j++) {
			if (mField[i][j] == 2) {
				count++;
				if (count > 9) {
					isComp = true;
				}
			}
		}
		if (isComp == true) {
			for (int j = i; j > 0; j--) {
				for (int k = 0; k < 20; k++) {
					//Set current row equal to previous row
					mField[j][k] = mField[j - 1][k];
				}
			}
			isComp = false;
			score += 100;
		}

	}
}

void Field::setCoords() {
	tBlock.setCoords();
}
void Field::resetFlags() {
	sFlag = false;
	vFlag = false;
	hFlag = false;
}

void Field::resetBlock() {
	tBlock.setX(8);
	tBlock.setY(0);
	tBlock.setR(0);
}