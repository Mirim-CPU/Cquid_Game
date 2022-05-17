#include "jingumdari.h"

int main_jingumdari(void) {
	while (1) {
		drawTitle();
		if (!JmenuDraw()) {
			gloop();
		}
		else
			break;
	}

	return 0;
}

void drawTitle() {
	int x = 48;
	int y = 2;
	system("cls");

	setColor(yellow, black);
	printf("\n\t\t\t\t    _ _                            _           _      ");
	printf("\n\t\t\t\t   (_|_)_ _   __ _  _  _ _ __   __| | __ _ _ _(_)     ");
	printf("\n\t\t\t\t   | | | ' | / _` |  || | '  \\\\/ _`  / _` | '_| |     ");
	printf("\n\t\t\t\t  _/ |_|_||_\\\\__, |\\\\_,_|_|_|_\\\\__,_\\\\__,_|_| |_|     ");
	printf("\n\t\t\t\t |__/        |___/                                    ");


	setColor(white, black);
	x = 37, y = 10;
	gotoxy(x, y);
	printf(" ---||-------||-------||----||------||-------||-----");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf("|           안깨진 징검다리를 맞추십시오.           |");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf("|      죽지 말고, 끝까지 징검다리를 건너십시오.     |");
	gotoxy(x, ++y);
	printf("|          방향키(← →) 엔터키(ENTER)              |");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf("|  총 10번의 기회 안에 징검다리를 건너면 통과입니다 |");
	gotoxy(x, ++y);
	printf("|                                                   |");
	gotoxy(x, ++y);
	printf(" ---||-------||-------||----||------||-------||-----");

	x = 94, y = 20;
	setColor(lightcyan, black);
	gotoxy(x, y);
	printf("    ♡ ♡ C  C ♡ ♡");
	gotoxy(x, ++y);
	printf("  ♡ ( //′- ′//) ♡ ");
	gotoxy(x, ++y);
	printf("    ┏━♡━ U U━♡━┓");
	gotoxy(x, ++y);
	printf("    ♡ 헤헤안녕  ♡");
	gotoxy(x, ++y);
	printf("    ┗━♡━━━━━━♡━┛");
	setColor(white, black);

	// 여기에 캐릭터 넣으면 됨!!
	setColor(brown, black);
	x = 7;
	y = 20;
	gotoxy(x, y);
	printf("＜￣｀ 、　　　　부엉　／￣＞");
	gotoxy(x, ++y);
	printf("　>、　　＼　／⌒\\,ノ 　/´");
	gotoxy(x, ++y);
	printf("　　　>、　`（ ´oωo)／");
	gotoxy(x, ++y);
	printf("　　 　　>　 　 　,ノ 　");
	gotoxy(x, ++y);
	printf("　　　　　∠_,,,/´””");
	setColor(white, black);
}

int JmenuDraw() {
	int input;
	int x = 58, y = 23;
	int key = y;
	int num = 1;
	gotoxy(x - 2, y);
	printf("> 시작하기\n");
	gotoxy(x, y + 1);
	printf("종료하기");
	while (1) {
		input = _getch();
		switch (input) {
		case UP: {
			if (y > key) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < key + num) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}
		case ENTER: {
			return y - key;
		}
		case ESC: {
			break;
		}
		}
	}
	return 0;
}
int JkeyControl() {
	int input;
	while (1) {
		input = _getch();
		switch (input) {
		case LEFT: {
			return 1;
			break;
		}
		case RIGHT: {
			return 2;
			break;
		}
		}
	}
	return 0;
}
void gloop() {
	int center = 15;
	int index = center;
	int turn = center;
	int life = center - 1;
	int arr_bool[16][2];	// 1 0 들어갈 배열
	char arr_glass[16][2];
	int a;

	//const randomBit = rand() % 2;
	//값 넣어주기
	system("cls");
	srand(time(NULL));
	for (int i = 0; i < 16; i++) {
		arr_bool[i][0] = rand() % 2;
		arr_bool[i][1] = !arr_bool[i][0];
		for (int j = 0; j < 2; j++) {
			arr_glass[i][j] = 'O';
			//printf("%d ", arr_bool[i][j]);
		}
		//printf("\n");
	}
	while (1) {

		system("cls");
		//테두리 그려주기
		for (int i = 0; i < 70; i++) {
			gotoxy(i, 0);
			printf("□");
			gotoxy(i, 29);
			printf("□");
		}
		for (int i = 0; i < 29; i++) {
			setColor(yellow, black);
			gotoxy(0, i);
			printf("■");
			gotoxy(70, i);
			printf("■");
			setColor(white, black);
		}
		int x = 25;
		int y = 3;
		// 징검다리 그려주기
		for (int i = 0; i < 16; i++) {
			gotoxy(x, ++y);
			printf("||");
			setColor(lightgreen, black);
			for (int j = 0; j < 2; j++) {
				printf("   %c   ", arr_glass[i][j]);
			}
			setColor(white, black);
			printf("||");
			if (i == turn + 1) printf("<------현위치\n");
			else printf("\n");
		}

		x = 75;
		y = 2;
		gotoxy(x, y);
		printf("저것 봐봐.. 저길 통과한대...");
		y = 4; gotoxy(x, ++y);
		setColor(white, black);
		printf(" /⌒＞―――＜⌒ヘ");
		gotoxy(x, ++y);
		printf("｜／　　　　　＼｜");
		gotoxy(x, ++y);
		printf(" Y　　　　　　　Y");
		gotoxy(x, ++y);
		printf(" | ●　　　 ●　|");
		gotoxy(x, ++y);
		printf(" ＼ //(_人_) //ノ");
		gotoxy(x, ++y);
		printf("　 ＞――――イ");
		gotoxy(x, ++y);
		printf("　/　|　　　|)");

		setColor(white, black);

		setColor(lightcyan, black);
		y = 12;
		gotoxy(x, y);
		printf(" -----------------");
		gotoxy(x, ++y);
		printf("|   생명♥ %d번   |\n", life);
		gotoxy(x, ++y);
		printf(" -----------------");

		y = 16;
		gotoxy(x, y);
		printf(" ----------------------");
		gotoxy(x, ++y);
		printf("|   %d번 참가자 도전!   |\n", center - life);
		gotoxy(x, ++y);
		printf(" ----------------------");

		setColor(white, black);
		y = 19;
		gotoxy(x, ++y);
		printf("당신의 선택은?");
		gotoxy(x, ++y);
		printf("1. 왼쪽 2. 오른쪽\n");
		gotoxy(x, ++y);
		scanf_s("%d", &a);


		y = 25;
		if (a == 1 || a == 2) {
			if (arr_bool[index][a - 1] == 1) {
				gotoxy(x, y);
				printf("성공!\n");
				Sleep(1000);
				index--;
				turn--;
			}
			else {
				gotoxy(x, y);
				printf("사망!\n");
				Sleep(1000);
				arr_glass[index][a - 1] = ' ';
				index = center;
				turn = center;
				life--;
			}
		}
		if (life == 0) {
			int x = 58;
			int y = 10;
			system("cls");
			gotoxy(x, y);
			printf("게임 오버...");
			Sleep(3000);
			break;
		}
		if (turn == -1) {
			system("cls");
			gotoxy(x, y);
			printf("우승!!!");
			Sleep(2000);
			break;
		}
	}
}