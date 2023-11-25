#include "Play.h"

#define Max 2,147,483,647

vector<Player> player;
//0 앞으로 3칸
//1 뒤로 3칸
//2 상점
//3 가위바위보
//4 업다운
//5 홀짝
//6 코인 얻기
//7 코인 잃기
vector<int> map;
vector<string> mapName;
//int map[27] = {
//	3,7,4,0,3,
//	7,6,0,1,7,
//	2,4,7,1,6,
//	6,5,4,7,0,
//	2,3,5,6,1,
//	6,5
//}; // 파일 입출력으로 수정

int shop[2];
bool somebodywin = false;
int numberOfPlayer;

void play()
{

	while (1) {
		shop[0] = shop[1] = Max;
		somebodywin = false;
		map.clear();
		mapName.clear();
		system("cls");
		printMiniFrame();
		if (select(0, 0) == 2) {//게임 플레이,종료 결정
			return;
		}
		//맵 결정 상점 2개이상이면 컷
		if (ChoiceMap()) {
			printFrame();
			numberOfPlayer = select(0, 1);//플레이어 수 결정

			for (int i = 0; i < numberOfPlayer; i++) {//플레이어 수 만큼 플레이어 생성
				Player p(i);
				player.push_back(p);
			}
			system("cls");
			printFrame();
			RenderPlayersState(player,map.size()); //플레이어들 정보 갱신 
			for (int i = 0; i < numberOfPlayer; i++) { // 각 플레이어들 주사위 선택
				player[i].setDice(select(i, 2) - 1);
			}

			//초반 세팅
			//RenderPlayersState(player);

			// 게임 시작

			while (!somebodywin) { //누군가 이길때까지
				int vod = 0; //value of dice
				//게임씬나오고
				// 얘네 플레이 하는 명수에 따라 포문 설정해주기
				for (int i = 0; i < numberOfPlayer; i++) {
					RenderPlayersState(player, map.size()); //플레이어들 정보 갱신 
					int ifUseItem = select(i, 3);
					//누구누구차례 y=1 erase, render
					//지금 뭐하는지 y=2 erase,render 
					if (ifUseItem == 2) {//아이템 선택 //지금 뭐하는지 y=2 erase, render
						player[i].setItemEffect(useItem(i, select(i, 4))); //아이템 이펙트 바뀜 select4 return 0 : 나가기,아이템 없음  1 : 주사위주사위 3 : 가보자

					}
					vod = rollDice(i);
					gotoxy(31, 8);
					//지금 뭐하는지 y=2 주사위 굴리는중 erase, render
					cout << "Dice : " << vod << endl;
					while (1) {
						int input = 0;
						input = _getch();
						if (input == 13)	break;
					}
					//Sleep(1000);
					eraseInfoWindow(8);
					if (player[i].getItemEffect() != 0) {
						gotoxy(26, 9);
						cout << "아이템 효과 : " << player[i].getItemEffect();
						vod += player[i].getItemEffect();
						player[i].resetItemEffect();
					}

					player[i].setNowPosition(vod);// 이동
					ErasePlayersState(player);
					RenderPlayersState(player, map.size()); //이동하고 정보 갱신 

					checkTile(i);
					// y=2 가위바위보, 코인 얻음, 코인 잃음,  홀짝, 업다운 , 상 점  erase, render
					//Sleep(1000);
					while (1) {
						int input = 0;
						input = _getch();
						if (input == 13)	break;
					}

					EraseChoiceScene();
					checkShop(i);

					ErasePlayersState(player);
					EraseChoiceScene();
					if (checkWin(i)) {
						//gotoxy(26, 6);
						//cout << "Player" << i + 1 << "승리";
						//Sleep(1000);
						break; //마지막 타일 도착했는지 판별하고 다음 사람
					}
				}

			}
			//cout<<"game over \n";
			for (int i = 0; i < numberOfPlayer; i++) {//플레이어 수 만큼 플레이어 생성
				Player p(i);
				player.pop_back();
			}
		}
	}

}

bool checkWin(int playerNum) {

	if (player[playerNum].getNowPosition() >= map.size()) {
		system("cls");
		gotoxy(26, 6);
		cout<<"player "<<playerNum + 1<<" Win!! \n";
//		Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		somebodywin = true;
		return true;
	}
	if (map.size() > 50){
		if (player[playerNum].getNowPosition() >= map.size() * 0.6) {
			system("cls");
			gotoxy(26, 6);
			cout << "plaer " << checkwhowin() << "win!!";
			//Sleep(1000);
			while (1) {
				int input = 0;
				input = _getch();
				if (input == 13)	break;
			}
			somebodywin = true;
			return true;
		}
	}
	return false;
}

