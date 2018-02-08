// TanChiShe1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "BaseData.h"
#include "Snake.h"
#include "Food.h"
#include "Stone.h"
#include <string>
#include <list>
#pragma comment(lib,"winmm.lib")
using std::list;

HWND hWnd;
MSG msg;
WNDCLASS wndClass;

CSnake snake;
CFood food;
CStone stone;

HFONT hFont;
HBRUSH hBrush;

bool TCSRegistClass();
bool TCSCreateMap();
void TCSGetMessage();
void initGame();
bool crash();
void changeScore();

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(0));
	if(!TCSRegistClass())
		return 0;
	if (!TCSCreateMap())
		return 0;
	PlaySoundA("sound\\bgMusic.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	TCSGetMessage();
}

bool TCSRegistClass()
{
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szAppName;

	if (!RegisterClass(&wndClass))
	{
		MessageBox(NULL, TEXT("error"), szAppName, MB_ICONERROR);
		return 0;
	}
	return 1;
}

bool TCSCreateMap()
{
	hWndGame = CreateWindow(szAppName, szAppName,
		WS_OVERLAPPEDWINDOW, 50, 50, MAP_TOTAL_WIDTH, MAP_TOTAL_HEIGHT,
		NULL, NULL, hInstance, NULL);

	if (!hWndGame)
	{
		return 0;
	}

	ShowWindow(hWndGame, SW_SHOW); 
	UpdateWindow(hWndGame);

	return 1;
}

