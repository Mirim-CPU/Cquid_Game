#include <stdio.h>   //표준입출력헤더
#include <stdlib.h>   //malloc, free 등
#include <Windows.h>//windows console api 헤더
#include <time.h>   //랜덤 시드용 time 함수 헤더
#include <conio.h>   //gotoxyD에서 사용할 api 헤더
#include "dalgona.h"

#define MAGIC_KEY 224
#define FIELD_WIDTH 65   //필드가로길이
#define FIELD_HEIGHT 25   //필드세로길이
#define LEFT 75         //키보드 좌 화살표의 char값
#define RIGHT 77      //키보드 우
#define UP 72         //키보드 위
#define DOWN 80         //지보드 아래
#define ITEM_GOLD 101   //골드 아이템 인디케이터
#define ITEM_EXP 102   //경험치 아이템 인디케이터
#define LEFT_MARGIN 25   //화면왼쪽마진(공백)
#define TOP_MARGIN 3   //화면 상단마진(공백)
#define DELAYTIME 200   //Sleep함수에 들어갈 x/1000 초 (지렁이속도/원래값200)ㄴ
#define TIMER 40.0   //Sleep함수에 들어갈 x/1000 초

#define SHAPES_SIZE 2
#define SHAPES_CIRCLE 54
#define SHAPES_ANGLE 40
#define SHAPES_SQUARE 56

int inputkey = 0;
int mode = 1;    // 모양에 따른 배열길이 
char* mshape = 'o';
clock_t start;   // 타이머 게임시작시간 
double limit = TIMER;   // 남은 시간
int(*shapes)[2];    // 모양 그릴 위치배열

void printstart();
void playgame();
void selectShape();
void timerlimit();

enum MENU
{
    GAMESTART = 0,
    EXIT
};

//지렁이를 구현할 이중연결리스트 구조체
#pragma pack(push,1)
typedef struct _WORM
{
    int x;   //x좌표
    int y;   //y좌표
    char direction;   //진행방향
    struct _WORM* next;   //다음노드주소
    struct _WORM* before;//이전노드주소
}WORM, * pWORM;

