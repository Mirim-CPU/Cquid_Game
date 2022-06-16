/* keysetting.c */

#include "keysetting.h"


// 키를 설정하는 씬
void main_keysetting() {

	const int klp = 51; // keysetting left padding
	const int ktp = 10; // keysetting top padding
	const int gap = 5; // 키 공간 사이의 간격 (+1)
	const int boxWid = LINE * gap - 1; // 키설정 UI 가로 범위
	memset(key, 0, sizeof(key));

	setCursor(BLOCK);
	setColor1(white1);
	gotoxy1(klp + (boxWid - 7) / 2 - 1, ktp);
	puts("키 설정");
	for (int i = 0; i < LINE; i++) {
		gotoxy1(klp + i * gap, ktp + 2); wprintf(L"▽");
	}

	// 키 입력
	for (int i = 0; i < LINE; i++) {
		gotoxy1(klp + i * gap, ktp + 6); wprintf(L"↑");

		int k = 0;
		for (;;) {
			gotoxy1(klp + i * gap, ktp + 4);
			setCursor(BLOCK);
			k = _getch();

			BOOL able = TRUE;
			if (k == 0xE0 || k == 0) { k = _getch(); able = FALSE; } // 특수키(확장키) 불가능
			else if (k == 27) able = FALSE; // Esc 불가능
			else if (strchr("`-=[]\\;',./", k)) able = FALSE; // 기타 문자
			for (int j = 0; j < i; j++) if (k == key[j]) { able = FALSE; break; } // 중복된 키 불가능

			if (able)
				break;
		}
		setCursor(HIDE);

		if ('a' <= k && k <= 'z')
			k -= 'a' - 'A'; // 대소문자 통일

		switch (k) {
		case BACKSPACE:
			wcscpy_s(keyName[i], sizeof(keyName[i]) / sizeof(wchar_t), L"Bksp"); break;
		case enter:
			wcscpy_s(keyName[i], sizeof(keyName[i]) / sizeof(wchar_t), L"Entr"); break;
		case SPACE:
			wcscpy_s(keyName[i], sizeof(keyName[i]) / sizeof(wchar_t), L"Spce"); break;
		case TAB:
			wcscpy_s(keyName[i], sizeof(keyName[i]) / sizeof(wchar_t), L"Tab"); break;
		default:
			swprintf(keyName[i], sizeof(keyName[i]) / sizeof(wchar_t), L" %c ", k + 0xFEE0); break;
		}

		gotoxy1(klp + i * gap - 1, ktp + 4);
		setColor1(SKYBLUE);
		wprintf(L"%s", keyName[i]);
		setColor1(white1);

		key[i] = k;

		gotoxy1(klp + i * gap, ktp + 2); wprintf(L"▼");
		gotoxy1(klp + i * gap, ktp + 6); wprintf(L"　");
	}

	// 깜빡깜빡
	Sleep(180);
	for (int r = 0; r < 2; r++) {
		setColor1(white1);
		for (int i = 0; i < LINE; i++) {
			gotoxy1(klp + i * gap - 1, ktp + 4); wprintf(L" ― ");
		}
		Sleep(110);

		setColor1(SKYBLUE);
		for (int i = 0; i < LINE; i++) {
			gotoxy1(klp + i * gap - 1, ktp + 4); wprintf(L"%s", keyName[i]);
		}
		Sleep(110);
	}
	Sleep(400);

	// 클리어
	for (int i = 0; i < 6; i++) {
		gotoxy1(klp - 1, ktp + i);
		for (int j = 0; j < boxWid; j++) {
			_putch(' ');
		}
	}
}
