#pragma once
class Player
{
private:
	int num;
	int coin;
	int nowPosition;
	int dice;
	int item[2];
	int itemEffect;
	int shopCnt;
	int minigameDid[4] = {0,};


public:
	Player(int x);
	int getNum();
	void setCoin(int x);
	int getCoin();
	void setNowPosition(int x);
	int getNowPosition();
	void setDice(int x);
	int getDice();
	void setItemEffect(int x);
	void resetItemEffect();
	int getItemEffect();
	int isItemEmpty();
	int getItem(int n);
	void setItem(int n, int x);
	int getshopCnt();
	void setshopCnt();
	void setMinigameDid(int n);
	int getMinigameDid(int n);
	void resetMinigameDid();
};
