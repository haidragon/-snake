#pragma once
#include <windows.h>

class CNode
{
public:
	COORD m_coord;		//node����
	int m_style;		//�ڵ�����
	HWND m_hWnd;	//ÿ���ڵ�ؼ��ľ��
public:
	CNode();
	CNode(COORD coord, int style, HWND hWnd);
	~CNode();
};

