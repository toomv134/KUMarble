#pragma once
#include "Player.h"
#include<iostream>
#include<Windows.h>
#include<vector>

using namespace std;

void gotoxy(int x, int y);
void printFrame();
void renderCursor();
void eraseCursor();
void RenderPlayerInfo(Player p,int n);
void RenderDiceChoice();
void RenderPlayerNumChoice(int x);
void RenderDiceItemChoice();
void RenderGameStartChoice();
void RenderUseItemChoice(Player player);
void RenderBuyItemChoice();
void RenderMinigamePlayerChoice(int numberOfPlayer, Player player, int check);
void RenderRSPChoice();
void RenderUpDownChoice(int x);
void RenderEQChoice();
void RenderChoiceNum(int x);
void RenderChoicePlayerNumTitle();//<플레이할 인원수 선택> 
void RenderWhoseTurnTitle(int playerNum);//<Player 1 차례>
void EraseChoiceScene();
void RenderPlayersState(vector<Player> player,int n);
void ErasePlayerInfo(int playerNum);
void ErasePlayersState(vector<Player> player);
void RenderAct(int map);
void EraseAct(int map);
void eraseInfoWindow(int i);
void printMiniFrame();
void printMapChoiceFrame();
void EraseChoiceMap();
void RenderChoiceMap(vector<string> map, int n);
