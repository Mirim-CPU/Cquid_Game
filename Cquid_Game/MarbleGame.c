#include "MarbleGame.h"

char tempMap[18][100];	//?? ?ӽ??????? ?迭

char map1[18][100] = {
	{"0"},
	{"0"},
	{"0"},
	{"0"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"},
	{"0000000000000000010000000100000000000000000000000000000000000000000000001"},
	{"0000000000000000010000000100000000000000000000000000000000000000000000001"}, // 0 : ?? ???? 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // 1 : ?? 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // k : ???? 
	{"0000000000000000010001000100000000000000000000000000000000000000000000001"}, // l : ???? ?? 
	{"0000000000000000010001000111111000000000000000000000000000000000000000001"}, // q : Ż?ⱸ  
	{"0000000000000000010001000000001000000000000000000000000000000000000000001"},
	{"0000000000000000010001000100001000000000000000000000000000000000000000001"},
	{"0000000000000000010001000100k01000000000000000000000000000000000011111111"},
	{"0000000000000000010001000100001000000000000000000000000000000000010000001"},
	{"0000000000000000010s010001111111111111111111111111111111111111111100q0001"},
	{"0000000000000000010001000l00000000000000k0000000000000000000000l000000001"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"}
};

char map2[18][100] = {
	{"0"},
	{"0"},
	{"0"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"},
	{"0000000000000000010s00100000000000l000k000000000000l0k1000000000000000001"},
	{"0000000000000000010000100111100000111111110001110011011000000000000000001"},
	{"0000000000000000011110111100000000l00000010001010001011111111111111100001"},
	{"000000000000000001k01000010001111110001l111111011111001000000000000100001"},
	{"000000000000000001001000010k010000111110000000000100001111100000000100001"},
	{"0000000000000000010010000100000000100000111110111100001000000100000100001"},
	{"0000000000000000010011100111111111111111100000100000001000000100000000001"},
	{"0000000000000000010000000100000000100000100000111001111111111111111111111"},
	{"0000000000000000011111100111000000l001000000111000000l0000000000000000001"},
	{"000000000000000001000k1l1100011111100111100010100000010111000101111111001"},
	{"0000000000000000010111100101110000001100110010100000010001111100001q01001"},
	{"0000000000000000010000000000k1001k100100000010000000010100000000001000001"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"}
};

char map3[18][100] = {
	{"0"},
	{"0"},
	{"0"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"},
	{"00000000000000000100000100010001k0001000000000010001000001000101000100001"},
	{"0000000000000000010000010101010111101011111011010101011101010101010001001"},
	{"000000000000000001000101010001000k10101000101k01010101k101010001111111001"},
	{"0000000000000000010001000101111111101010101011110001000101011111000000001"},
	{"00000000000000000100011111l1000000001010101000000011101101010001010111101"},
	{"0000000000000000010001000001011111111010101110111000000100010100010100001"},
	{"0000000000000000010001011111010000000010100000001110110101000101000100001"},
	{"0000000000000000010001010000010000001010110111100000000101010101010001l11"},
	{"0000000000000000010001010111010000001000000000101011110101010101011111l11"},
	{"00000000000000000100010101k0010000001111011110001000010101010100010000001"},
	{"0000000000000000010s010101111111110110010100001011110100010111110100q0001"},
	{"000000000000000001000100000l000l00010001000111100000010101000000010000001"},
	{"0000000000000000011111111111111111111111111111111111111111111111111111111"}
};


void drawMap(int* x, int* y) {
	system("cls");
	int h, w; //????, ????
	for (h = 0; h < 18; h++) {
		for (w = 0; w < 100; w++) {
			char temp = tempMap[h][w];	//?????? ?? ??????
			if (temp == '0') {	//?? ????(????)
				setBackColor(black, black);
				printf(" ");
			}
			else if (temp == '1') {	//??(#)
				setBackColor(white, white);
				printf("#");
			}
			else if (temp == 's') {	//?÷??̾?(@)
				*x = w;	//?÷??̾? ??ǥ?? ????
				*y = h;
				setBackColor(cyan, black);
				printf("@");
			}
			else if (temp == 'q') {	//??????(O)
				setBackColor(lightgreen, black);
				printf("O");
			}
			else if (temp == 'k') {	//????(*)
				setBackColor(yellow, black);
				printf("*");
			}
			else if (temp == 'l') {	//???? ?? 
				setBackColor(brown, black);
				printf("+");
			}
		}
		printf("\n");
	}
	setBackColor(white, black);
}

//???? ????
void gLoop(int mapCode) {
	time_t new_time, old_time;	//???? ?ð?
	int x, y;	// ?÷??̾? ??ǥ ???? ????????(x,y)
	int key = 0;
	int playing = 1; //1?̸? ??????, 0?̸? ???? ????
	int DELAY = 0;
	int move_key;

	if (mapCode == 0) {
		memcpy(tempMap, map1, sizeof(tempMap)); DELAY = 10000;
	}
	else if (mapCode == 1) {
		memcpy(tempMap, map2, sizeof(tempMap));	DELAY = 30000;
	}
	else if (mapCode == 2) {
		memcpy(tempMap, map3, sizeof(tempMap));	DELAY = 40000;
	}

	switch (drawlevel()) {
	case 0:
		DELAY += 10000;
		break;
	case 1:
		DELAY += 5000;
		break;
	}

	drawMap(&x, &y);	//?? ???? ?? ????, ?ʿ? ??ǥ ?????͸? ????
	old_time = clock();	//???۽ð?

	while (playing) {
		gamerule();
		drawUI(&x, &y, &key);
		move_key = getch();
		new_time = clock();
		// ?ð???
		double diff = difftime(new_time, old_time);
		if (diff > DELAY) {
			failDraw();
			break;
		}
		drawTime(diff, DELAY);

		switch (move_key) {
		case UP:	//???ο????̱?
			move(&x, &y, 0, -1, &key, &playing);
			break;

		case DOWN:	//?Ʒ??ο????̱?
			move(&x, &y, 0, 1, &key, &playing);
			break;

		case RIGHT:	//?????????ο????̱?
			move(&x, &y, 1, 0, &key, &playing);
			break;

		case LEFT:	//???????ο????̱?
			move(&x, &y, -1, 0, &key, &playing);
			break;
			//x : 1?? ?????ϸ? ?????????? ?̵?
			//y : 1?? ?????ϸ? ?Ʒ??? ?̵?

		case ESC:
			setBackColor(white, black);
			playing = 0;	//0?? ?Ǹ? ?ݺ? ????
		}
	}
	if (!playing) {
		endDraw();
	}
}

//???? ??ǥ(x, y), ?????? ??ǥ(_x, _y)
void move(int* x, int* y, int _x, int _y, int* key, int* playing) {
	//?̵??? ??ġ?? ?ִ? ?? ?迭?? ???? ?ӽ?????
	char mapObject = tempMap[*y + _y][*x + _x];
	setBackColor(white, black);

	if (mapObject == '0') {
		gotoxy(*x, *y);
		printf(" ");	//??????
		setBackColor(cyan, black); //?? ????
		gotoxy(*x + _x, *y + _y);	//?????? ??ġ?? ?̵? ?? ?÷??̾? ????
		printf("@");
		*x += _x;	//???? ??ǥ?? ?ݿ?--
		*y += _y;
	}
	else if (mapObject == 'k') {//?̵??? ??ġ?? ???谡 ?????? ȹ??
		*key += 1;	//???谳?? 1?? ????
		tempMap[*y + _y][*x + _x] = '0';	//ȹ???????? ?????? ?ִ? k?? 0???? ????
		gotoxy(*x + _x, *y + _y);	//???谡 ?ִ? ??ġ?? ????
		printf(" ");
	}
	else if (mapObject == 'l') {
		if (*key > 0) {
			*key -= 1;	//???谡 1?? ?̻??????? 1?? ?Ҹ?
			tempMap[*y + _y][*x + _x] = '0';	//???? ???????? l?????? 0???? ????
			setBackColor(white, black);	//?? ?⺻ ??
			gotoxy(*x + _x, *y + _y);
			printf(" ");
		}
	}
	else if (mapObject == 'q') {
		*playing = 0;	//1:???? ??????, 0:????????
	}
}

int keyControl(int x, int y, int num)
{
	int input;
	int key = y;

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
			return 1;
		}
		}
	}
	return 0;
}

//???? ?ϴܿ? ??ǥ ?? ?????? ???? ????
void drawUI(int* x, int* y, int* key) {
	setBackColor(white, black);
	gotoxy(79, 24);
	printf("--------------------");
	gotoxy(80, 25);
	printf("??ġ : %02d, %02d", *y, *x);
	gotoxy(79, 26);
	printf("--------------------");
	setBackColor(yellow, black);
	gotoxy(49, 24);
	printf("---------------");
	gotoxy(50, 25);
	printf("???? : %d??", *key);
	gotoxy(49, 26);
	printf("---------------");
}

void drawTime(double time, double stime)
{
	setBackColor(lightcyan, black);
	gotoxy(19, 24);
	printf("--------------------");
	gotoxy(20, 25);
	printf("???? ?ð? : %.0f ?? ", (stime - time) / 1000);
	gotoxy(19, 26);
	printf("--------------------");
}

int drawlevel()
{
	system("cls");
	int x = 58, y = 6;
	int level_n;
	setBackColor(white, black);
	printf("\n\n");
	printf("\t\t\t\t\t\t\t[???? ????]\n\n");
	gotoxy(x - 2, y);
	printf("> ?ϴܰ?");
	gotoxy(x, y + 1);
	printf("?ߴܰ?");
	gotoxy(x, y + 2);
	printf("???ܰ?");

	return keyControl(x, y, 2);
}

void titleDraw() {
	setBackColor(lightgreen, black);
	printf("\n\n\t\t\t  __  __            _     _        _____ \n");
	printf("\t\t\t |  \\/  |          | |   | |      / ____| \n");
	printf("\t\t\t | \\  / | __ _ _ __| |__ | | ___  | |  __  __ _ _ __ ___   ___ \n");
	printf("\t\t\t | |\\/| |/ _` | '__| '_ \\| |/ _ \\ | | |_ |/ _` | '_ ` _ \\ / _ \\ \n");
	printf("\t\t\t | |  | | (_| | |  | |_) | |  __/ | |__| | (_| | | | | | |  __/ \n");
	printf("\t\t\t |_|  |_|\\__,_|_|  |_.__/|_|\\___|  \\_____|\\__,_|_| |_| |_|\\___| \n");
	setBackColor(white, black);
	printf("\n\n");
	printf("          ??                        - - - - - ?? ?? ?? ???? ġ?? ?? ?? ?? - - - - -                      ?? \n\n");
	printf("                 ??                |      ?????? ?ļ? ?̷θ? Ż???Ͻʽÿ?          |        ??\n\n");
	printf("                                   |           ???? ???Ƶ? ???? ?ʽ??ϴ?.          |\n\n");
	printf("                       ??          |       ??(??), ?Ʒ?(??), ??(??), ??(??)        |              ??\n\n");
	printf("     ??                            |       Enter (????Ű) ESC (????Ű)             |       ??\n\n");
	printf("                                   |         ?ð????? Ż???ϸ? ?????Դϴ?.         |                     ??\n\n");
	printf("              ??                    - - - - - - - - - - - - - - - - - - - - - - - -\n");
}

int menuDraw() {
	int x = 55, y = 25;
	int input;
	gotoxy(x - 2, y);
	printf("> ???ӽ???");
	gotoxy(x, y + 1);
	printf("????????");
	setBackColor(darkgray, black);

	//gotoxy(x - 15, y + 3);
	print_by_name("?輭??, ????, ??????");
	//printf("developed by ?輭??, ????, ??????");
	setBackColor(white, black);

	return keyControl(x, y, 1);
}

int maplistDraw() {
	int x = 58;
	int y = 14;
	int n;
	system("cls");
	printf("\n\n\t\t                         - - - - - - - - - - - - - - - - - - \n");
	printf("\t\t                        |                                    |\n");
	printf("\t\t                        |              [?? ????]             |\n");
	printf("\t\t                        |                                    |\n");
	printf("\t\t                         - - - - - - - - - - - - - - - - - -");
	gotoxy(x - 2, y);
	printf("> Level 1");
	gotoxy(x, y + 1);
	printf("Level 2");
	gotoxy(x, y + 2);
	printf("Level 3");
	gotoxy(x, y + 3);
	printf("?ڷ?");
	printf("\n\n");
	printf("\t\t \t\t\t\t\t\t\t\t                     _ \n");
	printf("\t\t \t\t\t\t\t\t\t\t                    / ) \n");
	printf("\t\t \t\t\t\t\t\t\t\t                   ( ( \n");
	printf("\t\t \t\t\t\t\t\t\t\t     A.-.A  .-''-.  ) ) \n");
	printf("\t\t \t\t\t\t\t\t\t\t    / , , \\/      \\/ / \n");
	printf("\t\t \t\t\t\t\t\t\t\t    =\\  t  ;=    /  /\n");
	printf("\t\t \t\t\t\t\t\t\t\t     `--,'  . '' | / \n");
	printf("\t\t \t\t\t\t\t\t\t\t          || |  \\\\ \\ \n");
	printf("\t\t \t\t\t\t\t\t\t\t        ((,_|  ((,_\\ \n");
	printf("\t\t\t\t\t\t\t\t\t\t\t -----------------------");

	return keyControl(x, y, 3);
}

void endDraw() {
	PlaySound(NULL, 0, 0);
	system("cls");
	int x = 40, y = 5;	int input;
	gotoxy(x, y);
	printf("   _____ _    _  _____ _____ ______  _____ _____");
	gotoxy(x, y + 1);
	printf("  / ____| |  | |/ ____/ ____|  ____|/ ____/ ____|");
	gotoxy(x, y + 2);
	printf(" | (___ | |  | | |   | |    | |__  | (___| (___");
	gotoxy(x, y + 3);
	printf("  \\___ \\| |  | | |   | |    |  __|  \\___ \\\\___ \\");
	gotoxy(x, y + 4);
	printf("  ____) | |__| | |___| |____| |____ ____) |___) |");
	gotoxy(x, y + 5);
	printf(" |_____/ \\____/ \\_____\\_____|______|_____/_____/");
	gotoxy(x + 20, y + 7);
	printf("?????ϼ̽??ϴ?!");
	gotoxy(60, 23);
	printf(">???ư???<");
	gotoxy(50, 25);
	setBackColor(yellow, black);
	printf("?????? : ?輭??, ??????, ????");

	while (1) {
		input = _getch();
		if (input == ENTER) {
			system("cls");
			break;
		}
	}
}

void failDraw()
{
	PlaySound(NULL, 0, 0);
	int n;
	int x = 30, y = 8;
	system("cls");
	setBackColor(white, black);
	gotoxy(x, y);
	printf("    ___   _   __  __ ___    _____   _____ ___\n");
	gotoxy(x, y++);
	printf("   / __| /_\\ |  \\/  | __|  / _ \\ \\ / / __| _ \\ \n");
	gotoxy(x, y++);
	printf("  | (_ |/ _ \\| |\\/| | _|  | (_) \\ V /| _||   / \n");
	gotoxy(x, y++);
	printf("   \\___/_/ \\_\\_|  |_|___|  \\___/ \\_/ |___|_|_\\ \n");
	y += 3;
	x -= 5;
	gotoxy(x, y++);
	printf("\t?ð? ???? Ż?????? ???ؼ? ?????ϼ̽??ϴ?. ???͸? ?????? ???ư??ʽÿ?.");

	while (1) {
		n = _getch();
		if (n == ENTER) break;
	}
}

void gamerule()
{
	// ???? ???? ?ڵ?
	int x = 79, y = 4;
	setBackColor(white, black);
	gotoxy(x, y++);
	printf(" ===== ???? ???? =====");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|  ȭ??ǥ?? ????????  |");
	gotoxy(x, y++);
	printf("|       ?? ??????     |");
	gotoxy(x, y++);
	printf("|  ?????? ?????̼???  |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|   Ű (*)?? ???Ƽ?   |");
	gotoxy(x, y++);
	printf("|    ???? ??(+)??     |");
	gotoxy(x, y++);
	printf("|     ?????ϼ???      |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf("|      ????????       |");
	gotoxy(x, y++);
	printf("|      ?? ?Դϴ?      |");
	gotoxy(x, y++);
	printf("|                     |");
	gotoxy(x, y++);
	printf(" =====================");

}

//????
int main_marble() {
	PlaySound(TEXT("./sound/marble.wav"), NULL, SND_ASYNC | SND_LOOP);
	system("title ????ġ?? ");
	CursorView();
	int level_num;
	while (1) {
		system("cls");
		titleDraw();
		if (!menuDraw()) {
			level_num = maplistDraw();
			if (level_num == 0)	gLoop(0);
			else if (level_num == 1) gLoop(1);
			else if (level_num == 2) gLoop(2);
		}
		else {
			system("cls");
			main();
			break;
		}
	}
	return 0;
}