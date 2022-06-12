/* selectmap.h */
#pragma once

#include <io.h>
#include "rhythm_main.h"
#include "parson.h"


int mapCount; // 맵의 개수
char** mapList; // 맵 선택 창에서 띄울 맵 목록

const int slp = 32; // selectmap left padding
const int stp = 2; // selectmap top padding

char* statsPath; // stats.dat 파일 경로 (JSON) ("maps/stats.dat")


char* main_selectmap();
int loadMaps();
int showMapList();
int selecting(int mapCount);
void blink(int pointer);
