#include "stdafx.h"
#include "Node.h"


CNode::CNode()
{
}

CNode::CNode(COORD coord, int style, HWND hWnd)
{
	this->m_coord = coord;
	this->m_style = style;
	this->m_hWnd = hWnd;
}


CNode::~CNode()
{
}

