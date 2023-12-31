#include "UI.h"

void gotoxy(int x, int y)
{
	COORD posXY = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}


void printFrame()
{
	gotoxy(0, 0);
	cout << "┌────────────────────┬────────────────────────┬────────────────────┐\n";
	cout << "│                    │                        │                    │\n";
	cout << "│                    │                        │                    │\n";
	cout << "│                    │                        │                    │\n";
	cout << "│                    │                        │                    │\n";
	cout << "├────────────────────┤                        ├────────────────────┤\n";
	cout << "│                    │                        │                    │\n";
	cout << "│                    │                        │                    │\n";
	cout << "├────────────────────┤                        ├────────────────────┤\n";
	cout << "│                    │                        │                    │\n";
	cout << "│                    │                        │                    │\n";
	cout << "│                    │                        │                    │\n";
	cout << "│                    │                        │                    │\n";
	cout << "└────────────────────┴────────────────────────┴────────────────────┘\n";
}

void printTurn(int turn) {
	gotoxy(0, 14);
	cout << "                                                                   ";
	gotoxy(0, 14);
	cout << "			   남은 턴 : " << turn;
}

void renderCursor()
{
	cout << "◀";
}

void eraseCursor()
{
	cout << "  ";
}

void EraseChoiceScene() {
	for (int i = 1; i < 13; i++) {
		gotoxy(22, i);
		cout << "                       ";
	}

}

void ErasePlayerInfo(int playerNum) {
	int x = 0;
	int y = 0;
	if (playerNum == 0) {
		x = 2;
		y = 1;
	}
	else if (playerNum == 1) {
		x = 48;
		y = 9;
	}
	else if (playerNum == 2) {
		x = 48;
		y = 1;
	}
	else {
		x = 2;
		y = 9;
	}
	for (int i = 0; i < 4; i++) {
		gotoxy(x, y + i);
		cout << "                   ";
	}
}

void ErasePlayersState(vector<Player> player) {
	for (int i = 0; i < player.size(); i++) {
		ErasePlayerInfo(i);
	}
}

void RenderGameStartChoice() {
	gotoxy(30, 5);
	cout << "게임 시작";
	gotoxy(30, 6);
	cout << "게임 종료";
}

void RenderPlayersState(vector<Player> player, int n) {
	for (int i = 0; i < player.size(); i++) {
		RenderPlayerInfo(player[i],n);
	}
}

void RenderPlayerInfo(Player p,int n) {
	int x = 0;
	int y = 0;
	int num = p.getNum();
	string dice;
	if (num == 0) {
		x = 2;
		y = 1;
	}
	else if (num == 1) {
		x = 48;
		y = 9;
	}
	else if (num == 2) {
		x = 48;
		y = 1;
	}
	else {
		x = 2;
		y = 9;
	}

	if (p.getDice() == 0) {
		dice = "일반";
	}
	else if (p.getDice() == 1) {
		dice = "안전";
	}
	else {
		dice = "고수";
	}
	gotoxy(x, y);
	cout << "Player" << num + 1;
	gotoxy(x, y + 1);
	cout << "Coin : " << p.getCoin();
	gotoxy(x, y + 2);
	cout << "now : " << p.getNowPosition() + 1;
	gotoxy(x, y + 3);
	cout << "to Goal : " << n - (p.getNowPosition() + 1);
}

void RenderPlayerNumChoice(int x) {
	RenderChoiceNum(x);
}

void RenderDiceChoice() {
	gotoxy(26, 5);
	cout << "1. 일반 주사위";
	gotoxy(26, 6);
	cout << "2. 안전 주사위";
	gotoxy(26, 7);
	cout << "3. 고수 주사위";
}

void RenderDiceItemChoice() {
	gotoxy(28, 5);
	cout << "주사위 사용";
	gotoxy(28, 6);
	cout << "아이템 사용";
}

void RenderUseItemChoice(Player player) {
	string itemNo1; string itemNo2;

	if (player.getItem(0) == 0) itemNo1 = "비어있음";
	else if (player.getItem(0) == 1) itemNo1 = "가보자";
	else if (player.getItem(0) == 2) itemNo1 = "꼼짝마";
	else if (player.getItem(0) == 3) itemNo1 = "주사위주사위";

	if (player.getItem(1) == 0) itemNo2 = "비어있음";
	else if (player.getItem(1) == 1) itemNo2 = "가보자";
	else if (player.getItem(1) == 2) itemNo2 = "꼼짝마";
	else if (player.getItem(1) == 3) itemNo2 = "주사위주사위";
	gotoxy(26, 5);
	cout << "1. " << itemNo1;
	gotoxy(26, 6);
	cout << "2. " << itemNo2;
	gotoxy(26, 7);
	cout << "3. 나가기";
}

void RenderBuyItemChoice() {
	gotoxy(23, 5);
	cout << "1. 가보자(3C)";
	gotoxy(23, 6);
	cout << "2. 꼼짝마(3C)";
	gotoxy(23, 7);
	cout << "3. 주사위주사위(5C)";
	gotoxy(23, 8);
	cout << "4. 나가기";
}

void RenderMinigamePlayerChoice(int numberOfPlayer, Player player, int check) {
	int p = 5;
	gotoxy(26, 4);
	cout << "플레이어 한명 지정";
	for (int i = 0; i < numberOfPlayer; i++) {
		if (player.getNum()!=i && player.getMinigameDid(i) == 0) {
			gotoxy(28, p);
			cout << i + 1 << "번 플레이어";
			p++;
		}
	}
	if (check != 0) {
		gotoxy(28, p);
		cout << "나  가  기";
	}
}