int select(int playerNum, int k)
{
	if (k == 0) { //0: 게임 시작 return 1:게임 시작 2:게임 종료  
		RenderGameStartChoice();
		return cursorControl(2);
	}
	else if (k == 1) { //1: 플레이어 수 정하기 return : 2,3,4 
		RenderChoicePlayerNumTitle();
		return updowncursorControl(2, 4);
	}
	else if (k == 2) { //2: 주사위 종류 정하기 return 1:일반 2:안전 3: 고수 
		RenderWhoseTurnTitle(playerNum);
		RenderDiceChoice();
		return cursorControl(3);
	}
	else if (k == 3) { //3: 주사위,아이템 결정 return 1:아이템 사용 2:주사위 사용 
		RenderWhoseTurnTitle(playerNum);
		RenderDiceItemChoice();
		return cursorControl(2);
	}
	else if (k == 4) { //4: 무슨 아이템쓸건지 0, 1 return 0 : 나가기,아이템 없음  1 : 주사위주사위 3 : 가보자  
		//가지고 있는 아이템 보여주기
		RenderWhoseTurnTitle(playerNum);
		RenderUseItemChoice(player[playerNum]);
		int n = cursorControl(3);
		if (n == 3) {
			return 0;
		}
		else {
			if (player[playerNum].getItem(n - 1) == 1) { //0 없음 1가보자 2 꼼짝마 3 주주 getItem(int x) x->몇번째 아이템
				player[playerNum].setItem(n-1,0);
				return 3;
			}
			else if (player[playerNum].getItem(n - 1) == 2) { //꼼짝마
				//pnum = 몇번째 플레이어에게 꼼짝마를 먹일건지 
				player[playerNum].setItem(n - 1, 0);
				return select(select(playerNum, 6), 10);
			}
			else if (player[playerNum].getItem(n - 1) == 3) {//주주
				player[playerNum].setItem(n - 1, 0);
				return 1;
			}
			else { //없음
				return 0;
			}
		}
	}
	else if (k == 5) { //5: 상점에서 무슨 아이템 구매할건지 return 1: 가보자 2: 꼼짝마 3: 주사위주사위 4: 나가 기  
		RenderBuyItemChoice();
		return cursorControl(4);
	}
	else if (k == 6) { //6: 어느 플레이어와 게임할지 return : 상대방의 번호(벡터상의번호) 
		// 리턴이 -1이면 나가기 한것
		int check = 0;//한명이라도 선택했으면 1, 처음선택이면 0
		for (int i = 0; i < numberOfPlayer; i++) {
			if (player[playerNum].getMinigameDid(i) == 1) check++;
		}

		RenderMinigamePlayerChoice(numberOfPlayer, player[playerNum], check);
		
		int howManyChoose = numberOfPlayer - check;
		if (check == 0)howManyChoose = numberOfPlayer - 1;

		if (numberOfPlayer - check == 1)return -1;
		int n = cursorControl(howManyChoose);
		if (numberOfPlayer == 2) {
			if (playerNum == 0)	return 1;
			else return 0;
		}
		else {
			if (check != 0 && n == howManyChoose) return -1;
			int temp = 1;
			for (int i = 0; i < numberOfPlayer; i++) {
				if (i!=playerNum && player[playerNum].getMinigameDid(i) == 0) {
					if (temp == n) {
						return i;
					}
					temp++;
				}
			}
		}


	}
	else if (k == 7) { //7: 가위바위보 정하기	return 1:가위 2:바위 3: 보  
		RenderRSPChoice();
		return cursorControl(3);
	}
	else if (k == 8) { //8: 업다운 정하기 return 1~10
		return updowncursorControl(1, 10);
	}
	else if (k == 9) { //9: 홀짝 정하기 return 1:홀 2:짝 
		RenderEQChoice();
		return cursorControl(2);
	}
	else if (k == 10) { //10: 꼼짝마 상대 정하기 return  
		//RenderMinigamePlayerChoice(numberOfPlayer, player[playerNum]);
		player[playerNum].setItemEffect(-3);
		return 0;
	}
}

