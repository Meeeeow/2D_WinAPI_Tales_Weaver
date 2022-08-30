#include "stdafx.h"
#include "Mouse.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ObjMgr.h"
#include "JellyBee.h"
#include "ScrollMgr.h"

CMouse::CMouse()
	: m_eCurState(END), m_ePreState(END)
{
	Initialize();
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.iCX = 150;
	m_tInfo.iCY = 150;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Mouse/Mouse_Sprite.bmp", L"MOUSE");
	m_eCurState = IDLE;
}

void CMouse::Update()
{

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	ShowCursor(false);
	
	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
	{
		if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON))
			m_eCurState = CLICK;
		if (PtInRect(&iter->Get_Rect(), pt))
		{
			if (iter->Get_DrawID() == 0)
				m_eCurState = IDLE;
			else if (iter->Get_DrawID() == 1)
				m_eCurState = NOMOVE;
			else if (iter->Get_DrawID() == 4)
				m_eCurState = GATE;
		}
	}
}

void CMouse::Late_Update()
{
	Frame_Check();
	Frame_Update();
	Update_Rect();
}

void CMouse::Render(HDC _DC)
{
	HDC hMouseDC = CBmpMgr::Get_Instance()->Find_Bmp(L"MOUSE");

	GdiTransparentBlt(_DC
		, pt.x , pt.y
		, 50, 50
		, hMouseDC
		, m_tFrame.iStartX * 150, m_tFrame.iState * 150
		, 50, 50
		, RGB(255, 255, 255));
}

void CMouse::Release()
{

}

void CMouse::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CMouse::Frame_Check()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CMouse::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 11;
			m_tFrame.iState = IDLE;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CMouse::CLICK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iState = CLICK;
			m_tFrame.dwDelay = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CMouse::NOMOVE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 11;
			m_tFrame.iState = NOMOVE;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CMouse::GATE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.iState = GATE;
			m_tFrame.dwDelay = 60;
			m_tFrame.dwTime = GetTickCount();
		}
		m_ePreState = m_eCurState;
	}
}

void CMouse::Frame_Update()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX = 0;
	}
}

void CMouse::Change_ID(int _iD)
{
	m_tFrame.iState = _iD;
}

