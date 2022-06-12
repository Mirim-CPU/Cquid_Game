/* gameplay.c */

#include "gameplay.h"


// 게임을 플레이하는 씬
void main_gameplay(char* _mapName) {
	mapName = _mapName;

	init();

	if (readMap() == -1) {
		system("cls");
		gotoxy1(1, 1);
		puts("맵 파일이 존재하지 않거나 맵을 열 수 없습니다.");
		Sleep(1000);
		return;
	}

	initBgm();
	drawScreen();
	countdown();
	updateUI(0);

	while (!gameEnd && !quit) {
		removingJudgeTxt();
		keyInput();
		fallingNote();
		// 순서는 상관 없지만 keyInput 다음에 fallingNote가 오도록 하세요 (quit 때문)
	}

	clearBuffer();
	if (!quit) {
		showStats();
		while (!_kbhit()) removingJudgeTxt();
	}

	playBgm(3);
	free(mapDir);
	for (int i = 0; i < mapLength; i++) free(map[i]); free(map);
}


// 변수 초기화 + BGM 준비 + cls
void init()
{
	system("cls");
	gotoxy1(glp + LINE * NOTETHK / 2 - 5, gtp + HEI / 2 - 1);
	printf("Loading...");

	mapIndex = 0;
	paused = FALSE;
	songPlayed = FALSE;
	gameEnd = FALSE;
	quit = FALSE;
	score = 0;
	combo = 0;
	accuracy = 100;
	noteCount = 0;
	pauseTimer = 0;
	memset(note, x, sizeof(note));
	memset(shouldRemove, FALSE, LINE);
	memset(isPressed, FALSE, LINE);
}

// 노트 맵 파일을 읽어서 note에 저장한다.
int readMap() {
	FILE* f;

	// 맵 폴더 위치 설정 (maps/mapName/)
	const int mapDirSize = (int)strlen(mapFolder) + 1 + (int)strlen(mapName) + 1 + 1;
	mapDir = malloc(mapDirSize);
	sprintf_s(mapDir, mapDirSize, "%s/%s/", mapFolder, mapName);

	// info.json 경로 설정 (maps/mapName/info.json)
	const char infoStr[] = "info.json";
	const int infoPathSize = mapDirSize + (int)strlen(infoStr);
	char* infoPath = malloc(infoPathSize);
	sprintf_s(infoPath, infoPathSize, "%s%s", mapDir, infoStr);

	// info.json 객체 생성
	JSON_Value* jsonValue = json_parse_file(infoPath);
	if (jsonValue == NULL) return -1;
	mapInfo = json_value_get_object(jsonValue);

	// 맵 파일 경로 설정 (maps/mapName/mapName.txt)
	const char* noteFile = json_object_get_string(mapInfo, "mapFile");
	const int notePathSize = mapDirSize + (int)strlen(noteFile);
	char* notePath = malloc(notePathSize);
	if (notePath == NULL) return -1;
	sprintf_s(notePath, notePathSize, "%s%s", mapDir, noteFile);

	// 맵 정보 읽기
	mapLength = (int)json_object_get_number(mapInfo, "mapLength");
	FALLSPEED = (int)json_object_get_number(mapInfo, "fallSpeed");

	if (FALLSPEED == 0) { // FALLSPEED를 명시하지 않았을 경우 BPM으로부터 추출 (16비트 기준)
		const double bpm = (int)json_object_get_number(mapInfo, "bpm");
		if (bpm == 0)
			FALLSPEED = 150; // 기본값
		else
			FALLSPEED = (int)round(60 / bpm / 4 * 1000);
	}

	// 노트 읽어서 map에 넣기
	map = malloc(mapLength * sizeof(char*));
	if (map == NULL) return -1;
	fopen_s(&f, notePath, "r");
	if (f == NULL) return -1;

	// 한 줄씩 읽기
	char* line;
	for (int i = 0; i < mapLength; i++) {
		line = malloc(LINE * sizeof(char));
		if (line == NULL) return -1;
		for (int j = 0; j < LINE; j++) {
			line[j] = fgetc(f);
		}
		map[i] = line;

		fgetc(f); // '\n'
	}

	// 정리
	fclose(f);
	free(infoPath); free(notePath);
	return 0;
}

