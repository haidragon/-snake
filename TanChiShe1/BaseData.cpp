#include "stdafx.h"
#include <windows.h>

HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
HANDLE hConcoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
HWND hWndGame;
HWND hWndWelcome;
HWND hWndEnd;
HWND hWndScore;
TCHAR szAppName[] = TEXT("TanChiShe");

int createMapTimes = 0;
int drawMapTimes = 0;
int g_nDirect;
int g_nGameState = 0;
int g_nFoodState = 0;
int g_nEatCount = 0;
int g_nStoneState = 0;
int g_nEndState = 0;
int g_nWelcomState = 1;