int cursorControl(int numberOfIndex) //선택지 개 수  
{
	int nowpos = 1;
	int min = 1;
	int input = 0;
	int py = 5;
	int ny = 5;
	gotoxy(42, ny);
	renderCursor();
	while (input != 13) {
		input = _getch();
		if (input == 224) {
			input = _getch();
			if (input == 72) {
				if (nowpos != min) {
					nowpos--;
					py = ny;
					ny--;
				}
				else {
					nowpos = numberOfIndex;
					py = ny;
					ny = 4 + numberOfIndex;
				}
			}
			else if (input == 80) {
				if (nowpos != numberOfIndex) {
					nowpos++;
					py = ny;
					ny++;
				}
				else {
					nowpos = min;
					py = ny;
					ny = 5;
				}
			}
		}
		gotoxy(42, py);
		eraseCursor();
		gotoxy(42, ny);
		renderCursor();
	}
	EraseChoiceScene();
	return nowpos;
}

int updowncursorControl(int min, int max) {
	int n = (min + max) / 2;
	gotoxy(26, 6);
	RenderChoiceNum(n);
	int input = 0;
	while (input != 13) {
		input = _getch();
		if (input == 224) {
			input = _getch();
			if (input == 72) {
				if (n != max) {
					n++;
				}
				else {
					n = min;
				}
			}
			else if (input == 80) {
				if (n != min) {
					n--;
				}
				else {
					n = max;
				}
			}
		}
		gotoxy(26, 6);
		eraseCursor();
		RenderChoiceNum(n);
	}
	EraseChoiceScene();
	return n;
}

void checkTile(int playerNum) {
	//cout<<"position: "<<player[playerNum].getNowPosition()<<"\n";
	int pos = player[playerNum].getNowPosition();
	if (pos >= 26)return;
	EraseChoiceScene();
	gotoxy(28, 4);
	cout << "Player" << playerNum + 1;
	if (map[pos] == 0) { //앞으로 3칸
		RenderAct(map[pos]);
		player[playerNum].setNowPosition(3);
		checkTile(playerNum);
	}
	else if (map[pos] == 1) { //뒤로 3칸
		RenderAct(map[pos]);
		player[playerNum].setNowPosition(-3);
		checkTile(playerNum);
	}
	else if (map[pos] == 2) { //상점
		RenderAct(map[pos]);
		shopping(playerNum);
	}
	else if (map[pos] == 6) {
		RenderAct(map[pos]);
		player[playerNum].setCoin(3);
	}
	else if (map[pos] == 7) {
		RenderAct(map[pos]);
		player[playerNum].setCoin(-3);
	}
	else {
		miniGame(playerNum, map[pos]);
	}
}

void checkShop(int playerNum) {
	if (player[playerNum].getNowPosition() >= 26)return;
	if (player[playerNum].getNowPosition() > shop[0] && player[playerNum].getshopCnt() == 0) {
		shopping(playerNum);
	}
	else if (player[playerNum].getNowPosition() > shop[1] && player[playerNum].getshopCnt() == 1) {
		shopping(playerNum);
	}
	else if (player[playerNum].getNowPosition() > shop[1] && player[playerNum].getshopCnt() == 0) {
		shopping(playerNum);
		shopping(playerNum);
	}
}

void shopping(int playerNum) {
	EraseChoiceScene();
	//cout<<"shopping \n";
	player[playerNum].setshopCnt();
	//1. 가보자 (3) 2. 꼼짝마 (3) 3. 주주 (5) 4. 나가기
	int selectnum = select(playerNum, 5); //select에서 무슨아이템 살건지 번호 return
	if ((selectnum == 1 || selectnum == 2) && player[playerNum].getCoin() >= 3 && player[playerNum].isItemEmpty() != -1) {
		player[playerNum].setCoin(-3);
		player[playerNum].setItem(player[playerNum].isItemEmpty(), selectnum);
		gotoxy(28, 8);
		cout<< " 구매완료 \n";
	}
	else if (selectnum == 3 && player[playerNum].getCoin() >= 5 && player[playerNum].isItemEmpty() != -1) {
		player[playerNum].setCoin(-5);
		player[playerNum].setItem(player[playerNum].isItemEmpty(), selectnum);
		gotoxy(28, 8);
		cout << "구매완료 \n";
	}
	else {
		return;
	}
}

