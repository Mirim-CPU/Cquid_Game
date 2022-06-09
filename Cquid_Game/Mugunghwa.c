#include "Mugunghwa.h"


HANDLE musicThread;
HANDLE controlThread;
#define MAX 140
int score = 0; //점수
double beginTime;
double endTime;
double thisTime; //begin-end;
int showMN = 0;
double soundtime = 0; //술래 움직임 체크
double chktime = 0; // 플레이어 움직임 체크
int answer[MAX]; //문제 저장
int heart = 5; //목숨값
int inputChk = 1; //스레드 설정
int arrowNum = 0;// 맵 넘버
void check_rank();
typedef struct user {
	char name[10];
	int score;
}User;

User user;

//좌표
void gotoxy_2x(int x, int y)
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}



//커서 제어
int MkeyControl() {
	char c;
	while (1) {
		if (_kbhit()) {
			c = _getch();

			if (c == -32) {
				c = _getch();
				switch (c) {

				case 72:
					return UP; break;
				case 80:
					return DOWN;  break;
				case 75:
					return LEFT; break;
				case 77:
					return RIGHT; break;
				}
			}
			else if (c == 13)
				return ENTER;
		}
	}
}

//제목
void Mugunghwa_title() {

	int x = 1;
	int y = 6;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	gotoxy_2x(x, y++);  printf(" __   __ __   __ _______ __   __ __    _ _______ __   __ _     _ _______ ");
	gotoxy_2x(x, y++);  printf("|  |_|  |  | |  |       |  | |  |  |  | |       |  | |  | | _ | |   _   |");
	gotoxy_2x(x, y++);  printf("|       |  | |  |    ___|  | |  |   |_| |    ___|  |_|  | || || |  |_|  |");
	gotoxy_2x(x, y++);  printf("|       |  |_|  |   | __|  |_|  |       |   | __|       |       |       |");
	gotoxy_2x(x, y++);  printf("|       |       |   ||  |       |  _    |   ||  |       |       |       |");
	gotoxy_2x(x, y++);  printf("| ||_|| |       |   |_| |       | | |   |   |_| |   _   |   _   |   _   |");
	gotoxy_2x(x, y++);  printf("|_|   |_|_______|_______|_______|_|  |__|_______|__| |__|__| |__|__| |__|");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	gotoxy_2x(x, y++);  printf("|  | |  |   _   |       |     ");
	gotoxy_2x(x, y++);  printf("|  |_|  |  |_|  |  _____|   ");
	gotoxy_2x(x, y++);  printf("|       |       | |_____  ");
	gotoxy_2x(x, y++);  printf("|       |       |_____  |    ");
	gotoxy_2x(x, y++);  printf("|   _   |   _   |_____| |   ");
	gotoxy_2x(x, y++);  printf("|__|_|__|__| |__|_______|");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
	printf("_______ __   __ _______ ______          ");
	gotoxy_2x(x, y++);  printf("|  _    |   |   |       |       |  |_|  |       |      |         ");
	gotoxy_2x(x, y++);  printf("| |_|   |   |   |   _   |   _   |       |    ___|  _    |   ");
	gotoxy_2x(x, y++);  printf("|       |   |   |  | |  |  | |  |       |   |___| | |   |   ");
	gotoxy_2x(x, y++);  printf("|  _   ||   |___|  |_|  |  |_|  |       |    ___| |_|   |    ");
	gotoxy_2x(x, y++);  printf("| |_|   |       |       |       | ||_|| |   |___|       |     ");
	gotoxy_2x(x, y++);  printf("|_______|_______|_______|_______|_|   |_|_______|______|    ");


}



