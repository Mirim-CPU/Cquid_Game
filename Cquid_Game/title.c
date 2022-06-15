/* title.c */

#include "title.h"
#include "modules.h"


// Å¸ÀÌÆ² È­¸é ¾À
void main_title() {

	system("cls");

	setColor1(MINT);
	for (int i = 0; i < titleHei; i++) {
		gotoxy1(SCREEN_WIDTH / 2 - titleWid / 2, 4 + i);
		puts(rhythm_title[i]);
	}

	print_by_name("½ÉÀÌÁø");

	/*setColor1(yellow1);
	const wchar_t title[] = L"Developed by ½ÉÀÌÁø";
	gotoxy1((SCREEN_WIDTH - (int)wcslen(title)) / 2, 4 + titleHei + 1);
	wprintf(L"%s", title);*/

	setColor(white1);
	int x = 5;
	int y = 13;
	print_auto_y(&x, &y, "    ¡ø_¡¬");
	print_auto_y(&x, &y, "	¡¬¡¬ ¥Ë£ß¥Ë");
	print_auto_y(&x, &y, "	  ¡¬(¢§¥ø¢§)    µÒÄ©");
	print_auto_y(&x, &y, "	      > ¡Ò`");
	print_auto_y(&x, &y, "	      / ªØ¡¬");
	print_auto_y(&x, &y, "	     /¡¡/¡¬¡¬");
	print_auto_y(&x, &y, "	     /  «Î¡¡¡¬_ªÄ");
	print_auto_y(&x, &y, "	    /  /");
	print_auto_y(&x, &y, "µÒÄ©     /¡¡/|");
	print_auto_y(&x, &y, "	  (   (`");
	print_auto_y(&x, &y, "	  | |¡¢¡¬");
	print_auto_y(&x, &y, "	  | | ¡¬ ¡Ò)");
	print_auto_y(&x, &y, "	  | |¡¡¡¡) /");
	print_auto_y(&x, &y, "	 «Î )¡¡¡¡L/");
	print_auto_y(&x, &y, "      (___/     µÒÄ©");

	setColor(RED);
	x = 28;
	y = 15;
	print_auto_y(&x, &y, " £þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ");
	print_auto_y(&x, &y, "|¡¡°ÔÀÓ ¹ß»ý!¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ ¡¡[£­][Ï¢][¡¿] |");
	print_auto_y(&x, &y, "|£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ|");
	print_auto_y(&x, &y, "|¡¡¼¼»ó¿¡¼­ Á¤¸» ¾î·Á¿î ¸®µë°ÔÀÓÀ» ½ÇÇàÇÏ¼Ì½À´Ï´Ù! ¡¡¡¡¡¡        |");
	print_auto_y(&x, &y, "|¡¡Á¤¸»ÀÎ°¡¿ä?¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡ ¡¡|");
	print_auto_y(&x, &y, "|¡¡¡¡¡¡¡¡£ß£ß£ß£ß£ß¡¡¡¡¡¡¡¡£ß£ß£ß£ß£ß£ß¡¡¡¡¡¡¡¡£ß£ß£ß£ß£ß¡¡¡¡¡¡  |");
	print_auto_y(&x, &y, "| ¡¡¡¡¡¡£ü¿¹¡¡¡¡   |¡¡¡¡¡¡£ü¾Æ¸¶µµ?¡¡¡¡£ü ¡¡ ¡¡|¿¹¡¡ ¡¡ |¡¡  ¡¡  |");
	print_auto_y(&x, &y, "|¡¡¡¡¡¡¡¡£þ£þ£þ£þ£þ¡¡¡¡¡¡¡¡£þ£þ£þ£þ£þ£þ¡¡¡¡¡¡¡¡£þ£þ£þ£þ£þ¡¡¡¡¡¡  |");
	print_auto_y(&x, &y, "£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ");
	
	setColor(YELLOW);
	x = 43;
	y = 25;
	print_auto_y(&x, &y, "[ ½ÃÀÛÇÏ·Á¸é ¾Æ¹« Å°¸¦ ´©¸£½Ê½Ã¿À ]");


	setColor(WHITE);
	x = 100;
	y = 15;
	print_auto_y(&x, &y, " ¡ü,,¡ü !!!!");
	print_auto_y(&x, &y, "( '¥ø' )ªÄ");
	print_auto_y(&x, &y, "£¨m9  ¡¬ ");
	print_auto_y(&x, &y, "¡¡ ¡¬¡¡ ¡¬ ");
	print_auto_y(&x, &y, "¡¡ ¡¡) ) ¡¬");
	print_auto_y(&x, &y, "¡¡  £¯£¯¡¬ ¡¬");
	print_auto_y(&x, &y, "¡¡ (£ß£© (£ß)");


	gotoxy1(SCREEN_WIDTH / 2, 4 + titleHei + 5);
	setCursor(UNDERBAR);
	clearBuffer();

	int _ = _getch();
}