void miniGame(int playerNum, int typeOfGame) {// 리턴값이 이긴사람 playerNum
	EraseChoiceScene();
	
	int check = 0;//한명이라도 선택했으면 1, 처음선택이면 0
	for (int i = 0; i < numberOfPlayer; i++) {
		if (player[playerNum].getMinigameDid(i) == 1) check++;
	}
	int howManyChoose = numberOfPlayer - check;
	if (check == 0)howManyChoose = numberOfPlayer - 1;
	if (numberOfPlayer - check == 1)return;

	
	int n;
	if (typeOfGame == 3) { //가위바위보	
		RenderAct(typeOfGame);

		n = select(playerNum, 6);
		player[playerNum].setMinigameDid(n);

		if (n == -1) {
			player[playerNum].resetMinigameDid();
			return;
		}
		//TODO
		EraseChoiceScene();
		checkRSP(playerNum, n);
		
		miniGame(playerNum, 3);

		//if (winner == n) { //졌음
		//	EraseChoiceScene();
		//	gotoxy(28, 6);
		//	cout << "player" << n + 1 << " 승리";
		//	gotoxy(23, 7);
		//	cout << "Player" << winner + 1 << " " <<"5 코인 획득! ";
		//	gotoxy(23, 8);
		//	cout << "Player" << playerNum + 1 << " " << "5 코인 압수 ! ";
		//	Sleep(1000);
		//	player[winner].setCoin(5);
		//	player[playerNum].setCoin(-5);
		//}
		//else if (winner == playerNum) { //이겼음
		//	EraseChoiceScene();
		//	gotoxy(28, 6);
		//	cout << "player" << n + 1 << " 승리";
		//	gotoxy(23, 7);
		//	cout << "Player" << winner + 1 << " " << "5 코인 획득! ";
		//	gotoxy(23, 8);
		//	cout << "Player" << n + 1 << " " << "5 코인 압수 ! ";
		//	Sleep(1000);
		//	player[winner].setCoin(5);
		//	player[n].setCoin(-5);
		//}
		//else { //비겼음
		//	EraseChoiceScene();
		//	gotoxy(28, 6);
		//	cout << "비겼습니다" << endl;
		//	Sleep(1000);
		//}
	}
	else if (typeOfGame == 4) { //업다운
		RenderAct(typeOfGame);
		n = select(playerNum, 6);
		player[playerNum].setMinigameDid(n);
		if (n == -1) {
			player[playerNum].resetMinigameDid();
			return;
		}
		EraseChoiceScene();
		int tk = checkUpDown(playerNum, n) * 3; //2 1 0 -1
		player[playerNum].setCoin(tk);
		player[n].setCoin(-tk);
		miniGame(playerNum, 4);
	}
	else if (typeOfGame == 5) { //홀짝
		RenderAct(typeOfGame);
		n = select(playerNum, 6);
		player[playerNum].setMinigameDid(n);
		if (n == -1) {
			player[playerNum].resetMinigameDid();
			return;
		}
		EraseChoiceScene();
		int tk = checkEQ(playerNum, n - 1); //5 -5
		player[playerNum].setCoin(tk);
		player[n].setCoin(-tk);
		miniGame(playerNum, 5);
	}
}

int checkUpDown(int playerNum, int otherNum) {
	//상대방이 숫자 골라 1~10
	gotoxy(26, 4);
	cout << "Player" << otherNum + 1 << "숫자 지정";
	int num = select(otherNum, 8);
	int x = 0;
	for (int i = 0; i < 3; i++) {
		gotoxy(26, 2);
		cout << playerNum + 1 << " player(Life:"<<2-i<<")";
		x = select(playerNum, 8);
		if (num == x) {
			//std::cout<<i+1<<"트 win \n";
			EraseChoiceScene();
			gotoxy(23, 4);
			cout << "Correct!";
			gotoxy(23, 5);
			cout << "Player" << otherNum + 1 << "이 정한 숫자:" << num;
			gotoxy(26, 6);
			cout << "Player" << playerNum + 1 << "의 승리";
			gotoxy(23, 7);
			cout << "Player" << playerNum + 1 <<" "<< 3*(2-i) << "코인 획득! ";
			gotoxy(23, 8);
			cout << "Player" << otherNum + 1 << " " << 3 * (2 - i) << "코인 압수 ! ";
			//Sleep(1000);
			while (1) {
				int input = 0;
				input = _getch();
				if (input == 13)	break;
			}
			EraseChoiceScene();
			return 2 - i;
		}
		else if (num > x) {
			gotoxy(26, 5);
			cout << playerNum + 1 << " player(Life:" << 2 - i << ")";
			gotoxy(33, 8);
			cout << "Up";
			//Sleep(1000);
			while (1) {
				int input = 0;
				input = _getch();
				if (input == 13)	break;
			}
			EraseChoiceScene();
		}
		else {
			gotoxy(26, 5);
			cout << playerNum + 1 << " player(Life:" << 2 - i << ")";
			gotoxy(32, 8);
			cout << "Down";
			//Sleep(1000);
			while (1) {
				int input = 0;
				input = _getch();
				if (input == 13)	break;
			}
			EraseChoiceScene();
		}
	}
	gotoxy(25, 8);
	cout << "맞추지 못했습니다";
	return -1;
}

