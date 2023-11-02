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
void moveToInfoxy();
void RenderPlayerInfo(Player p);
void RenderDiceChoice();
void RenderPlayerNumChoice(int x);
void RenderDiceItemChoice();
void RenderGameStartChoice();
void RenderUseItemChoice(Player player);
void RenderBuyItemChoice();
void RenderMinigamePlayerChoice(int numberOfPlayer, Player player);
void RenderRSPChoice();
void RenderUpDownChoice(int x);
void RenderEQChoice();
void RenderChoiceNum(int x);
void RenderChoicePlayerNumTitle();//<ÇÃ·¹ÀÌÇÒ ÀÎ¿ø¼ö ¼±ÅÃ> 
void RenderWhoseTurnTitle(int playerNum);//<Player 1 Â÷·Ê>
void RenderGetCoinInfo(int playerNum, int coin); // player (playernum) (coin)coin È¹µæ!
void RenderLoseCoinInfo(int playerNum, int coin); // player (playernum) (coin)coin »¯±è!
void RenderGetCoinByMapTitleInfo(int playerNum);//ÆÄ¶ûÅ¸ÀÏ µµÂø 3ÄÚÀÎ È¹µæ
void RenderLoseCoinByMapTitleInfo(int playerNum);//»¡°­Å¸ÀÏ µµÂø 3ÄÚÀÎ »¯±è
void RenderTradeCoinInfo(int win, int lose, int coin);
void EraseChoiceScene();
void RenderPlayersState(vector<Player> player);
void ErasePlayerInfo(int playerNum);
void ErasePlayersState(vector<Player> player);
void RenderAct(int map);
void EraseAct(int map);
void eraseInfoWindow(int i);
void printMiniFrame();