//커서를 일정 좌표로 이동
void gotoxyD(int x, int y)
{
    COORD Pos;
    Pos.X = x + LEFT_MARGIN;//가로세로 비율을 맞추기 위해서 가로의 좌표는 2배
    Pos.Y = y + TOP_MARGIN;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// 첫화면 시작종료 선택 커서 함수
enum MENU gamemenu() {
    int y = 0;
    while (1) {
        printstart();

        if (y <= 0)
        {
            y = 0;
        }
        else if (y >= 4)
        {
            y = 2;
        }

        gotoxy(53, 18 + y);
        printf(">");

        inputkey = _getch();

        if (inputkey == MAGIC_KEY)
        {
            switch (_getch())
            {
            case UP:
                gotoxy(53, 18 + y);
                printf("  ");
                y = y - 2;
                break;
            case DOWN:
                gotoxy(53, 18 + y);
                printf("  ");
                y = y + 2;
                break;
            }
        }
        else if (inputkey == 13)
        {
            switch (y)
            {
            case 0:
                return GAMESTART;
            case 2:
                return EXIT;
            }
        }
    }
}

// 게임 시작화면 
void printstart() {
    int x = 40;
    int y = 11;
    system("cls");
    gotoxy(34, 5);
    printf("△￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣○");
    gotoxy(34, 7);
    printf("|                   설탕 뽑기 게임                   |");
    gotoxy(34, 9);
    printf("|    각자 자신이 원하는 모양 중 하나를 선택합니다    |");
    gotoxy(34, 11);
    printf("|     먹이를 먹으며 제한시간 안에 살아가면 됩니다    |");
    gotoxy(34, 13);
    printf("|      먹이를 다 먹지못하면 끝나는 게임입니다        |");
    gotoxy(34, 15);
    printf("□＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿☆");

    x = 100;
    y = 2;
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|_∧");
    print_auto_y(&x, &y, "|□|ㅁ0` )");
    print_auto_y(&x, &y, "|□|⊂ ）");
    print_auto_y(&x, &y, "|□|L");
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|");
    print_auto_y(&x, &y, "|□|");


    x = 45;
    y = 21;
    print_auto_y(&x, &y, "　　ｏ");
    print_auto_y(&x, &y, "　°");
    print_auto_y(&x, &y, "　┳┳   ∩∩");
    print_auto_y(&x, &y, "　┃┃ (0 ㅁ 0)");
    print_auto_y(&x, &y, "┏┻┻┷━Ｏ┏┷┓┏┷┓");
    print_auto_y(&x, &y, "┃ 　　  　 ┠┨○┠┨○┃");
    print_auto_y(&x, &y, "┗◎━━◎┛┗◎┛┗◎┛");
    print_auto_y(&x, &y, "-----------------------------------------------------");

    x = 1;
    y = 20;
    print_auto_y(&x, &y, "            ,===,==, ");
    print_auto_y(&x, &y, "           ||__|＿|| ");
    print_auto_y(&x, &y, "       l|＿＼ ＼＼ ");
    print_auto_y(&x, &y, "      |□|＼＼ 　∧--∧ ");
    print_auto_y(&x, &y, "      |口|　＼＼(   0ㅁ0) ");
    print_auto_y(&x, &y, "      |口|　　＼⊂ 　 つ ");
    print_auto_y(&x, &y, "      |口|　 　 ＼＼つつ＼ ");
    print_auto_y(&x, &y, "      |口|　　　　＼| 　＼| ");
    print_auto_y(&x, &y, "     ------------------------------------------------");

    gotoxy(56, 18);
    printf("게임 시작");

    gotoxy(56, 20);
    printf("게임 종료");

    print_by_name("전유리 고에스더 김민주");
}

// 게임시작 시작종료처리 함수
void main_dalgona() {
    system("cls");
    PlaySound(TEXT("./sound/dalgona.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    while (1) {
        switch (gamemenu()) {
        case GAMESTART:
            selectShape();
            //break;

        case EXIT:
            system("cls");
            //PlaySound(NULL, 0, 0);
            main();
            break;
        }
    }
}

// 게임 모양선택 함수
void printShape() {
    int x = 10;
    int y = 20;
    system("cls");
    gotoxy(34, 5);
    printf("△￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣  ￣○");
    gotoxy(34, 7);
    printf("|     지금 즉시 하나를 선택해 이동하시기바랍니다.    |");
    //gotoxy(45, 9);
    //printf("지금부터 게임을 시작하겠습니다");
    gotoxy(34, 9);
    printf("|    엔터를 누르면 타이머와 함께 게임을 시작합니다.  |");
    gotoxy(34, 11);
    printf("□＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿  ＿☆");


    print_auto_y(&x, &y, "            ○○○○    ");
    print_auto_y(&x, &y, "          ○        ○");
    print_auto_y(&x, &y, "	   ○          ○");
    print_auto_y(&x, &y, "	    ○        ○");
    print_auto_y(&x, &y, "	      ○○○○   ");
    print_auto_y(&x, &y, "	             ");
    print_auto_y(&x, &y, "	    ");
    print_auto_y(&x, &y, "	  ");
    print_auto_y(&x, &y, "     ");

    x = 40;
    y = 20;
    print_auto_y(&x, &y, "             △     ");
    print_auto_y(&x, &y, "           △   △");
    print_auto_y(&x, &y, "	  △      △");
    print_auto_y(&x, &y, "	 △         △");
    print_auto_y(&x, &y, "	△ △ △ △  △   ");
    print_auto_y(&x, &y, "	            ");
    print_auto_y(&x, &y, "	    ");
    print_auto_y(&x, &y, "	  ");
    print_auto_y(&x, &y, "     ");

    x = 70;
    y = 20;
    print_auto_y(&x, &y, "         □□□□□□□");
    print_auto_y(&x, &y, "         □          □");
    print_auto_y(&x, &y, "	       □          □");
    print_auto_y(&x, &y, "	       □          □");
    print_auto_y(&x, &y, "	       □          □   ");
    print_auto_y(&x, &y, "	       □□□□□□□    ");
    print_auto_y(&x, &y, "	  ");
    print_auto_y(&x, &y, "     ");
}
void selectShape() {
    system("cls");
    int kx = 24;
    int ky = 15;
    int gap = 30;

    while (1) {
        printShape();
        if (kx > 24 + gap * 2) {
            kx = 24 + gap * 2;
        }
        else if (kx < 20) {
            kx = 20;
        }
        gotoxy(kx, ky);
        printf("　∧,,∧");
        gotoxy(kx, ky + 1);
        printf("(-＞ㅁ0-)");
        gotoxy(kx, ky + 2);
        printf("　(O O)");
        gotoxy(kx, ky + 3);
        printf("　 T-T");

        inputkey = _getch();
        if (inputkey == MAGIC_KEY) // 방향키
        {
            switch (_getch())
            {
            case LEFT:
                gotoxy(kx, ky);
                printf("  ");
                gotoxy(kx, ky + 1);
                printf("    ");
                gotoxy(kx, ky + 2);
                printf("   ");
                kx -= gap;
                break;
            case RIGHT:
                gotoxy(kx, ky);
                printf("  ");
                gotoxy(kx, ky + 1);
                printf("    ");
                gotoxy(kx, ky + 2);
                printf("   ");
                kx += gap;
                break;
            }
        }
        else if (inputkey == 13)   // 엔터
        {
            switch (kx)
            {
            case 24:
                mode = modeSize(1);
                shapes = shape1();
                mshape = "o";
                break;
            case 24 + 30:
                mode = modeSize(2);
                shapes = shape2();
                mshape = "△";
                break;
            case 24 + 30 * 2:
                mode = modeSize(3);
                shapes = shape3();
                mshape = "□";
                break;
            }
            gotoxy(0, 0);
            for (int i = 0; i < 4; i++) {
                printf("%d\n", shapes[i][0]);
            }
            playgame();
            return 0;
        }
    }
}


//게임영역출력
void PrintField()
{
    for (int i = 1; i < FIELD_WIDTH; i++)
    {
        gotoxyD(i, 0);
        printf("─");
        gotoxyD(i, FIELD_HEIGHT);
        printf("─");
    }

    for (int i = 1; i < FIELD_HEIGHT; i++)
    {
        gotoxyD(0, i);
        printf("│");
        gotoxyD(FIELD_WIDTH, i);
        printf("│");
    }
    gotoxyD(0, 0);
    printf("┌");
    gotoxyD(0, FIELD_HEIGHT);
    printf("└");
    gotoxyD(FIELD_WIDTH, 0);
    printf("┐");
    gotoxyD(FIELD_WIDTH, FIELD_HEIGHT);
    printf("┘");
}

//지렁이를 늘리는 함수(이중연결리스트의 테일쪽에 노드 추가)
void AddWorm(pWORM wormTailNode)
{
    pWORM newNode = malloc(sizeof(WORM));
    pWORM temp = wormTailNode->next;

    //새 노드의 주솟값 이어주기;
    newNode->before = wormTailNode;
    newNode->next = wormTailNode->next;
    wormTailNode->next = newNode;
    newNode->next->before = newNode;
    newNode->direction = temp->direction;
    newNode->x = temp->x;
    newNode->y = temp->y;
    switch (temp->direction)
    {
    case LEFT:
        newNode->x = newNode->x + 1;
        break;
    case RIGHT:
        newNode->x = newNode->x - 1;
        break;
    case UP:
        newNode->y = newNode->y + 1;
        break;
    case DOWN:
        newNode->y = newNode->y - 1;
        break;
    default:
        break;
    }


}

//연결리스트를 받아서 지렁이 출력
void PrintWorm(pWORM wormTailNode, pWORM wormHeadNode)
{
    pWORM curr = wormTailNode->next;
    while (curr != wormHeadNode)
    {
        gotoxyD(curr->x, curr->y);
        printf("@");
        curr = curr->next;
    }
}

//게임점수 출력
void PrintScore(int score, int left)
{
    gotoxyD(FIELD_WIDTH + 3, 3);
    printf("%s 잘린달고나조각 : %d개", mshape, score);
    gotoxyD(FIELD_WIDTH + 3, 5);
    printf("%s 남은달고나조각 : %d개", mshape, left);
    gotoxy(FIELD_WIDTH / 2 + 15, 29);
    printf("종료하려면 ESC를 누르시오");
}

//웜이 지나간 자리 지우기
void ClearWorm(int x, int y)
{
    if (x == x && y == y) {
        gotoxyD(x, y);
        printf(" ");
    }

    printf(" ");
}

//웜 움직이기 
void MoveWorm(pWORM wormTailNode, pWORM wormHeadNode)
{
    pWORM curr;

    curr = wormTailNode->next;
    while (curr != NULL && curr != wormHeadNode->before)
    {
        curr->x = curr->next->x;
        curr->y = curr->next->y;
        curr = curr->next;
    }
    curr = wormHeadNode->before;
    if (curr->direction == LEFT)
    {
        curr->x--;
    }
    else if (curr->direction == RIGHT)
    {
        curr->x++;
    }
    else if (curr->direction == UP)
    {
        curr->y--;
    }
    else if (curr->direction == DOWN)
    {
        curr->y++;
    }
}


//웜 리스트에 할당된 메모리를 순차로 해제
void FreeWormList(pWORM wormTailNode)
{
    pWORM curr;
    pWORM temp;
    curr = wormTailNode;
    while (curr != NULL)
    {
        temp = curr->next;
        free(curr);
        curr = temp;
    }
}

//아이템(골뱅이)와 웜의 헤드가 만났는지 검사, 
// left, result로 남은개수와 먹은개수 넘겨줌
int CheckItemHit(pWORM wormHeadPointer, int* left, int* result)
{
    for (int i = 0; i < mode; i++) {
        if (wormHeadPointer->x == (shapes[i][0] - LEFT_MARGIN) && wormHeadPointer->y == (shapes[i][1] - TOP_MARGIN)) {
            *result += 1;   // 먹은개수 업데이트
            *left -= 1;     // 남은개수 업데이트
            shapes[i][0] = 0;
            continue;
        }
        if (shapes[i][0] > 0) {
            gotoxyD(shapes[i][0] - LEFT_MARGIN, shapes[i][1] - TOP_MARGIN);
            printf("o");
        }
    }

    return 1;
}

// 타이머
void timerlimit() {
    clock_t end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC; //초단위 변환
    limit = TIMER - time;
    gotoxy(FIELD_WIDTH / 2 + 20, 1);
    printf("[ 타이머 : %0.2lf ]\n", limit); //소수점 셋째 자리까지
    gotoxy(FIELD_WIDTH / 2 + 20, 2);
    printf("    ||      ||"); //소수점 셋째 자리까지
}

void playgame()
{
    pWORM wormHeadNode = malloc(sizeof(WORM));//이중연결리스트 헤드노드
    pWORM wormTailNode = malloc(sizeof(WORM));//이중연결리스트 테일노드
    pWORM addWorm = malloc(sizeof(WORM));//첫번째 웜몸통 

    wormHeadNode->next = NULL;
    wormHeadNode->before = addWorm;
    addWorm->next = wormHeadNode;
    addWorm->before = wormTailNode;
    addWorm->x = FIELD_WIDTH / 2;
    addWorm->y = FIELD_HEIGHT / 2;
    addWorm->direction = RIGHT;
    wormTailNode->next = addWorm;
    wormTailNode->before = NULL;

    //지렁이 게임시작 지렁이 생성
    for (int i = 9; i > 0; i--)
        AddWorm(wormTailNode);

    //웜의 머리를 가리키는 포인터
    pWORM wormHeadPointer = addWorm;

    int score = 0;         //최초점수
    char key;            //키입력받을 변수
    start = clock();   //시작 시간
    int left = mode;
    int result = 0;

    system("cls");   //화면지우고
    PrintField();   //필드 출력


    while (1)
    {
        //테스트용 출력부분
        //gotoxyD(-LEFT_MARGIN, 0);
        //PrintItemList(itemNode);
        timerlimit();
        if (_kbhit() != 0)
        {
            key = _getch();
            if (key == 27)  // esc키 누르면종료
            {
                printf("%c", key);
                break;
            }
            if (key == LEFT && wormHeadPointer->direction != RIGHT)
            {
                wormHeadPointer->direction = LEFT;
            }
            else if (key == RIGHT && wormHeadPointer->direction != LEFT)
            {
                wormHeadPointer->direction = RIGHT;
            }
            else if (key == UP && wormHeadPointer->direction != DOWN)
            {
                wormHeadPointer->direction = UP;
            }
            else if (key == DOWN && wormHeadPointer->direction != UP)
            {
                wormHeadPointer->direction = DOWN;
            }
        }

        //웜 지나간 자리 지우기
        ClearWorm(wormTailNode->next->x, wormTailNode->next->y);

        //웜 한칸씩 움직이기
        MoveWorm(wormTailNode, wormHeadNode);

        //벽에 부딛히면 게임오버
        if (wormHeadPointer->x == 0 || wormHeadPointer->x == FIELD_WIDTH || wormHeadPointer->y == 0 || wormHeadPointer->y == FIELD_HEIGHT)
        {
            system("cls");
            gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2);
            printf("벽에 부딛혔습니다. GAME OVER");
            Sleep(2000);
            break;
        }

        //시간 다돼면 종료
        if (limit <= 0.0) {
            system("cls");
            gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2);
            printf("%d", result);
            gotoxyD(FIELD_WIDTH / 2 - 7, FIELD_HEIGHT / 2);
            printf("만큼 뜯겨졌습니다");
            gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 - 2);
            printf("%d", left);
            gotoxyD(FIELD_WIDTH / 2 - 7, FIELD_HEIGHT / 2 - 2);
            printf("만큼 남았습니다");

            // Sleep(2000);
            // break;
            if (result <= 10)
            {
                //system("cls");
                gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 - 4);
                printf("10개도 뜯지 못했습니다. 따라서 사망");
                Sleep(2000);
                break;
            }
            if (result <= 20)
            {
                //system("cls");
                gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 - 4);
                printf("절반도 뜯지 못했습니다. 따라서 사망");
                Sleep(2000);
                break;
            }

            if (result <= 30)
            {
                //system("cls");
                gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 - 4);
                printf("절반정도 뜯었습니다. 그래도 사망");
                Sleep(2000);
                break;
            }
            if (result <= 40)
            {
                //system("cls");
                gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 - 4);
                printf("거의 다 뜯었는데.. 아깝게 사망 ");
                Sleep(2000);
                break;
            }
            if (result <= 50)
            {
                //system("cls");
                gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 - 4);
                printf("진짜 미세한 차이로 사망...");
                Sleep(2000);
                break;
            }




        }
        // 아이템 출력
        CheckItemHit(wormHeadPointer, &left, &result);
        score = result * 100;

        //아이템 다 먹으면 종료
        if (left <= 0)
        {
            system("cls");
            gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2);
            printf("△통과, 다음 게임으로 넘어갑니다☆");
            gotoxyD(FIELD_WIDTH / 2 - 10, FIELD_HEIGHT / 2 - 5);
            printf("○시간은 %0.2lf\n", limit);

            Sleep(2000);
            break;
        }

        PrintWorm(wormTailNode, wormHeadNode);
        PrintScore(result, left);
        Sleep(DELAYTIME);
    }
    FreeWormList(wormTailNode);
}