//설명
void manual() {
	gotoxy(82, 8);  printf("_____________________________");
	gotoxy(85, 10);  printf("무궁화 꽃이 피었습니다");
	gotoxy(93, 12);  printf("○△□ ");

	gotoxy(82, 13);  printf("참가자는 방향키(→←↑↓)를 ");
	gotoxy(85, 14);  printf("눌러 영희가 있는 곳 까지");
	gotoxy(88, 15);  printf("도착해야합니다");

	gotoxy(82, 17);  printf("ESC를 누르면 게임종료가 됩니다");
	gotoxy(93, 18);  printf("○△□ ");
	gotoxy(82, 19);  printf("_____________________________");


	gotoxy(20, 28);  printf("엔터키와 방향키로 시작!");

}

void showMenu() {
	int x = 45;
	int y = 22;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy_2x(x - 1, y);  printf("▶ 게 임 시 작");
	gotoxy_2x(x, y += 2);  printf(" 게 임 종 료");

	gotoxy_2x(30, y -= 2);
}
//메뉴선택
int  menu() {

	int x = 45;
	int y = 22;
	int show = 0;

	//if (++showMN == 1) showMenu();

	while (1) {
		int n = MkeyControl();
		switch (n)
		{

		case UP: {
			if (y > 22) {

				gotoxy_2x(x - 1, y); printf("  ");
				gotoxy_2x(x - 1, y -= 2); printf("▶");
			}
			break;
		}
		case DOWN: {
			if (y < 24) {
				gotoxy_2x(x - 1, y); printf("  ");
				gotoxy_2x(x - 1, y += 2); printf("▶");
			}

			break;
		}
		case ENTER: {
			return y - 22;
			break;
		}

		}
	}

}

//완료 체크
void checkFinish(int x, int y) {
	if (x >= 50 && y >= 1 && y <= 23) {
		system("cls");
		gotoxy_2x(30, 13); printf("완주");
		check_rank();
	}
}

int m_x = 3; //화살표 처음 위치
//캐릭터 움직이기