int checkEQ(int playerNum, int otherNum) {
	//상대방이 숫자 골라 1~10
	EraseChoiceScene();
	gotoxy(23, 4);
	cout << "Player" << otherNum + 1;
	int num = select(otherNum, 8); //1~10
	EraseChoiceScene();
	gotoxy(23, 4);
	cout << "Player" << playerNum + 1;
	int x = select(playerNum, 9); //1 2

	if (num % 2 == x % 2) {
		EraseChoiceScene();
		gotoxy(32, 4);
		cout << "Win!";
		gotoxy(23, 5);
		cout << "Player" << otherNum + 1 << "이 정한 숫자:" << num;
		gotoxy(23, 6);
		cout << "Player" << playerNum + 1 << "의 승리";
		gotoxy(23, 7);
		cout << "Player" << playerNum + 1 << " " << "5 코인 획득! ";
		gotoxy(23, 8);
		cout << "Player" << otherNum + 1 << " " << "5 코인 압수 ! ";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
		return 5;
	}
	else {
		EraseChoiceScene();
		gotoxy(32, 4);
		cout << "Lose";
		gotoxy(23, 5);
		cout << "Player" << otherNum + 1 << "이 정한 숫자:" << num;
		gotoxy(23, 6);
		cout << "Player" << otherNum + 1 << "의 승리";
		gotoxy(23, 7);
		cout << "Player" << playerNum + 1 << " " << "5 코인 압수! ";
		gotoxy(23, 8);
		cout << "Player" << otherNum + 1 << " " << "5 코인 획득 ! ";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		EraseChoiceScene();
		return -5;
	}
}

void checkRSP(int playerNum, int otherNum) { //return -1 이면 비김  가위 바위 보 바위 가위  보 
	gotoxy(32, 4);
	cout << "Player" << playerNum + 1;
	int pnum = RSP(playerNum);
	gotoxy(32, 4);
	cout << "Player" << otherNum + 1;
	int onum = RSP(otherNum);
	string pc, oc;
	if (pnum == 1)	pc = "가위";
	else if (pnum == 2)	pc = "바위";
	else if (pnum == 3)	pc = " 보";

	if (onum == 1)	oc = "가위";
	else if (onum == 2)	oc = "바위";
	else if (onum == 3)	oc = " 보";

	if ((pnum == 1 && onum == 2) || (pnum == 2 && onum == 3) || (pnum == 3 && onum == 1)) {
		EraseChoiceScene();
		gotoxy(28, 4);
		cout << "Player" << playerNum + 1 << " " << pc;
		gotoxy(28, 5);
		cout << "Player" << otherNum + 1 << " " << oc;
		gotoxy(28, 6);
		cout << "Player" << otherNum + 1 << " 승리";
		gotoxy(23, 7);
		cout << "Player" << otherNum + 1 << " " << "5 코인 획득! ";
		gotoxy(23, 8);
		cout << "Player" << playerNum + 1 << " " << "5 코인 압수 ! ";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		player[otherNum].setCoin(5);
		player[playerNum].setCoin(-5);
	} //진거
	if ((pnum == 1 && onum == 3) || (pnum == 2 && onum == 1) || (pnum == 3 && onum == 2)) {
		EraseChoiceScene();
		gotoxy(28, 4);
		cout << "Player" << playerNum + 1 << " " << pc;
		gotoxy(28, 5);
		cout << "Player" << otherNum + 1 << " " << oc;
		gotoxy(28, 6);
		cout << "Player" << playerNum + 1 << " 승리";
		gotoxy(23, 7);
		cout << "Player" << playerNum + 1 << " " << "5 코인 획득! ";
		gotoxy(23, 8);
		cout << "Player" << otherNum + 1 << " " << "5 코인 압수 ! ";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		player[playerNum].setCoin(5);
		player[otherNum].setCoin(-5);
	}
	if (pnum == onum) {
		EraseChoiceScene();
		gotoxy(28, 4);
		cout << "Player" << playerNum + 1 << " " << pc;
		gotoxy(28, 5);
		cout << "Player" << otherNum + 1 << " " << oc;
		gotoxy(26, 6);
		cout << "가위바위보 무승부";
		gotoxy(26, 7);
		cout << "아무일도 없었다";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
	}
}

