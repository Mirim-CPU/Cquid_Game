#include "modules.h"
#include "MarbleGame.h"
#include "Jingumdari.h"
#include "pushpull.h"
#include"dalgona.h"
#include "Mugunghwa.h"
#include "rhythm.h"

#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void set_console(void);
void set_cursor(int flag, int size);

void draw_main(void);
int select_game(void);

int main(void) {
	PlaySound(TEXT("./sound/mainback.wav"), NULL, SND_ASYNC | SND_LOOP);
	set_console();

	FILE* fp;

	if (fp = fopen("rank.txt", "r")) {
		fclose(fp);
	}
	else {
		fp = fopen("rank.txt", "w");
		fprintf(fp, "firstplace 0"); 

		fclose(fp);
	}
	

	// input value
	int select;
	while (select = select_game()) {
		PlaySound(NULL, 0, 0);

		switch (select)
		{
		case 1:
			rectangle(114, 29, 2, 1);
			main_mugunghwa();
			break;

		case 2:
			rectangle(114, 29, 2, 1);
			main_dalgona();
			break;

		case 3:
			rectangle(114, 29, 2, 1);
			main_pushpull();
			break;

		case 4:
			rectangle(114, 29, 2, 1);
			main_marble();
			break;

		case 5:
			rectangle(114, 29, 2, 1);
			main_jingumdari();
			break;

		case 6:
			rectangle(114, 29, 2, 1);
			rhythm_main();
			break;

		default:
			break;
		}
	}

	return 0;
}


void set_console(void) {
	// set the console size
	system("mode con:cols=120 lines=31");
	// hide cursor
	set_cursor(0, 1);
	// set title
	system("title Cquid Game");
	// clear console
	system("cls");
}

void set_cursor(int flag, int size) {
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = flag;
	cursor.dwSize = size;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}


void drawSolider(int x) {
	setColor(RED);
	gotoxy(x, 3); printf("       ¡á¡á¡á¡á");
	gotoxy(x, 4); printf("     ¡á        ¡á");
	gotoxy(x, 5); printf("   ¡á            ¡á");
	gotoxy(x, 6); printf("  ¡á              ¡á");
	gotoxy(x, 7); printf("  ¡á              ¡á");
	gotoxy(x, 8); printf("  ¡á              ¡á");
	gotoxy(x, 9); printf("  ¡á              ¡á");
	gotoxy(x, 10); printf("    ¡á          ¡á");
	gotoxy(x, 11); printf("      ¡á      ¡á");
	gotoxy(x, 12); printf("        ¡á¡á¡á");
	gotoxy(x, 13); printf("      ¡á¡á¡á¡á¡á");
	gotoxy(x, 14); printf("   ¡á¡á¡á¡á¡á¡á¡á¡á");
	gotoxy(x, 15); printf("  ¡á¡á¡á¡á¡á¡á¡á¡á¡á");
}

void draw_main(void) {
	system("cls");
	drawSolider(15);

	setColor(yellow);
	int x = 42;
	gotoxy(x, 4); printf(" _____ ____  __    __ _____ _____   ");
	gotoxy(x, 5); printf("/ ____/ __ ¡¬| |  | ||_   _|  __ ¡¬ ");
	gotoxy(x, 6); printf("| |   | |  | | |  | |  | | | |  | |");
	gotoxy(x, 7); printf("| |   | |  | | |  | |  | | | |  | | ");
	gotoxy(x, 8); printf("| |___| |__| | |__| | _| |_| |__| | ");
	gotoxy(x, 9); printf("¡¬____¡¬___¡¬¡¬____/ |_____|_____/  ");

	gotoxy(x, 10); printf("   _____          __    __ ______ ");
	gotoxy(x, 11); printf("  / ____|   /¡¬   |  ¡¬/  |  ____|");
	gotoxy(x, 12); printf(" | |  __   /  ¡¬  | ¡¬  / | |__ ");
	gotoxy(x, 13); printf(" | | |_ | / /¡¬¡¬ | |¡¬/| |  __|");
	gotoxy(x, 14); printf(" | |__| |/ ____ ¡¬| |   | | |____ ");
	gotoxy(x, 15); printf("  ¡¬____/_/   ¡¬_¡¬_|   |_|______|");



	drawSolider(80);

	setColor(WHITE);

	gotoxy(52, 18); printf("°ÔÀÓ ¼±ÅÃÈÄ ¿£ÅÍ");

	gotoxy(86, 5); printf("¡á¡á¡á¡á¡á");
	gotoxy(86, 6); printf("¡á      ¡á");
	gotoxy(86, 7); printf("¡á      ¡á");
	gotoxy(86, 8); printf("¡á¡á¡á¡á¡á");

	setColor(WHITE);
	gotoxy(21, 5); printf("  ¡Ü¡Ü¡Ü");
	gotoxy(21, 6); printf("¡Ü      ¡Ü");
	gotoxy(21, 7); printf("¡Ü      ¡Ü");
	gotoxy(21, 8); printf("  ¡Ü¡Ü¡Ü");


	setColor(WHITE);
	gotoxy(30, 22); printf("¨ç ¹«±ÃÈ­²É\n");
	gotoxy(54, 22);  printf("¨è ¼³ÅÁ»Ì±â");
	gotoxy(78, 22);  printf("¨é ÁÙ´Ù¸®±â");

	gotoxy(30, 26);  printf("¨ê ±¸½½Ä¡±â");
	gotoxy(54, 26);  printf("¨ë Â¡°Ë´Ù¸®");
	gotoxy(78, 26);  printf("¨ì ¸®µë°ÔÀÓ");


}

int select_game(void) {
	draw_main();

	int select_x[3] = { 26, 50, 74 };
	int select_y[2] = { 20, 24 };

	// default menu 1
	int select = 1;

	int i, j, x, y;

	int key = 0;
	while (key != ENTER) {
		// 1, 4 | 2, 5 | 3, 6 | 
		i = (select - 1) % 3;
		x = select_x[i];
		// 1, 2, 3| 5, 6, 7
		j = select <= 3 ? 0 : 1;
		y = select_y[j];

		// print rectangle
		print_auto_y(&x, &y, "¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");
		print_auto_y(&x, &y, "¦¢");
		gotoxy(x + 18, y - 1);			printf("¦¢");
		print_auto_y(&x, &y, "¦¢");
		gotoxy(x + 18, y - 1);			printf("¦¢");
		print_auto_y(&x, &y, "¦¢");
		gotoxy(x + 18, y - 1);			printf("¦¢");
		print_auto_y(&x, &y, "¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");

		// ¡è, ¡é, ¡ç, ¡æ
		key = _getch();

		switch (key) {
		case RIGHT:
			select = select == 6 ? 6 : select + 1;
			break;

		case LEFT:
			select = select == 1 ? 1 : select - 1;
			break;

		case UP:
			if (select > 3) {
				select -= 3;
			}
			break;

		case DOWN:
			if (select <= 3) {
				select += 3;
			}
			break;
		}

		// remove rectangle
		y -= 5;
		print_auto_y(&x, &y, "                    ");
		print_auto_y(&x, &y, "  ");
		gotoxy(x + 18, y - 1);			printf("  ");
		print_auto_y(&x, &y, "  ");
		gotoxy(x + 18, y - 1);			printf("  ");
		print_auto_y(&x, &y, "  ");
		gotoxy(x + 18, y - 1);			printf("  ");
		print_auto_y(&x, &y, "                    ");
	}

	return select;
}