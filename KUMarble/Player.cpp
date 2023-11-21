#include "Player.h"



Player::Player(int x)
{
	num = x;
	nowPosition = -1;
	coin = 3;
	shopCnt = 0;
	dice = 0;
	item[0] = 0;
	item[1] = 0;
	itemEffect = 0;
	shopCnt = 0;
	
}

int Player::getNum()
{
	return num;
}

void Player::setCoin(int x)
{
	//if ((coin + x) < 0) {
	//	coin = 0;
	//}
	//else
	coin += x;
}

int Player::getCoin()
{
	return coin;
}

void Player::setNowPosition(int x)
{
	if ((nowPosition + x) < 0) {
		nowPosition = 0;
	}
	else
		nowPosition += x;
}

int Player::getNowPosition()
{
	return nowPosition;
}

void Player::setDice(int x)
{
	dice = x;
}

int Player::getDice()
{
	return dice;
}

void Player::setItemEffect(int x)
{
	itemEffect += x;
}

void Player::resetItemEffect()
{
	itemEffect = 0;
}

int Player::getItemEffect()
{
	return itemEffect;
}

int Player::isItemEmpty()
{
	if (item[0] == 0) return 0;
	if (item[1] == 0) return 1;
	return -1; //²Ë Âü
}

int Player::getItem(int n)
{
	return item[n];
}

void Player::setItem(int n, int x)
{
	item[n] = x;
}

int Player::getshopCnt()
{
	return shopCnt;
}

void Player::setshopCnt()
{
	shopCnt++;
}

void Player::setMinigameDid(int n)
{
	minigameDid[n] = 1;
}

int Player::getMinigameDid(int n)
{
	return minigameDid[n];
}

void Player::resetMinigameDid()
{
	for (int i = 0; i < 4; i++) {
		minigameDid[i] = 0;
	}
}
