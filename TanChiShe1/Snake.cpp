#include "stdafx.h"
#include "Snake.h"
#include "Node.h"
#include <list>
#include "BaseData.h"
#include <windows.h>

using std::list;

CSnake::CSnake()
{
}


CSnake::~CSnake()
{
}

void CSnake::createSnakeItem(HWND hWnd)
{
	COORD coord;
	switch (g_nDirect)
	{
	case key_NULL:	//方向键为空，代表初始化蛇头，位置为预设值
		coord.X = InitPosition_SnakeHead_X;
		coord.Y = InitPosition_SnakeHead_Y;
		break;
	case key_UP:	//方向键不为空，代表运行中蛇头，位置为链表中第一个节点位置上移动，下同
		coord.X = this->m_Snake.front().m_coord.X;
		coord.Y = this->m_Snake.front().m_coord.Y - 30;
		break;
	case key_DOWN:
		coord.X = this->m_Snake.front().m_coord.X;
		coord.Y = this->m_Snake.front().m_coord.Y + 30;
		break;
	case key_LEFT:
		coord.X = this->m_Snake.front().m_coord.X - 30;
		coord.Y = this->m_Snake.front().m_coord.Y;
		break;
	case key_RIGHT:
		coord.X = this->m_Snake.front().m_coord.X + 30;
		coord.Y = this->m_Snake.front().m_coord.Y;
		break;
	default:
		break;
	};

	HWND hCtrl = CreateWindow(TEXT("STATIC"), TEXT("node1"),
		WS_CHILD | WS_VISIBLE | SS_BITMAP, coord.X, coord.Y, 30, 30,
		hWnd, (HMENU)1, hInstance, NULL);
	HDC dc = GetDC(hCtrl);
	HBITMAP hBitMap = (HBITMAP)LoadImageA(NULL, Pic_SnakeHead, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HDC dcMemary = CreateCompatibleDC(dc);
	(HBITMAP)SendMessage(hCtrl, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitMap);
	DeleteDC(dc);
	DeleteDC(dcMemary);
	DeleteObject(hBitMap);

	CNode node(coord, NodeStyle_SnakeHead, hCtrl);
	this->m_Snake.push_front(node);
}

void CSnake::dropListItem()
{
	DestroyWindow(this->m_Snake.back().m_hWnd);
	this->m_Snake.pop_back();
}


