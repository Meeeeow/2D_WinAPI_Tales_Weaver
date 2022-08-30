#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;


CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f), m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(int _Max_X_Size, int _Max_Y_Size)
{
	if (0 < m_fScrollX)
		m_fScrollX = 0;
	if (0 < m_fScrollY)
		m_fScrollY = 0;
	if (WINCX - _Max_X_Size > m_fScrollX)
		m_fScrollX = WINCX - _Max_X_Size;
	if (WINCY - _Max_Y_Size > m_fScrollY)
		m_fScrollY = WINCY - _Max_Y_Size;
}