// 음악 재생 준비
void initBgm() {
	// 음악 파일 경로 제작 ("maps/mapName/*.*")
	const char* bgmName = json_object_get_string(mapInfo, "songFile");
	if (bgmName == NULL) bgmName = "";
	const int pathSize = (int)strlen(mapDir) + (int)strlen(bgmName) + 1;
	char* bgmPath = malloc(pathSize);
	if (bgmPath == NULL) return;
	sprintf_s(bgmPath, pathSize, "%s%s", mapDir, bgmName);

	// wide char로 변환
	const int bgmPathWSize = MultiByteToWideChar(CP_ACP, 0, bgmPath, -1, NULL, 0);
	wchar_t* bgmPathW = malloc(bgmPathWSize * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, bgmPath, (int)strlen(bgmPath) + 1, bgmPathW, bgmPathWSize);

	// 음악 로드
	openBgm.lpstrElementName = bgmPathW;
	openBgm.lpstrDeviceType = L"mpegvideo";
	mciSendCommandW(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)(LPVOID)&openBgm); // 음악 열기
	dwID = openBgm.wDeviceID;
	mciSendCommandW(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)(LPVOID)&openBgm); // 음악 재생
	playBgm(1); // 바로 일시정지

	free(bgmPath);
}


// 화면 맵을 그린다.
void drawScreen() {

	// 박스
	setColor1(gray1);
	for (int i = 0; i <= HEI; i++) {
		gotoxy1(glp - 1, gtp + i);

		_putch('|');

		for (int j = 0; j < LINE * NOTETHK; j++) {
			if (i == HEI - 2) {
				setColor1(white1);
				wprintf(L"□"); j++; // 판정선
				setColor1(gray1);
			}
			else if (i == HEI) {
				_putch('^'); // 데드라인
			}
			else {
				_putch(' '); // 노트 있는 빈칸
			}
		}

		_putch('|');
	}

	// 키
	setColor1(SKYBLUE);
	for (int i = 0; i < LINE; i++) {
		gotoxy1(glp + i * NOTETHK + 1, gtp + HEI + 2);
		wprintf(L"%s", keyName[i]);
	}

	// 곡 제목
	setColor1(yellow1);
	gotoxy1(glp - 6 - (int)strlen(mapName), gtp + 1);
	printf("< %s >", mapName);
}

// 카운트다운
void countdown() {
	for (int i = 3; i >= 1; i--) {
		gotoxy1(glp + LINE * NOTETHK / 2 - 1, gtp + HEI / 2 - 1); // 맵 중앙
		wprintf(L"%c", i + '0' + 0xFEE0);
		Sleep(500);
	}

	gotoxy1(glp + LINE * NOTETHK / 2 - 3, gtp + HEI / 2 - 1);
	printf("Start!");
	Sleep(500);

	// 키
	gotoxy1(glp + 1, gtp + HEI + 2);
	for (int i = 0; i < LINE * NOTETHK; i++) {
		_putch(' ');
	}

	clearBuffer();
}


// 화면에 있는 모든 노트를 한 칸씩 아래로 이동시킨다. (스레드)
// 노트를 만들고, 화면 밖으로 나가면 없앤다.
void fallingNote() {
	static clock_t timer = 0;
	if (timer == 0) timer = clock();
	static clock_t runtime = 0;
	if (runtime == 0) runtime = FALLSPEED;

	// 모든 노트가 만들어지고 좀 있다가 게임을 종료시키기 위한 타이머
	static clock_t endTimer = 0;
	static BOOL end = FALSE;

	if (quit) {
		timer = 0;
		runtime = 0;
		return;
	}

	if (clock() - (timer + pauseTimer) >= runtime) {

		// miss 노트 검사
		for (int i = 0; i < LINE; i++) {
			if (note[HEI - 1][i] == N) {
				hitNote(i, -1);
			}
		}

		// 밑으로 한 칸씩 내리기
		for (int i = 1; i < HEI; i++) {
			for (int j = 0; j < LINE; j++) {
				note[HEI - i][j] = note[HEI - (i + 1)][j];

				// 노트가 처음 판정선에 닿았을 때 BGM 재생
				if (!songPlayed && i == 2 + json_object_get_number(mapInfo, "offset") && note[HEI - i][j] == N) {
					playBgm(0);
					songPlayed = TRUE;
				}
			}
		}

		// 맨 윗 줄에 새로 노트 추가
		if (mapIndex < mapLength) {
			for (int i = 0; i < LINE; i++) {
				note[0][i] = map[mapIndex][i];
			}
			mapIndex++;

			// 맵의 마지막 노트를 만들면 좀 있다 게임 종료
			if (mapIndex == mapLength) {
				end = TRUE;
				endTimer = clock();
			}
		}

		// 추가할 노트가 없으면 빈칸
		else {
			for (int i = 0; i < LINE; i++) {
				note[0][i] = x;
			}
		}

		// 화면 업데이트
		showNotes();

		runtime += FALLSPEED;
	}

	// 맵의 마지막 노트를 만들면 좀 있다 게임 종료
	if (end) {
		if (clock() - (endTimer + pauseTimer) >= FALLSPEED * HEI + 1000) {
			timer = 0;
			runtime = 0;
			gameEnd = TRUE;
			end = FALSE;
		}
	}
}

