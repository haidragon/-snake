#pragma once
#include "Node.h"
#include "BaseData.h"

class CStone :	public CNode
{
public:
	CNode stone[Count_Stone];
public:
	CStone();
	~CStone();
	void createStone(HWND hWnd);
};