int RSP(int playerNum) {
	return select(playerNum, 7);
}

int useItem(int playerNum, int vod) { // select4 return 0 : 나가기,아이템 없음  1 : 주사위주사위 3 : 가보자
	// 아이템이펙트 가보자	3
	// 아이템이펙트 꼼짝마 -3
	// 아이템이펙트 주사위주사위 1
	// 아이템이펙트 효과 없음 0
	//무슨 아이템 쓸건지 확인하고 실행까지 해줘야함
	if (vod == 1) //주주 
		return rollDice(playerNum);
	else
		return vod;
}

bool readMap(string mapName)
{	
	int n = 0;
	int num = 0;
	int i = 0;
	ifstream readFile;
	readFile.open(mapName);
	if (readFile.is_open()) {
		while (!readFile.eof()){
			readFile >> num;
			map.push_back(num);
			if (num == 2) {
				if (n == 2) {
					gotoxy(22, 9);
					cout << "상점은 2개이어야 합니다.";
					//Sleep(1000);
					while (1) {
						int input = 0;
						input = _getch();
						if (input == 13)	break;
					}
					return false;
				}
				shop[n++] = i;
			}
			else if (num < 0 || num>7) {
				gotoxy(18, 9);
				cout << "유효하지 않은 타일이 존재합니다.";
				//Sleep(1000);
				while (1) {
					int input = 0;
					input = _getch();
					if (input == 13)	break;
				}
				return false;
			}
			i++;
		}
	}
	if (n < 2) {
		gotoxy(20, 9);
		cout << "상점은 2개이어야 합니다.";
		//Sleep(1000);
		while (1) {
			int input = 0;
			input = _getch();
			if (input == 13)	break;
		}
		return false;
	}
	return true;
}

void findMap() {
	string path = "\*.txt";
	int n = 1;
	int k = 3;
	struct _finddata_t fd;
	gotoxy(31, 1);
	cout << "맵 선택";
	intptr_t handle;

	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)
	{

		cout << "No file in directory!" << endl;
		// 파일이 없을경우 발생시킬 이벤트.
	}
	do
	{
		mapName.push_back(fd.name);
		//gotoxy(23, k++);
		//cout << n++ << ". " << mapName[n-1];
		//cout << n ++ << ". " << fd.name;

	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);
}

int CursorMapChoice() {
	int n = 0;
	gotoxy(26, 6);
	RenderChoiceMap(mapName,n);
	int input = 0;
	while (input != 13) {
		input = _getch();
		if (input == 224) {
			input = _getch();
			if (input == 72) {
				if (n != mapName.size() - 1) {
					n++;
				}
				else {
					n = 0;
				}
			}
			else if (input == 80) {
				if (n != 0) {
					n--;
				}
				else {
					n = mapName.size() - 1;
				}
			}
		}
		gotoxy(26, 6);
		EraseChoiceMap();
		RenderChoiceMap(mapName,n);
	}
	//EraseChoiceScene();
	return n;
}

bool ChoiceMap() {
	printMapChoiceFrame();
	findMap();
	return readMap(mapName[CursorMapChoice()]);
}

int checkwhowin() {
	int max = -500;
	int whowin = 0;
	for (int i = 0; i < player.size(); i++) {
		if (max < player[i].getCoin() + player[i].getNowPosition()) {
			whowin = i + 1;
		}
	}
	return whowin;
}



int rollDice(int playerNum) {
	srand((unsigned int)time(NULL));
	int typeOfDice = player[playerNum].getDice();
	if (typeOfDice == 0) { //일반 
		return (rand() % 6) + 1;
	}
	else if (typeOfDice == 1) {//안전 2 3 3 4 4 5
		int vod = (rand() % 6) + 1;
		if (vod == 1)
			return 3;
		else if (vod == 6)
			return 4;
		else
			return vod;
	}
	else { //고수
		if ((rand() % 2) == 0)
			return 1;
		else
			return 6;
	}
}