// shape ----------------------------------------

int(*shape1())[SHAPES_SIZE];
int(*shape2())[SHAPES_SIZE];
int(*shape3())[SHAPES_SIZE];
int modeSize(int);

int modeSize(int mode) {
    switch (mode)
    {
    case 1:
        return SHAPES_CIRCLE;
    case 2:
        return SHAPES_ANGLE;
    default:
        return SHAPES_SQUARE;
        break;
    }
}
int(*shape1())[SHAPES_SIZE] {
    static int shapes[SHAPES_CIRCLE][SHAPES_SIZE] = { 0 };
    shapes[0][0] = 43; shapes[0][1] = 7;
    shapes[1][0] = 45; shapes[1][1] = 7;
    shapes[2][0] = 47; shapes[2][1] = 7;
    shapes[3][0] = 49; shapes[3][1] = 7;
    shapes[4][0] = 51; shapes[4][1] = 7;
    shapes[5][0] = 53; shapes[5][1] = 7;
    shapes[6][0] = 55; shapes[6][1] = 7;
    shapes[7][0] = 57; shapes[7][1] = 7;
    shapes[8][0] = 59; shapes[8][1] = 7;
    shapes[9][0] = 61; shapes[9][1] = 7;
    shapes[10][0] = 63; shapes[10][1] = 7;
    shapes[11][0] = 65; shapes[11][1] = 7;
    shapes[12][0] = 67; shapes[12][1] = 7;
    shapes[13][0] = 69; shapes[13][1] = 7;
    shapes[14][0] = 41; shapes[14][1] = 8;
    shapes[15][0] = 71; shapes[15][1] = 8;
    shapes[16][0] = 39; shapes[16][1] = 9;
    shapes[17][0] = 73; shapes[17][1] = 9;
    shapes[18][0] = 37; shapes[18][1] = 10;
    shapes[19][0] = 75; shapes[19][1] = 10;
    shapes[20][0] = 35; shapes[20][1] = 11;
    shapes[21][0] = 77; shapes[21][1] = 11;
    shapes[22][0] = 35; shapes[22][1] = 12;
    shapes[23][0] = 77; shapes[23][1] = 12;
    shapes[24][0] = 35; shapes[24][1] = 13;
    shapes[25][0] = 77; shapes[25][1] = 13;
    shapes[26][0] = 35; shapes[26][1] = 14;
    shapes[27][0] = 77; shapes[27][1] = 14;
    shapes[28][0] = 35; shapes[28][1] = 15;
    shapes[29][0] = 77; shapes[29][1] = 15;
    shapes[30][0] = 35; shapes[30][1] = 16;
    shapes[31][0] = 77; shapes[31][1] = 16;
    shapes[32][0] = 35; shapes[32][1] = 17;
    shapes[33][0] = 77; shapes[33][1] = 17;
    shapes[34][0] = 37; shapes[34][1] = 18;
    shapes[35][0] = 75; shapes[35][1] = 18;
    shapes[36][0] = 39; shapes[36][1] = 19;
    shapes[37][0] = 73; shapes[37][1] = 19;
    shapes[38][0] = 41; shapes[38][1] = 20;
    shapes[39][0] = 43; shapes[39][1] = 20;
    shapes[40][0] = 45; shapes[40][1] = 20;
    shapes[41][0] = 47; shapes[41][1] = 20;
    shapes[42][0] = 49; shapes[42][1] = 20;
    shapes[43][0] = 51; shapes[43][1] = 20;
    shapes[44][0] = 53; shapes[44][1] = 20;
    shapes[45][0] = 55; shapes[45][1] = 20;
    shapes[46][0] = 57; shapes[46][1] = 20;
    shapes[47][0] = 59; shapes[47][1] = 20;
    shapes[48][0] = 61; shapes[48][1] = 20;
    shapes[49][0] = 63; shapes[49][1] = 20;
    shapes[50][0] = 65; shapes[50][1] = 20;
    shapes[51][0] = 67; shapes[51][1] = 20;
    shapes[52][0] = 69; shapes[52][1] = 20;
    shapes[53][0] = 71; shapes[53][1] = 20;

    return shapes;

}
int(*shape2())[SHAPES_SIZE] {
    static int shapes[SHAPES_ANGLE][SHAPES_SIZE] = { 0 };
    shapes[0][0] = 58; shapes[0][1] = 7;
    shapes[1][0] = 56; shapes[1][1] = 8;
    shapes[2][0] = 60; shapes[2][1] = 8;
    shapes[3][0] = 54; shapes[3][1] = 9;
    shapes[4][0] = 62; shapes[4][1] = 9;
    shapes[5][0] = 52; shapes[5][1] = 10;
    shapes[6][0] = 64; shapes[6][1] = 10;
    shapes[7][0] = 50; shapes[7][1] = 11;
    shapes[8][0] = 66; shapes[8][1] = 11;
    shapes[9][0] = 48; shapes[9][1] = 12;
    shapes[10][0] = 68; shapes[10][1] = 12;
    shapes[11][0] = 46; shapes[11][1] = 13;
    shapes[12][0] = 70; shapes[12][1] = 13;
    shapes[13][0] = 44; shapes[13][1] = 14;
    shapes[14][0] = 72; shapes[14][1] = 14;
    shapes[15][0] = 42; shapes[15][1] = 15;
    shapes[16][0] = 74; shapes[16][1] = 15;
    shapes[17][0] = 40; shapes[17][1] = 16;
    shapes[18][0] = 76; shapes[18][1] = 16;
    shapes[19][0] = 38; shapes[19][1] = 17;
    shapes[20][0] = 40; shapes[20][1] = 17;
    shapes[21][0] = 42; shapes[21][1] = 17;
    shapes[22][0] = 44; shapes[22][1] = 17;
    shapes[23][0] = 46; shapes[23][1] = 17;
    shapes[24][0] = 48; shapes[24][1] = 17;
    shapes[25][0] = 50; shapes[25][1] = 17;
    shapes[26][0] = 52; shapes[26][1] = 17;
    shapes[27][0] = 54; shapes[27][1] = 17;
    shapes[28][0] = 56; shapes[28][1] = 17;
    shapes[29][0] = 58; shapes[29][1] = 17;
    shapes[30][0] = 60; shapes[30][1] = 17;
    shapes[31][0] = 62; shapes[31][1] = 17;
    shapes[32][0] = 64; shapes[32][1] = 17;
    shapes[33][0] = 66; shapes[33][1] = 17;
    shapes[34][0] = 68; shapes[34][1] = 17;
    shapes[35][0] = 70; shapes[35][1] = 17;
    shapes[36][0] = 72; shapes[36][1] = 17;
    shapes[37][0] = 74; shapes[37][1] = 17;
    shapes[38][0] = 76; shapes[38][1] = 17;
    shapes[39][0] = 78; shapes[39][1] = 17;
    return shapes;
}

