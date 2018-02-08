#include "stdafx.h"
#include "Stone.h"
#include "BaseData.h"
#include <time.h>

CStone::CStone()
{
}


CStone::~CStone()
{
}

void CStone::createStone(HWND hWnd)
{
	COORD coord;
	HWND hCtrl;
	HDC dc;
	HBITMAP hBitMap;
	HDC dcMemary;

	for (int i = 0; i < Count_Stone; i++)
	{
		coord.X = (rand() % (MAP_GAME_WIDTH / 30 - 2) + 1) * 30;
		coord.Y = (rand() % (MAP_GAME_HEIGHT / 30 - 3) + 1) * 30;

		hCtrl = CreateWindow(TEXT("STATIC"), TEXT("node1"),
			WS_CHILD | WS_VISIBLE | SS_BITMAP, coord.X, coord.Y, 30, 30,
			hWnd, (HMENU)1, hInstance, NULL);

		dc = GetDC(hCtrl);
		hBitMap = (HBITMAP)LoadImageA(NULL, Pic_Stone, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		dcMemary = CreateCompatibleDC(dc);

		(HBITMAP)SendMessage(hCtrl, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap);

		this->stone[i].m_coord = coord;
		this->stone[i].m_style = NodeStyle_Stone;
		this->stone[i].m_hWnd = hCtrl;
	}

	DeleteDC(dc);
	DeleteDC(dcMemary);
	DeleteObject(hBitMap);
}