unsigned _stdcall character_control() {
	int x = 4;
	int y = 6;

	int i = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);

	gotoxy_2x(4, 5); printf("START!");
	Sleep(800);
	gotoxy_2x(4, 5); printf("          ");

	while (inputChk) {

		int n = MkeyControl();


		switch (n)
		{


		case RIGHT: {

			if (answer[i] == 0) { score += 10; }
			else heart--;
			break;


		}
		case LEFT: {

			if (answer[i] == 1) { score += 10; }
			else heart--;
			break;


		}
		case UP: {


			if (answer[i] == 3) { score += 10; }
			else heart--;


			break;
		}

		case DOWN: {

			if (answer[i] == 2) { score += 10; }
			else heart--;
			break;
		}
		}

		if (arrowNum == 0) {
			switch (i / 5)
			{
			case 0: gotoxy_2x(x, y++); printf("  "); break;
			case 1:  gotoxy_2x(x++, y); printf("  "); break;
			case 2:  gotoxy_2x(x, y++); printf("  "); break;
			case 3: gotoxy_2x(x++, y); printf("  "); break;
			case 4: gotoxy_2x(x, y--);  printf("  "); break;
			case 5: gotoxy_2x(x++, y); printf("  "); break;
			case 6:  gotoxy_2x(x, y++); printf("  "); break;
			case 7:  gotoxy_2x(x++, y); printf("  "); break;
			case 8:  gotoxy_2x(x, y++); printf("  "); break;
			case 9:  gotoxy_2x(x++, y);  printf("  "); break;
			case 10:  gotoxy_2x(x, y--); printf("  "); break;
			case 11:  gotoxy_2x(x, y--); printf("  "); break;
			case 12:  gotoxy_2x(x, y--); printf("  "); break;
			case 13:  gotoxy_2x(x--, y); printf("  "); break;
			case 14:  gotoxy_2x(x--, y); printf("  "); break;
			case 15:  gotoxy_2x(x, y--); printf("  "); break;
			case 16:  gotoxy_2x(x++, y); printf("  "); break;
			case 17:  gotoxy_2x(x++, y); printf("  "); break;
			case 18:  gotoxy_2x(x++, y); printf("  "); break;
			case 19:  gotoxy_2x(x, y++); printf("  "); break;
			case 20:  gotoxy_2x(x, y++); printf("  "); break;
			case 21:  gotoxy_2x(x, y++); printf("  "); break;
			case 22:  gotoxy_2x(x++, y); printf("  "); break;
			case 23:  gotoxy_2x(x, y++); printf("  "); break;
			case 24:  gotoxy_2x(x++, y); printf("  "); break;
			case 25:  gotoxy_2x(x, y--); printf("  "); break;
			case 26:  gotoxy_2x(x, y--); printf("  "); break;
			case 27:  gotoxy_2x(x++, y); printf("  "); break;
			}
		}

		else if (arrowNum == 1) {
			switch (i / 5)
			{
			case 0: gotoxy_2x(x, y++); printf("  ");  break;
			case 1:  gotoxy_2x(x++, y++); printf("  ");   break;
			case 2:  gotoxy_2x(x++, y--); printf("  ");   break;
			case 3: gotoxy_2x(x++, y++); printf("  ");   break;
			case 4: gotoxy_2x(x, y--);  printf("  ");  break;
			case 5: gotoxy_2x(x++, y++); printf("  ");  break;
			case 6:  gotoxy_2x(x++, y--); printf("  ");   break;
			case 7:  gotoxy_2x(x--, y--); printf("  ");   break;
			case 8:  gotoxy_2x(x--, y); printf("  ");  break;
			case 9:  gotoxy_2x(x, y--); printf("  ");  break;
			case 10:  gotoxy_2x(x++, y); printf("  ");  break;
			case 11:  gotoxy_2x(x++, y); printf("  ");  break;
			case 12:  gotoxy_2x(x, y++); printf("  ");  break;
			case 13:  gotoxy_2x(x++, y); printf("  ");  break;
			case 14:  gotoxy_2x(x, y++); printf("  ");  break;
			case 15:  gotoxy_2x(x, y++); printf("  ");  break;
			case 16:  gotoxy_2x(x, y++); printf("  "); break;
			case 17:  gotoxy_2x(x++, y--); printf("  ");   break;
			case 18:  gotoxy_2x(x++, y--); printf("  ");   break;
			case 19:  gotoxy_2x(x--, y--); printf("  ");  break;
			case 20:  gotoxy_2x(x, y--); printf("  ");  break;
			case 21:  gotoxy_2x(x++, y); printf("  ");  break;
			case 22:  gotoxy_2x(x++, y); printf("  ");  break;
			case 23:  gotoxy_2x(x, y++); printf("  ");  break;
			case 24:  gotoxy_2x(x, y++); printf("  ");   break;
			case 25:  gotoxy_2x(x--, y++);  printf("  "); ;  break;
			case 26:  gotoxy_2x(x, y++);  printf("  ");   break;
			case 27:  gotoxy_2x(x++, y);  printf("  ");    break;
			}
		}

		else if (arrowNum == 2) {
			switch (i / 5)
			{
			case 0: gotoxy_2x(x, y++); printf("  ");  break;
			case 1:  gotoxy_2x(x, y++); printf("  ");    break;
			case 2:  gotoxy_2x(x, y++); printf("  ");    break;
			case 3: gotoxy_2x(x++, y); printf("  ");   break;
			case 4: gotoxy_2x(x, y--); printf("  ");  break;
			case 5: gotoxy_2x(x, y--);  printf("  ");  break;
			case 6:  gotoxy_2x(x, y--); ; printf("  ");   break;
			case 7:  gotoxy_2x(x, y--);  printf("  ");  break;
			case 8:  gotoxy_2x(x++, y++); printf("  ");  break;
			case 9:  gotoxy_2x(x++, y++); printf("  ");   break;
			case 10:  gotoxy_2x(x--, y); printf("  ");  break;
			case 11:  gotoxy_2x(x++, y++); printf("  ");  break;
			case 12:  gotoxy_2x(x, y++); printf("  ");  break;
			case 13:  gotoxy_2x(x++, y); printf("  ");   break;
			case 14:  gotoxy_2x(x++, y--); printf("  ");  break;
			case 15:  gotoxy_2x(x--, y--); printf("  ");   break;
			case 16:  gotoxy_2x(x, y--); printf("  ");   break;
			case 17:  gotoxy_2x(x--, y--); printf("  ");   break;
			case 18:  gotoxy_2x(x++, y); printf("  ");  break;
			case 19:  gotoxy_2x(x++, y); printf("  ");  break;
			case 20:  gotoxy_2x(x++, y); printf("  ");  break;
			case 21:  gotoxy_2x(x, y++); printf("  ");   break;
			case 22:  gotoxy_2x(x, y++); printf("  ");   break;
			case 23:  gotoxy_2x(x, y++); printf("  ");  break;
			case 24:  gotoxy_2x(x, y++); printf("  ");  break;
			case 25:  gotoxy_2x(x++, y); printf("  ");   break;
			case 26:  gotoxy_2x(x++, y--); printf("  ");   break;
			case 27:  gotoxy_2x(x++, y--); printf("  ");  break;
			}
		}


		//맵 바꾸기~
		if (i == MAX - 1) { //139

			switch (arrowNum)
			{
			case 0: arrowNum = 1; 		break;
			case 1: arrowNum = 2; 		break;
		    case 2: arrowNum = 0;  	break;

			}
			//맵구성 초기화
			i = 0;
			x = 4; y = 6;


			mission();
		}
		else i++;


		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy_2x(20, 28); printf(" %d", score);
		gotoxy_2x(46, 28); printf(" %d", heart);


	}

}

