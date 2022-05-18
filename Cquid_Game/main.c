#include "modules.h"
#include "MarbleGame.h"
#include "Jingumdari.h"
#include "pushpull.h"
#include"dalgona.h"
#include "Mugunghwa.h"

//타이틀 찍기
void title() {
	gotoxy(60, 4); printf(" _____ ____  __    __ _____ _____   ");
	gotoxy(60, 5); printf("/ ____/ __ ＼| |  | ||_   _|  __ ＼ ");
	gotoxy(60, 6); printf("| |   | |  | | |  | |  | | | |  | |");
	gotoxy(60, 7); printf("| |   | |  | | |  | |  | | | |  | | ");
	gotoxy(60, 8); printf("| |___| |__| | |__| | _| |_| |__| | ");
	gotoxy(60, 9); printf("＼____＼___＼＼____/ |_____|_____/  ");

	gotoxy(60, 10); printf("   _____          __    __ ______ ");
	gotoxy(60, 11); printf("  / ____|   /＼   |  ＼/  |  ____|");
	gotoxy(60, 12); printf(" | |  __   /  ＼  | ＼  / | |__ ");
	gotoxy(60, 13); printf(" | | |_ | / /＼＼ | |＼/| |  __|");
	gotoxy(60, 14); printf(" | |__| |/ ____ ＼| |   | | |____ ");
	gotoxy(60, 15); printf("  ＼____/_/   ＼_＼_|   |_|______|");
}

//게임 포커스
void focus() {




	/*gotoxy(11, 20);
	printf("┌─────────────────┐\n");
	gotoxy(11, 21);
	printf("│                 │\n");
	gotoxy(11, 22);
	printf("│                 │\n");
	gotoxy(11, 23);
	printf("│                 │\n");
	gotoxy(11, 24);
	printf("└─────────────────┘\n");*/

	gotoxy(13, 22); printf("① 무궁화 꽃\n");
	gotoxy(26, 22);  printf("② 달고나뽑기");
	gotoxy(39, 22);  printf("③ 줄다리기");
	gotoxy(13, 26);  printf("④ 구슬치기");
	gotoxy(26, 26);  printf("⑤ 징검다리");
	gotoxy(39, 26);  printf("⑥ 리듬게임");
}



int main() {


	while (1) {
		title();
		focus();
		PlaySound(NULL, 0, 0);
		int chk = 0;
		gotoxy(13, 18); printf("게임 선택 : \n");
		gotoxy(20, 18); scanf_s("%d", &chk);

		switch (chk)
		{
		case 1: main_mugunghwa(); break;
		case 2: main_dalgona();  break;
		case 3: main_pushpull(); break;
		case 4: main_marble(); break;
		case 5: main_jingumdari(); break;
		case 6: break;

		}
	}

	

		system("cls");
	return 0;
}