void RenderRSPChoice() {
	gotoxy(33, 5);
	cout << "가위";
	gotoxy(33, 6);
	cout << "바위";
	gotoxy(33, 7);
	cout << " 보";
}

void RenderUpDownChoice(int x) {
	RenderChoiceNum(x);
}

void RenderEQChoice() {
	gotoxy(33, 5);
	cout << "홀수";
	gotoxy(33, 6);
	cout << "짝수";
}

void RenderChoiceNum(int x) {
	eraseInfoWindow(6);
	gotoxy(33, 5);
	cout << "▲";
	gotoxy(33, 6);
	cout << x;
	gotoxy(33, 7);
	cout << "▼";
}

void RenderChoicePlayerNumTitle()
{
	gotoxy(23, 4);
	cout << "<플레이할 인원 수 선택>";
}

void RenderWhoseTurnTitle(int playerNum)
{
	gotoxy(27, 1);
	cout << "<Player " << playerNum + 1 << " 차례>";
}

void RenderNoLoop() {
	gotoxy(23, 6);
	cout << "무한히 반복되므로";
	gotoxy(23, 7);
	cout << " 이 타일에서 멈춥니다.";
	while (1) {
		int input = 0;
		input = _getch();
		if (input == 13)	break;
	}
	EraseChoiceScene();
}

void RenderAct(int map) {
	//0 앞으로 3칸
	//1 뒤로 3칸
	//2 상점
	//3 가위바위보
	//4 업다운
	//5 홀짝
	//6 코인 얻기
	//7 코인 잃기
	if (map == -1) {
		gotoxy(23, 6);
		cout << "시작칸으로 이동";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
	else if (map == 0) {
		gotoxy(23, 6);
		cout << "앞으로 이동 타일 도착";
		gotoxy(30, 7);
		cout << "3칸 전진 !";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
	else if (map == 1) {
		gotoxy(23, 6);
		cout << "뒤로 이동 타일 도착";
		gotoxy(30, 7);
		cout << "3칸 후진 !";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}

	else if (map == 2) {
		gotoxy(26, 5);
		cout << "상점 타일 출현";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
	else if (map == 3) {
		gotoxy(23, 6);
		cout << "미니게임 타일 도착";
		gotoxy(26, 7);
		cout << "가위바위보 시작";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
	else if (map == 4) {
		gotoxy(23, 6);
		cout << "미니게임 타일 도착";
		gotoxy(26, 7);
		cout << "업다운 시작";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
	else if (map == 5) {
		gotoxy(23, 6);
		cout << "미니게임 타일 도착";
		gotoxy(26, 7);
		cout << "홀짝 시작";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
	else if (map == 6) {
		gotoxy(26, 6);
		cout << "파란 타일 도착";
		gotoxy(28, 7);
		cout << "코인 3 획득!";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
	else if (map == 7) {
		gotoxy(26, 6);
		cout << "빨간 타일 도착";
		gotoxy(28, 7);
		cout << "코인 3 뺏김!";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
	}
}

void EraseAct(int map) {
	gotoxy(22, 2);
	cout << "                       ";
}

void eraseInfoWindow(int i)
{
	gotoxy(22, i);
	for (int j = 0; j < 24; j++)cout << " ";

}
void printMiniFrame()
{
	gotoxy(21, 2);
	cout << "┌─────────────────────────┐";
	gotoxy(21, 3);
	cout << "│                         │";
	gotoxy(21, 4);
	cout << "│                         │";
	gotoxy(21, 5);
	cout << "│                         │";
	gotoxy(21, 6);
	cout << "│                         │";
	gotoxy(21, 7);
	cout << "│                         │";
	gotoxy(21, 8);
	cout << "│                         │";
	gotoxy(21, 9);
	cout << "└─────────────────────────┘";
}

void printMapChoiceFrame(){
	gotoxy(15, 2);
	cout << "┌───────────────────────────────────┐";
	gotoxy(15, 3);
	cout << "│                                   │";
	gotoxy(15, 4);
	cout << "│                                   │";
	gotoxy(15, 5);
	cout << "│                                   │";
	gotoxy(15, 6);
	cout << "│                                   │";
	gotoxy(15, 7);
	cout << "│                                   │";
	gotoxy(15, 8);
	cout << "│                                   │";
	gotoxy(15, 9);
	cout << "│                                   │";
	gotoxy(15, 10);
	cout << "└───────────────────────────────────┘";
}

void RenderChoiceMap(vector<string> map,int n) {
	eraseInfoWindow(6);
	gotoxy(33, 4);
	cout << "▲";
	gotoxy(33-map[n].size()/2, 6);
	cout << map[n];
	gotoxy(33, 8);
	cout << "▼";
}

void EraseChoiceMap() {
	gotoxy(17, 6);
	cout << "                                  ";
}
/*
커서컨트롤 사촌(int max, int min){
	int n = (max+min)/2;
	while(엔터 입력시까지만){
		렌더 초이스 넘
		이프 위키 누르면 n++고 이프 max를 넘어가면 min으로
		이프 아래키 누르면 n-- 인데 이프min 아래로 넘어가면 max로
	}
}
*/