// 노트 + 맵을 콘솔 창에 출력한다.
void showNotes() {

	for (int i = 0; i < HEI; i++) {
		gotoxy1(glp, gtp + i);

		for (int j = 0; j < LINE; j++) {
			for (int k = 0; k < NOTETHK / 2; k++) {

				if (note[i][j] == N) { // 노트
					setColor1(green1);
					wprintf(L"■");
				}

				else {
					if (i == HEI - 2) { // 판정선
						setColor1(white1);
						wprintf(L"%c", isPressed[j] ? L'▣' : L'□');
					}

					else { // 빈칸
						wprintf(L"　");
					}
				}
			}
		}
	}
}

// 키보드 입력을 감지한다.
void keyInput() {

	if (_kbhit()) {

		// 노트 키
		for (int i = 0; i < LINE; i++) {
			if (GetAsyncKeyState(key[i])) {
				if (!isPressed[i]) { // 누름

					press(i);
					isPressed[i] = TRUE;

					setColor1(white1);
					gotoxy1(glp + i * NOTETHK, gtp + HEI - 2);
					for (int j = 0; j < NOTETHK / 2; j++)
						wprintf(L"▣");
				}
			}

			else if (isPressed[i]) { // 뗌

				setColor1(white1);
				gotoxy1(glp + i * NOTETHK, gtp + HEI - 2);
				for (int j = 0; j < NOTETHK / 2; j++)
					if (note[HEI - 2][i] == x)
						wprintf(L"□");

				isPressed[i] = FALSE;
			}
		}

		// ESC 누르면 일시정지
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			pause();
		}
	}
}

// key가 눌렸을 때 호출된다.
void press(int line) {
	for (int i = 1; i <= 4; i++) {
		if (note[HEI - i][line] == N) {
			hitNote(line, i);
			return;
		}
	}
}

// 해당 line의 노트를 친다.
// judgement :
//   1 -> LATE
//   2 -> GOOD
//   3 -> FAST
//   4 -> miss(TOOFAST)
//  -1 -> miss(TOOLATE)
void hitNote(int line, int judgement) {

	// 해당 노트 삭제
	if (judgement != -1) note[HEI - judgement][line] = x;
	noteCount++;


	// 점수, 정확도
	switch (judgement) {
	case 1: // LATE
	case 3: // FAST (200점에 66%)
		score += 200 + (int)round(200 * combo / 300.0);
		accuracy = (accuracy * (noteCount - 1) + 200 / 3.0) / noteCount;
		updateUI(+1);
		break;
	case 2: // GOOD (300점에 100%)
		score += 300 + (int)round(300 * combo / 200.0);
		accuracy = (accuracy * (noteCount - 1) + 100) / noteCount;
		updateUI(+1);
		break;
	case 4:
	case -1: // miss (0점에 0%)
		score += 0;
		accuracy = (accuracy * (noteCount - 1) + 0) / noteCount;
		updateUI(-1);
		break;
	}


	// 판정 텍스트
	gotoxy1(glp + line * NOTETHK + 1, gtp + HEI + 1);
	switch (judgement) {
	case 1:          setColor1(DARK_YELLOW); puts("LATE"); break;
	case 2:          setColor1(DARK_GREEN);  puts("GOOD"); break;
	case 3:          setColor1(DARK_YELLOW); puts("FAST"); break;
	case 4: case -1: setColor1(DARK_GRAY); puts("miss"); break;
	}
	shouldRemove[line] = 1;


	// 화면 업데이트
	showNotes();
}

// 노트를 치고 1초 이후에 판정 텍스트 제거 (스레드)
void removingJudgeTxt() {
	static clock_t timer[LINE] = { 0, };

	for (int i = 0; i < LINE; i++) {
		if (shouldRemove[i] == 1) {
			timer[i] = clock();
			shouldRemove[i] = 2;
		}

		if (shouldRemove[i] == 2 && clock() - timer[i] >= 1000) {
			gotoxy1(glp + i * NOTETHK + 1, gtp + HEI + 1);
			puts("    ");
			shouldRemove[i] = 0;
		}
	}

}


