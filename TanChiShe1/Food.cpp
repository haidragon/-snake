#include "stdafx.h"
#include "Food.h"
#include <windows.h>
#include "BaseData.h"
#include <time.h>


CFood::CFood()
{
}


CFood::~CFood()
{
}

void CFood::createFood(HWND hWnd)
{
	COORD coord;
	
	coord.X = (rand() % (MAP_GAME_WIDTH / 30 - 2) + 1) * 30;
	coord.Y = (rand() % (MAP_GAME_HEIGHT / 30 - 3) + 1) * 30;

	HWND hCtrl = CreateWindow(TEXT("STATIC"), TEXT("node1"),
		WS_CHILD | WS_VISIBLE | SS_BITMAP, coord.X, coord.Y, 30, 30,
		hWnd, (HMENU)1, hInstance, NULL);

	HDC dc = GetDC(hCtrl);

	HBITMAP hBitMap = (HBITMAP)LoadImageA(NULL, Pic_Food, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC dcMemary = CreateCompatibleDC(dc);

	(HBITMAP)SendMessage(hCtrl, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap);

	DeleteDC(dc);
	DeleteDC(dcMemary);
	DeleteObject(hBitMap);

	this->m_coord = coord;
	this->m_style = NodeStyle_Food;
	this->m_hWnd = hCtrl;
}

void CFood::dropItem()
{
	DestroyWindow(this->m_hWnd);	
}
