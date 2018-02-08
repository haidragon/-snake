#pragma once
#include <windows.h>

class CNode
{
public:
	COORD m_coord;		//node坐标
	int m_style;		//节点类型
	HWND m_hWnd;	//每个节点控件的句柄
public:
	CNode();
	CNode(COORD coord, int style, HWND hWnd);
	~CNode();
};

