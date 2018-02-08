#pragma once
#include "Node.h"
class CFood : public CNode
{
public:
	CFood();
	~CFood();
	void createFood(HWND hWnd);
	void dropItem();
};

