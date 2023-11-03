#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cstring>
#include<conio.h>
#include "Player.h"
#include "UI.h"
#include <fstream>
using namespace std;

void play();
//int testSelect(int playerNum, int k);
int rollDice(int playerNum);
int useItem(int playerNum, int vod);
void checkRSP(int playerNum, int otherNum);
void miniGame(int playerNum, int typeOfGame);
int RSP(int playerNum);
void shopping(int playerNum);
void checkShop(int playerNum);
void checkTile(int playerNum);
int checkUpDown(int playerNum, int otherNum);
int checkEQ(int playerNum, int otherNum);
bool checkWin(int playerNum);
void readMap();

int select(int playerNum, int k);
int cursorControl(int numberOfIndex);
int updowncursorControl(int min, int max);