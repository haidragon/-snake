#pragma once
#include "Node.h"
#include <list>

using std::list;

class CSnake:CNode
{
public:
	list<CNode> m_Snake;
public:
	CSnake();
	~CSnake();
	void createSnakeItem(HWND hCtrl);
	void dropListItem();
};