void TCSGetMessage()
{
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

//修改节点图标
//仅有吃到豆后，蛇头变蛇身一种情况下调用
void changeNode()
{
	HWND hCtrl = snake.m_Snake.front().m_hWnd;
	HDC dc = GetDC(hCtrl);
	HBITMAP hBitMap = (HBITMAP)LoadImageA(NULL, Pic_SnakeBody, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC dcMemary = CreateCompatibleDC(dc);
	(HBITMAP)SendMessage(hCtrl, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap);
	DeleteDC(dc);
	DeleteDC(dcMemary);
	DeleteObject(hBitMap);
}

//吃
int eat()
{
	if (snake.m_Snake.front().m_coord.X == food.m_coord.X && snake.m_Snake.front().m_coord.Y == food.m_coord.Y)
	{ 
		g_nEatCount++;
		changeScore();
		return 1;
	}
	return 0;
}

//创建结束界面
void createEnd(HWND hWnd)
{
	HWND tmpHWnd = CreateWindow(TEXT("STATIC"), TEXT("start"),
		WS_CHILD | WS_VISIBLE | SS_BITMAP, 200, 100, 400, 400,
		hWnd, (HMENU)1, NULL, NULL);
	HDC dc = GetDC(hWnd);
	HBITMAP hBitMap = (HBITMAP)LoadImageA(NULL, Pic_End, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC dcMemary = CreateCompatibleDC(dc);
	(HBITMAP)SendMessage(tmpHWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap);
	hWndEnd = tmpHWnd;
	/*DeleteDC(dc);
	DeleteDC(dcMemary);
	DeleteObject(hBitMap);*/
}

//移动
void move(HWND hWnd)
{
	if (!g_nGameState)	//如果游戏状态为0，退出
		return;
	if (!g_nFoodState)	//如果食物状态为0，创建食物，改变状态
	{
		food.createFood(hWnd);
		g_nFoodState = 1;
	}
	if (!g_nStoneState)	//如果障碍物状态为0，创建障碍物，改变状态
	{
		stone.createStone(hWnd);
		g_nStoneState = 1;
	}
		
	changeNode();
	snake.createSnakeItem(hWnd);
	if (!eat())		//如果没吃到，删除蛇末尾节点
	{
		snake.dropListItem();
	}
	else//如果吃到了，删除食物节点
	{
		food.dropItem();
		g_nFoodState = 0;
	}
	
	//判断碰撞
	if (crash())
	{
		g_nGameState = 0;
		createEnd(hWnd);
		g_nEndState = 1;
		//销毁所有控件，上次游戏遗留
		initGame();
	}
}

//修改分数
void changeScore()
{
	TCHAR score[20];
	wsprintf(score, L"Score : %d", g_nEatCount);
	SetWindowText(hWndScore, score);
}

//销毁所有控件
void initGame()
{
	//销毁蛇
	if (!snake.m_Snake.empty())
	{
		for (auto node = snake.m_Snake.begin(); node != snake.m_Snake.end(); node++)
		{
			DestroyWindow(node->m_hWnd);
		}
		snake.m_Snake.clear();
	}
	//销毁障碍物
	for (int i = 0; i < Count_Stone; i++)
	{
		DestroyWindow(stone.stone[i].m_hWnd);
		stone.stone[i].m_coord = { 0, 0 };
		stone.stone[i].m_hWnd = NULL;
	}
	//销毁食物
	if (food.m_hWnd)
	{
		DestroyWindow(food.m_hWnd);
		food.m_coord = { 0, 0 };
		food.m_hWnd = NULL;
	}
	//键盘操作记录还原
	g_nDirect = key_NULL;
	g_nGameState = 0;
	g_nFoodState = 0;
	g_nEatCount = 0;
}

//创建欢迎界面
void createWelcome(HWND hWnd)
{
	HWND tmpHWnd = CreateWindow(TEXT("STATIC"), TEXT("start"),
		WS_CHILD | WS_VISIBLE | SS_BITMAP, 200, 100, 400, 400,
		hWnd, (HMENU)1, NULL, NULL);
	HDC dc = GetDC(hWnd);
	HBITMAP hBitMap = (HBITMAP)LoadImageA(NULL, Pic_Start, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC dcMemary = CreateCompatibleDC(dc);
	(HBITMAP)SendMessage(tmpHWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap);
	hWndWelcome = tmpHWnd;
	//SendMessage(tmpHWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
	/*DeleteDC(dc);
	DeleteDC(dcMemary);
	DeleteObject(hBitMap);*/
}

//创建信息区域界面
void createInfoArea(HWND hWnd)
{
	HWND tmpHWnd;
	//title
	hFont = CreateFont(60, 0, 0, 0, FW_BLACK, false, false, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SCRIPT, TEXT("Aunt-逗比莉麻体"));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	tmpHWnd = CreateWindow(TEXT("STATIC"), TEXT("贪 吃 蛇"),
		WS_CHILD | WS_VISIBLE, 930, 50, 240, 60,
		hWnd, (HMENU)1, NULL, NULL);
	SendMessage(tmpHWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

	//score
	hFont = CreateFont(30, 0, 0, 0, FW_BLACK, false, false, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SCRIPT, TEXT("Aunt-逗比莉麻体"));
	tmpHWnd = CreateWindow(TEXT("STATIC"), TEXT("score : 0"),
		WS_CHILD | WS_VISIBLE, 930, 200, 240, 60,
		hWnd, (HMENU)1, NULL, NULL);
	hWndScore = tmpHWnd;
	SendMessage(tmpHWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

	//introduce
	hFont = CreateFont(25, 0, 0, 0, FW_BLACK, false, false, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SCRIPT, TEXT("Aunt-逗比莉麻体"));
	tmpHWnd = CreateWindow(TEXT("STATIC"), TEXT("UP:向上移动   DOWN:向下移动 LEFT:向左移动 RIGHT:向右移动"),
		WS_CHILD | WS_VISIBLE, 930, 300, 220, 240,
		hWnd, (HMENU)1, NULL, NULL);
	SendMessage(tmpHWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

	//start
	createWelcome(hWnd);
}

//碰撞判断
bool crash()
{
	//石头碰撞检测
	for (int i = 0; i < Count_Stone; i++)
	{
		if (stone.stone[i].m_coord.X == snake.m_Snake.front().m_coord.X && stone.stone[i].m_coord.Y == snake.m_Snake.front().m_coord.Y)
		{
			return 1;
		}
	}
	//边界碰撞检测
	if (snake.m_Snake.front().m_coord.Y == 0 || snake.m_Snake.front().m_coord.Y == MAP_GAME_HEIGHT - 30)
	{
		return 1;
	}
	if (snake.m_Snake.front().m_coord.X == 0 || snake.m_Snake.front().m_coord.X >= MAP_GAME_WIDTH - 30)
	{
		return 1;
	}
	//自身碰撞
	for (auto node = snake.m_Snake.begin(); node != snake.m_Snake.end(); node++) 
	{
		if (snake.m_Snake.size() > 1 && node->m_style == NodeStyle_SnakeBody && node->m_coord.X == snake.m_Snake.front().m_coord.X && node->m_coord.Y == snake.m_Snake.front().m_coord.Y)
		{
			return 1;
		}
	}
	return 0;
}

//开始游戏
void startGame(HWND hWnd)
{
	//关闭欢迎界面
	if (hWndWelcome)
	{
		DestroyWindow(hWndWelcome);
		//g_nStoneState = 0;
		g_nWelcomState = 0;
	}
	//关闭结束界面
	if (hWndEnd)
	{
		DestroyWindow(hWndEnd);
		g_nEndState = 0;
	}
	//创建蛇头
	snake.createSnakeItem(hWnd);
	//创建时间控件
	SetTimer(hWnd, 1, 200, (TIMERPROC)NULL);
	//创建食物
	food.createFood(hWnd);
	g_nFoodState = 1;
	//创建障碍
	stone.createStone(hWnd);
	g_nStoneState = 1;
	//清空分数
	changeScore();
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		if (g_nGameState == 0)
		{
			createInfoArea(hWnd);
			//snake.createSnakeItem(hWnd);
			//SetTimer(hWnd, 1, 200, (TIMERPROC)NULL);
		}
		break;
	}
	case WM_PAINT:
	{
		HDC tmpDC;
		PAINTSTRUCT ps;
		HPEN hPen;
		HPEN hPenOld;
		tmpDC = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hPenOld = (HPEN)SelectObject(tmpDC, hPen);
		MoveToEx(tmpDC, 900, 10, NULL);
		LineTo(tmpDC, 900, 550);
		SelectObject(tmpDC, hPenOld);
		DeleteObject(hPen);
		ReleaseDC(hWnd, tmpDC);
		break;
	}
	case WM_TIMER:
		move(hWnd);
		break;

	case WM_KEYUP:
	{

		switch (wParam)
		{
		case key_LEFT:
		case key_UP:
		case key_RIGHT:
		case key_DOWN:
		{
// 			char str[10] = { 0 };
// 			sprintf_s(str, "VK\"%d\"", wParam);
// 			MessageBoxA(NULL, str, str, MB_OK);
			g_nDirect = wParam;
			g_nGameState = 1;
			break;
		}
		case key_Enter:
		{
			if (g_nWelcomState || g_nEndState)	//欢迎界面 或 结束界面 按回车 开始游戏
				startGame(hWnd);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_CTLCOLORSTATIC:
		SetTextColor((HDC)wParam, RGB(255, 255, 0));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return(INT_PTR)hBrush;
	case WM_DESTROY:
		DeleteObject(hBrush);
		DeleteObject(hFont);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}