// 일시정지
void pause() {
	// 정지
	if (!paused) {
		paused = TRUE;
		clock_t pauseStart = clock();
		playBgm(1);

		// 창 클리어
		drawScreen();
		setColor1(gray1);
		gotoxy1(glp + LINE * NOTETHK / 2 - 3, gtp + HEI / 2 - 1); puts("Paused");
		gotoxy1(glp, gtp + HEI / 2 + 1); puts("ESC를 눌러서 계속 플레이");
		gotoxy1(glp, gtp + HEI / 2 + 2); puts("Q를 눌러서 맵 나가기");

		// ESC를 누를 때까지 대기
		while (GetAsyncKeyState(VK_ESCAPE)) removingJudgeTxt();
		while (!GetAsyncKeyState(VK_ESCAPE)) {
			if (GetAsyncKeyState('Q')) {
				quit = TRUE;
				return;
			}
			removingJudgeTxt();
		}

		paused = FALSE;
		drawScreen();
		countdown();
		playBgm(2);
		pauseTimer += clock() - pauseStart; // 일시정지 중이었던 시간을 빼줌
	}
}


// BGM을 재생한다.
// 0: 재생, 1: 일시정지, 2: 일시정지 해제, 3: 정지
void playBgm(int action) {

	switch (action) {
	case 0: // 음악 재생
		mciSendCommandW(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)(LPVOID)&openBgm);
		break;

	case 1: // 음악 일시정지
		mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD_PTR)(LPVOID)&openBgm);
		break;

	case 2: // 음악 일시정지 해제
		mciSendCommandW(dwID, MCI_RESUME, MCI_NOTIFY, (DWORD_PTR)(LPVOID)&openBgm);
		break;

	case 3: // 음악 정지
		mciSendCommandW(dwID, MCI_STOP, MCI_NOTIFY, (DWORD_PTR)(LPVOID)&openBgm); // 음악 정지
		mciSendCommandW(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)(LPVOID)NULL); //음원 재생 위치를 처음으로 초기화
		break;
	}
}

// 점수 & 콤보 UI 업데이트
// 1: 콤보 증가, -1: 콤보 초기화
void updateUI(int comboPlus) {

	// 점수
	gotoxy1(glp + LINE * NOTETHK + 2, gtp + 1);
	setColor1(gray1);  printf("Score: ");
	setColor1(green1); printf("%d", score);

	// 콤보
	if (comboPlus == 1)
		combo++;
	else if (comboPlus == -1)
		combo = 0;
	gotoxy1(glp + LINE * NOTETHK + 2, gtp + 3);
	setColor1(gray1);  printf("Combo: ");
	setColor1(white1); printf("%-4d", combo);

	// 정확도
	gotoxy1(glp + LINE * NOTETHK + 2, gtp + 5);
	setColor1(gray1);   printf("Accuracy: ");
	setColor1(yellow1); printf("%-3.3f%% ", accuracy);
}


// 기록 띄우기
void showStats() {
	gotoxy1(glp + 1, gtp + HEI / 2 - 3);
	setColor1(yellow1); printf("%s", mapName);
	setColor1(gray1);   printf(" 플레이 결과");
	gotoxy1(glp + 1, gtp + HEI / 2 - 1);
	setColor1(gray1);  printf("점수: ");
	setColor1(green1); printf("%d", score);
	gotoxy1(glp + 1, gtp + HEI / 2);
	setColor1(gray1);   printf("정확도: ");
	setColor1(yellow1); printf("%.3f%%", accuracy);

	setColor1(gray1);
	gotoxy1(glp + 1, gtp + HEI / 2 + 2);
	printf("메인 화면으로 돌아가려면");
	gotoxy1(glp + 1, gtp + HEI / 2 + 3);
	printf("아무 키나 누르세요");

	// 점수 저장
	JSON_Value* rootValue = json_parse_file(statsPath);
	JSON_Object* highScore = json_value_get_object(rootValue);
	if (json_object_get_number(highScore, mapName) < score) { // 하이 스코어를 넘으면 갱신
		json_object_set_number(highScore, mapName, score);
		json_serialize_to_file_pretty(rootValue, statsPath);
	}
}
