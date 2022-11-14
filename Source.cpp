/*
*	Code for creating a console buffer sourced from:
*	https://github.com/OneLoneCoder/Javidx9/blob/master/SimplyCode/OneLoneCoder_Tetris.cpp
*/
#include <iostream>
#include <thread>
#include <vector>
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
#include <fstream>
using namespace std;

int readInput();
int readRot();
vector<vector<int>> getRotateBlock(int blockNum, Block b, OBlock oB, ZBlock zB, IBlock iB, JBlock jB);
int main()
{
	int pos = 0;
	int highscore;
	//Additional Setup
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// Code for creating console buffer
	wchar_t* screen = new wchar_t[rows * columns];
	for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;


	ifstream fin("highscore.txt");
	fin >> highscore;
	fin.close();
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
	wchar_t tempChar;
	//Set block1 as the moving block
	srand(time(0));
	//Create a field with the active block;
	Field mField(block);
	string msg;
	int test = 0;
	bool isDone = false;
	bool startGame = false;
	bool endGame = false;
	//Reset the field
	while (!isDone) {
		ifstream fin("highscore.txt");
		fin >> highscore;
		fin.close();
		while (!startGame) {
			if (GetAsyncKeyState(VK_SPACE)) {
				startGame = true;
			}
			msg = "Falling Geometric Block Game";
			for (int i = 0; i < msg.size(); i++) {
				tempChar = (wchar_t)msg[i];
				screen[i + 80 + 10] = tempChar;
			}
			msg = "Press Space to Start Game";
			for (int i = 0; i < msg.size(); i++) {
				tempChar = (wchar_t)msg[i];
				screen[i + 80 * 2 + 10] = tempChar;
			}

			WriteConsoleOutputCharacter(hConsole, screen, rows * columns, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(100ms); // Delay a bit
			for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
		}

		blockNum = rand() % 4;
		blockNum = 2;
		if (blockNum == 0) {
			block.setBlock(oB.getBlock(block.getR()));
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
			int test = readRot();
			mField.setRState(test);
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
			mField.setRot(getRotateBlock(blockNum, mField.getBlock(), oB, zB, iB, jB));
			/*
			*	This code checks for complete "lines"
			*	Allows for a "Tetris" to occur
			*/
			mField.checkTetris();

			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 20; j++) {
					if (mField.getValue(j, i) == 1) {
						y_coord = mField.getfdY() + i;
						x_coord = mField.getfdX() + j;
						pos = y_coord * columns + x_coord;
						try {
							if (pos >= rows * columns) {
								throw(pos);
							}
						}
						catch (int val) {
							cout << "Error: " << val << "Screen position out of range" << endl;
							pos = 0;
						}

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
			int val;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < 4; j++) {
					if (j == 0) {
						val = i + 160;
					}
					else if (j == 1) {
						val = i + (80 * 22);
					}
					else if (j == 2) {
						val = (i + 2) * 80 + 4;
					}
					else {
						val = (i + 2) * 80 + 16;
					}
					try {
						if (val >= rows * columns) {
							throw(val);
						}
					}
					catch (int val) {
						cout << "Error: " << val << "Screen position out of range" << endl;
						val = 0;
					}
					if (screen[val] != L'*') {
						screen[val] = L'*';
					}
				}
			}


			string endMsg = "Your Score: ";
			string sScore = to_string(mField.getScore());
			for (int i = 0; i < endMsg.size(); i++) {
				tempChar = (wchar_t)endMsg[i];
				screen[i] = tempChar;
			}
			for (int i = 0; i < sScore.size(); i++) {
				tempChar = (wchar_t)sScore[i];
				screen[i + 20] = tempChar;
			}
			endMsg = "High Score: ";
			sScore = to_string(highscore);
			for (int i = 0; i < endMsg.size(); i++) {
				tempChar = (wchar_t)endMsg[i];
				screen[i + 80] = tempChar;
			}
			for (int i = 0; i < sScore.size(); i++) {
				tempChar = (wchar_t)sScore[i];
				screen[i + 80 + 20] = tempChar;
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
			for (int i = 0; i < rows * columns; i++) screen[i] = L' ';
			if (mField.getScore() > highscore) {
				ofstream fout("highscore.txt");
				fout << mField.getScore() << endl;
				fout.close();
			}
			endGame = false;
			msg = "Game Over";
			for (int i = 0; i < msg.size(); i++) {
				tempChar = (wchar_t)msg[i];
				screen[i + 80] = tempChar;
			}
			msg = "Score: ";
			string sScore = to_string(mField.getScore());
			for (int i = 0; i < msg.size(); i++) {
				tempChar = (wchar_t)msg[i];
				screen[i + 160] = tempChar;
			}
			for (int i = 0; i < sScore.size(); i++) {
				tempChar = (wchar_t)sScore[i];
				screen[i + 160 + 15] = tempChar;
			}
			msg = "High Score: ";
			sScore = to_string(highscore);
			for (int i = 0; i < msg.size(); i++) {
				tempChar = (wchar_t)msg[i];
				screen[i + 240] = tempChar;
			}
			for (int i = 0; i < sScore.size(); i++) {
				tempChar = (wchar_t)sScore[i];
				screen[i + 240 + 15] = tempChar;
			}
			msg = "Press Space to Restart";
			for (int i = 0; i < msg.size(); i++) {
				tempChar = (wchar_t)msg[i];
				screen[i + 80 * 4] = tempChar;
			}
			msg = "Press Escape to Quit";
			for (int i = 0; i < msg.size(); i++) {
				tempChar = (wchar_t)msg[i];
				screen[i + 80 * 5] = tempChar;
			}

			while (!endGame) {
				if (GetAsyncKeyState(VK_SPACE)) {
					endGame = true;
					startGame = false;
					mField.fullReset();
					mField.resetFlags();
				}
				if (GetAsyncKeyState(VK_ESCAPE)) {
					isDone = true;
					endGame = true;
				}

				WriteConsoleOutputCharacter(hConsole, screen, rows * columns, { 0,0 }, &dwBytesWritten);
				this_thread::sleep_for(100ms); // Delay a bit

			}

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
vector<vector<int>> getRotateBlock(int blockNum, Block b, OBlock oB, ZBlock zB, IBlock iB, JBlock jB) {

	if (blockNum == 0) {
		b.setBlock(oB.getBlock(b.getR()+1));
	}
	else if (blockNum == 1) {
		b.setBlock(zB.getBlock(b.getR()+1));
	}
	else if (blockNum == 2) {
		b.setBlock(iB.getBlock(b.getR()+1));
	}
	else if (blockNum == 3) {
		b.setBlock(jB.getBlock(b.getR()+1));
	}

	return b.getBlock();
}