//영희 보여주기
void showYoungHee(int show) {
	int x = 52;
	int y = 7;

	if (show == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy_2x(x, y++);  printf("／￣￣￣￣＼");
		gotoxy_2x(x, y++);  printf("/ㅡ　 　ㅡ ＼ ");
		gotoxy_2x(x, y++);  printf("/(★) (★)     ");
		gotoxy_2x(x, y++);  printf("｜⌒ 人⌒   | ");
		gotoxy_2x(x, y++);  printf("＼　　     ノ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		gotoxy_2x(x, y++);  printf("  /⌒＼-イ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		gotoxy_2x(x, y++);  printf(" (　r 　 ｜ ");
		gotoxy_2x(x, y++);  printf(" ＼ノノ--｜ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy_2x(x, y++);  printf("  |＿_/_/ ");
		gotoxy_2x(x, y++);  printf("  `ㅡ^ㅡ`");
	}
	//영희 뒤돌기전
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy_2x(x, y++);  printf("／￣￣￣￣＼");
		gotoxy_2x(x, y++);  printf("/　 ㅡ　 ㅡ＼ ");
		gotoxy_2x(x, y++);  printf("/ (●) 　(●) ");
		gotoxy_2x(x, y++);  printf("｜ ⌒  人⌒ | ");
		gotoxy_2x(x, y++);  printf("＼　　     ノ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		gotoxy_2x(x, y++);  printf("  /⌒＼-イ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
		gotoxy_2x(x, y++);  printf(" (　r 　 ｜ ");
		gotoxy_2x(x, y++);  printf(" ＼ノノ--｜ ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		gotoxy_2x(x, y++);  printf("  |＿_/_/ ");
		gotoxy_2x(x, y++);  printf("  `ㅡ^ㅡ`");
	}

}
void showGameOver(char* c) {

	system("cls");
	PlaySound(TEXT("./sound/mugunghwa/tang.wav"), NULL, SND_FILENAME | SND_ASYNC);
	system("color 40");
	Sleep(1000);
	system("color 0C");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy_2x(27, 13); printf("GAME OVER");
	gotoxy_2x(25, 15); printf("%s", c);
	gotoxy_2x(28, 17); printf("점수 : %d", score);
	gotoxy_2x(25, 20); printf("2초후 메인화면으로...");


	check_rank();
	score = 0;
	heart = 5;
	Sleep(1500);
	system("cls");
	main_mugunghwa();


}


void check() {

	if (heart == 0) {
		inputChk = 0;
		showGameOver("5번 기회를 다 날렸다!");
		TerminateThread(musicThread, 0);
		TerminateThread(controlThread, 0);

	}

	if (_kbhit()) {

		if (thisTime > (double)soundtime && thisTime < (double)soundtime + 2) {
			inputChk = 0;
			showGameOver("영희에게 걸려버렸다!");
			TerminateThread(musicThread, 0);
			TerminateThread(controlThread, 0);

		}
	}
}





unsigned _stdcall  MusicTimer() {
	timeBeginPeriod(1);



	while (inputChk) {

		int rn = (rand() % 5);

		switch (rn)
		{

		case 0:	PlaySound(TEXT("./sound/mugunghwa/sound1.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 4.5; break;
		case 1:	PlaySound(TEXT("./sound/mugunghwa/sound2.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 3.2; break;
		case 2:	PlaySound(TEXT("./sound/mugunghwa/sound3.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 2.3; break;
		case 3:	PlaySound(TEXT("./sound/mugunghwa/sound4.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 1.9; break;
		case 4:	PlaySound(TEXT("./sound/mugunghwa/sound5.wav"), NULL, SND_FILENAME | SND_ASYNC); soundtime = 1.5;   break;

		}

		beginTime = timeGetTime();

		while (inputChk)
		{
			endTime = timeGetTime();

			thisTime = (endTime - beginTime) / 1000;

			if (thisTime == soundtime) {
				showYoungHee(1);
			}
			else if (thisTime == soundtime + 2) {
				showYoungHee(0);
				beginTime = (double)0;
				break;
			}



		}
	}

	return 0;
}




//술래 과정
void tagger() {
	int showMotion = 0; //영희 모션 상태 1 - 뒤돌기, 0 - 앞 보기
	showYoungHee(showMotion);

	controlThread = _beginthreadex(NULL, 0, character_control, 0, 0, NULL);
	musicThread = _beginthreadex(NULL, 0, MusicTimer, 0, 0, NULL);

	while (1) {
		check();
	}

}




void showHeart() {

	int y = 26;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	gotoxy_2x(32, y++);  printf("  ,d88b.d88b,");
	gotoxy_2x(32, y++);  printf("  88888888888");
	gotoxy_2x(32, y++);  printf("  `Y8888888Y'");
	gotoxy_2x(32, y++);  printf("    `Y888Y'    ");
	gotoxy_2x(32, y++);  printf("      `Y' ");

	y = 27;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy_2x(40, y++);  printf("( ＼/ )");
	gotoxy_2x(40, y++);  printf("  ) ( ");
	gotoxy_2x(40, y++);  printf("(_/＼_)");
	gotoxy_2x(46, 28); printf(" %d", 5);

}


//점수 나타내기
void showScore() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
	int y = 26;
	gotoxy_2x(5, y++);  printf(" ___  ___ ___   _  __ ___   ");
	gotoxy_2x(5, y++);  printf("/ __|/ __/ _ ＼ | '__/ _ ＼  0");
	gotoxy_2x(5, y++);  printf("＼__＼ (_| (_)  | |  | __/");
	gotoxy_2x(5, y++);  printf("|___/＼___＼___/|_|  ＼___|  0 ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	gotoxy_2x(20, 28); printf(" % d", 0);

}



//맵 라인 그리기
void map() {
	mission(); //미션
	int show = 0; // 1 = show, 0 - hide
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	for (int i = 0; i < 60; i++) {
		gotoxy_2x(i, 0); printf("■");
	}

	for (int i = 0; i < 60; i++) {
		gotoxy_2x(i, 24); printf("■");
	}
	//start 라인
	for (int i = 0; i < 25; i++) {
		gotoxy_2x(3, i); printf("|");
	}

	//finish 라인
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
	for (int i = 1; i < 24; i++) {
		gotoxy_2x(50, i); printf("|");
	}

	tagger();



}




//미션출력
void mission() {

	srand(time(NULL));
	char m[4][10] = { "→","←","↓","↑" };
	int color[5] = { 10, 11, 13,  6,4 }; //컬러 랜덤
	int x = 4, y = 6;


	for (int i = 0; i < MAX; i++) {
		int rn = (rand() % 4);
		int crn = (rand() % 5);
		answer[i] = rn;

		if (arrowNum == 0) {
			switch (i / 5)
			{
			case 0: gotoxy_2x(x, y++); printf("%s", m[rn]); break;
			case 1:  gotoxy_2x(x++, y); printf("%s", m[rn]);   break;
			case 2:  gotoxy_2x(x, y++); printf("%s", m[rn]);   break;
			case 3: gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 4: gotoxy_2x(x, y--);  printf("%s", m[rn]);  break;
			case 5: gotoxy_2x(x++, y); printf("%s", m[rn]); break;
			case 6:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 7:  gotoxy_2x(x++, y);  printf("%s", m[rn]);  break;
			case 8:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 9:  gotoxy_2x(x++, y);  printf("%s", m[rn]);  break;
			case 10:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 11:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 12:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 13:  gotoxy_2x(x--, y); printf("%s", m[rn]);  break;
			case 14:  gotoxy_2x(x--, y); printf("%s", m[rn]);  break;
			case 15:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 16:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 17:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 18:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 19:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 20:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 21:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 22:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 23:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 24:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 25:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 26:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 27:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			}
		}
		else if (arrowNum == 1) {
			switch (i / 5)
			{
			case 0: gotoxy_2x(x, y++); printf("%s", m[rn]); break;
			case 1:  gotoxy_2x(x++, y++); printf("%s", m[rn]);   break;
			case 2:  gotoxy_2x(x++, y--); printf("%s", m[rn]);   break;
			case 3: gotoxy_2x(x++, y++); printf("%s", m[rn]);  break;
			case 4: gotoxy_2x(x, y--);  printf("%s", m[rn]);  break;
			case 5: gotoxy_2x(x++, y++); printf("%s", m[rn]); break;
			case 6:  gotoxy_2x(x++, y--); printf("%s", m[rn]);  break;
			case 7:  gotoxy_2x(x--, y--); printf("%s", m[rn]);  break;
			case 8:  gotoxy_2x(x--, y); printf("%s", m[rn]);  break;
			case 9:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 10:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 11:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 12:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 13:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 14:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 15:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 16:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 17:  gotoxy_2x(x++, y--); printf("%s", m[rn]);  break;
			case 18:  gotoxy_2x(x++, y--); printf("%s", m[rn]);  break;
			case 19:  gotoxy_2x(x--, y--); printf("%s", m[rn]);  break;
			case 20:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 21:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 22:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 23:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 24:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 25:  gotoxy_2x(x--, y++); printf("%s", m[rn]);  break;
			case 26:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 27:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			}
		}

		else if (arrowNum == 2) {
			switch (i / 5)
			{
			case 0: gotoxy_2x(x, y++); printf("%s", m[rn]); break;
			case 1:  gotoxy_2x(x, y++); printf("%s", m[rn]);   break;
			case 2:  gotoxy_2x(x, y++); printf("%s", m[rn]);   break;
			case 3: gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 4: gotoxy_2x(x, y--);  printf("%s", m[rn]);  break;
			case 5: gotoxy_2x(x, y--);  printf("%s", m[rn]); break;
			case 6:  gotoxy_2x(x, y--); ; printf("%s", m[rn]);  break;
			case 7:  gotoxy_2x(x, y--);  printf("%s", m[rn]);  break;
			case 8:  gotoxy_2x(x++, y++); printf("%s", m[rn]);  break;
			case 9:  gotoxy_2x(x++, y++);  printf("%s", m[rn]);  break;
			case 10:  gotoxy_2x(x--, y); printf("%s", m[rn]);  break;
			case 11:  gotoxy_2x(x++, y++); printf("%s", m[rn]);  break;
			case 12:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 13:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 14:  gotoxy_2x(x++, y--); printf("%s", m[rn]);  break;
			case 15:  gotoxy_2x(x--, y--); printf("%s", m[rn]);  break;
			case 16:  gotoxy_2x(x, y--); printf("%s", m[rn]);  break;
			case 17:  gotoxy_2x(x--, y--); printf("%s", m[rn]);  break;
			case 18:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 19:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 20:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 21:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 22:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 23:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 24:  gotoxy_2x(x, y++); printf("%s", m[rn]);  break;
			case 25:  gotoxy_2x(x++, y); printf("%s", m[rn]);  break;
			case 26:  gotoxy_2x(x++, y--); printf("%s", m[rn]);  break;
			case 27:  gotoxy_2x(x++, y--); printf("%s", m[rn]);  break;
			}

		}


		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[crn]);
		//화살표 출력
	}
}


//1위 계산, 파일 입출력 저장
void check_rank() {
	FILE* fp;
	User first_place;

	fp = fopen("rank.txt", "r");
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		exit(1);
	}

	fscanf(fp, "%s %d", first_place.name, &first_place.score);
	//printf("%s : %d\n", user.name, user.score);

	fclose(fp);
	user.score = score;

	if (first_place.score < user.score) {
		fp = fopen("rank.txt", "w");
		fprintf(fp, "%s %d\n", user.name, user.score);

		fclose(fp);
	}
}

//1위 보여주기
void show_rank() {
	FILE* fp;
	User first_place;

	fp = fopen("rank.txt", "r");
	if (fp == NULL) {
		printf("파일 열기 실패\n");
		exit(1);
	}

	fscanf(fp, "%s %d", first_place.name, &first_place.score);
	//printf("%s : %d\n", first_place.name, first_place.score);

	fclose(fp);

	setColor(YELLOW);
	gotoxy_2x(41, 3); printf("┏━━━━━━━━  현재 1위 ━━━━━━━━┓\n");
	gotoxy_2x(41, 4); printf("┃                           ┃\n");
	gotoxy_2x(41, 5); printf("┃                           ┃\n");
	gotoxy_2x(41, 6); printf("┃                           ┃\n");
	gotoxy_2x(41, 7); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	gotoxy_2x(43, 5);
	setColor(WHITE);
	printf(">> %s : %d <<", first_place.name, first_place.score);
}

//참가자 이름 입력
void setUser() {
	int setX = 14, setY = 9;
	system("cls");
	gotoxy_2x(setX, setY++); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┃                                                            ┃\n");
	gotoxy_2x(setX, setY++); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

	setY = 9;
	gotoxy_2x(setX + 5, setY + 4);
	printf("* 참가자님 이름을 입력해주세요(5자이내) *\n");
	gotoxy_2x(setX + 15, setY + 6);
	scanf("%s", user.name);
}

//게임 시작
void StartGame() {

	system("cls");
	CursorView(); //커서 숨기기
	showScore();//점수판
	showHeart();//목숨판
	map(); //맵 그리기
	system("pause>null\n");
}


void  main_mugunghwa() {
	system("cls");
	PlaySound(TEXT("./sound/mugunghwa/back.wav"), NULL, SND_ASYNC | SND_LOOP);
	CursorView();
	//system("mode con: cols=120 lines=30");
	system("title 무궁화꽃이 피었습니다");
	manual();
	Mugunghwa_title();
	showMenu();
	show_rank();
	print_by_name("조해정 황소은");
	while (1) {
		switch (menu()) {
		case 0: 	inputChk = 1;  	setUser(); StartGame(); break; //게임시작
		case 2: 	system("cls"); main();  break; // 게임종료

		}

	}
	system("pause>null\n");
}