int(*shape3())[SHAPES_SIZE] {
    static int shapes[SHAPES_SQUARE][SHAPES_SIZE] = { 0 };
    shapes[0][0] = 43; shapes[0][1] = 7;
    shapes[1][0] = 45; shapes[1][1] = 7;
    shapes[2][0] = 47; shapes[2][1] = 7;
    shapes[3][0] = 49; shapes[3][1] = 7;
    shapes[4][0] = 51; shapes[4][1] = 7;
    shapes[5][0] = 53; shapes[5][1] = 7;
    shapes[6][0] = 55; shapes[6][1] = 7;
    shapes[7][0] = 57; shapes[7][1] = 7;
    shapes[8][0] = 59; shapes[8][1] = 7;
    shapes[9][0] = 61; shapes[9][1] = 7;
    shapes[10][0] = 63; shapes[10][1] = 7;
    shapes[11][0] = 65; shapes[11][1] = 7;
    shapes[12][0] = 67; shapes[12][1] = 7;
    shapes[13][0] = 69; shapes[13][1] = 7;
    shapes[14][0] = 71; shapes[14][1] = 7;
    shapes[15][0] = 73; shapes[15][1] = 7;
    shapes[16][0] = 43; shapes[16][1] = 8;
    shapes[17][0] = 73; shapes[17][1] = 8;
    shapes[18][0] = 43; shapes[18][1] = 9;
    shapes[19][0] = 73; shapes[19][1] = 9;
    shapes[20][0] = 43; shapes[20][1] = 10;
    shapes[21][0] = 73; shapes[21][1] = 10;
    shapes[22][0] = 43; shapes[22][1] = 11;
    shapes[23][0] = 73; shapes[23][1] = 11;
    shapes[24][0] = 43; shapes[24][1] = 12;
    shapes[25][0] = 73; shapes[25][1] = 12;
    shapes[26][0] = 43; shapes[26][1] = 13;
    shapes[27][0] = 73; shapes[27][1] = 13;
    shapes[28][0] = 43; shapes[28][1] = 14;
    shapes[29][0] = 73; shapes[29][1] = 14;
    shapes[30][0] = 43; shapes[30][1] = 15;
    shapes[31][0] = 73; shapes[31][1] = 15;
    shapes[32][0] = 43; shapes[32][1] = 16;
    shapes[33][0] = 73; shapes[33][1] = 16;
    shapes[34][0] = 43; shapes[34][1] = 17;
    shapes[35][0] = 73; shapes[35][1] = 17;
    shapes[36][0] = 43; shapes[36][1] = 18;
    shapes[37][0] = 73; shapes[37][1] = 18;
    shapes[38][0] = 43; shapes[38][1] = 19;
    shapes[39][0] = 73; shapes[39][1] = 19;
    shapes[40][0] = 43; shapes[40][1] = 20;
    shapes[41][0] = 45; shapes[41][1] = 20;
    shapes[42][0] = 47; shapes[42][1] = 20;
    shapes[43][0] = 49; shapes[43][1] = 20;
    shapes[44][0] = 51; shapes[44][1] = 20;
    shapes[45][0] = 53; shapes[45][1] = 20;
    shapes[46][0] = 55; shapes[46][1] = 20;
    shapes[47][0] = 57; shapes[47][1] = 20;
    shapes[48][0] = 59; shapes[48][1] = 20;
    shapes[49][0] = 61; shapes[49][1] = 20;
    shapes[50][0] = 63; shapes[50][1] = 20;
    shapes[51][0] = 65; shapes[51][1] = 20;
    shapes[52][0] = 67; shapes[52][1] = 20;
    shapes[53][0] = 69; shapes[53][1] = 20;
    shapes[54][0] = 71; shapes[54][1] = 20;
    shapes[55][0] = 73; shapes[55][1] = 20;


    return shapes;
}