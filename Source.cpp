#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <string>
#include "ZBlock.h"
#include "OBlock.h"
#include "IBlock.h"
#include "JBlock.h"
#include "Block.h"
#include "Field.h"

int nScreenWidth = 80;			// Console Screen Size X (columns)
int nScreenHeight = 30;			// Console Screen Size Y (rows)

int readInput();

int main()
{
	int pos = 0;
	//Additional Setup
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	int x_input;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// Create Screen Buffer
	wchar_t* screen = new wchar_t[rows * columns];
	//wchar_t tempScreen = &screen;
	for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	int x_coord;
	int y_coord;
	int blockNum = 0;
	//Block cBlock;
	//Field gField(cBlock);
	/*
	*	Generate a random block;
	*/
	//Create a block
	Block block;
	//Create the Z-Block
	ZBlock zB;
	OBlock oB;
	JBlock jB;
	IBlock iB;
	//Create block1 outside of class
	
	//Set block1 as the moving block
	srand(time(0));
	//Create a field with the active block;
	Field mField(block);
	int test = 0;
	bool isDone = false;
	//Reset the field
	while (!isDone) {
		//Code for generating block
		//test++;
		blockNum = rand() % 4;
		if (blockNum == 0) {
			block.setBlock(oB.getBlock());
		}
		else if (blockNum == 1) {
			block.setBlock(zB.getBlock(block.getR()));
		}
		else if (blockNum == 2) {
			block.setBlock(iB.getBlock(block.getR()));
		}
		else if (blockNum == 3) {
			block.setBlock(jB.getBlock(block.getR()));
		}
		mField.setBlock(block);
		while (mField.getsFlag() == false) {
			mField.setXState(readInput());
			mField.resetField();
			mField.setCoords();

			/*
			*	Determines if the y-pos is valid
			*	"Returns" a flag
			*/
			mField.checkYPos();
			mField.checkXPos();
			mField.setYPos();
			mField.setXPos();
			/*
			*	This code checks for complete "lines"
			*	Allows for a "Tetris" to occur
			*/
			mField.checkTetris();
			mField.printField();

			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					if (mField.getValue(j, i) == 1) {
						y_coord = mField.getfdY() + i;
						x_coord = mField.getfdX() + j;
						pos = y_coord * columns + x_coord;
						screen[pos] = L'#';
					}
					else if (mField.getValue(j, i) == 2) {
						y_coord = mField.getfdY() + i;
						x_coord = mField.getfdX() + j;
						pos = y_coord * columns + x_coord;
						screen[pos] = L'@';
					}
				}
			}
			wchar_t tempChar;
			string endMsg = "x: ";
			string sScore = to_string(mField.getsFlag());
			for (int i = 0; i < endMsg.size(); i++) {
				tempChar = (wchar_t)endMsg[i];
				screen[i] = tempChar;
			}
			for (int i = 0; i < sScore.size(); i++) {
				tempChar = (wchar_t)sScore[i];
				screen[i + 80] = tempChar;
			}
			WriteConsoleOutputCharacter(hConsole, screen, rows * columns, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(100ms); // Delay a bit
			for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
		}
		//Reset 
		mField.setValue(8, 0, 0);
		mField.resetFlags();
		mField.resetBlock();

		if (mField.getlFlag()) {
			break;
		}
		
	}

	return 0;
}

int readInput() {
	int xt;
	if (GetAsyncKeyState(0x41)) {
		xt = 0;
	}
	else if (GetAsyncKeyState(0x44)) {
		xt = 1; //increment x
	}
	else {
		xt = 2;
	}

	return xt;
}
int readRot() {
	int rot;
	if (GetAsyncKeyState(0x57)) {
		rot = 1;
	}
	else {
		rot = 0;
	}
	return rot;
}

