#include "stdafx.h"
#include "Spin.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CSpin::CSpin()
{
	ZeroMemory(&m_tEndPos, sizeof(m_tEndPos));
	ZeroMemory(&m_tStartPos, sizeof(m_tStartPos));
}


CSpin::~CSpin()
{
}

void CSpin::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Spin/Player_Spin_Effect.bmp", L"Player_Spin_Effect");
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 40;
	m_tFrame.dwDelay = 29;
}

void CSpin::Update()
{
}

void CSpin::Render(HDC _DC, const TCHAR * _pFrameKey)
{
	if (m_bRender)
	{
		Frame_Update();

		int iScrollX = (int)(CScrollMgr::Get_Instance()->Get_ScrollX());
		int iScrollY = (int)(CScrollMgr::Get_Instance()->Get_ScrollY());
		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Bmp(_pFrameKey);

		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, 175, 175
			, hEffectDC
			, m_tFrame.iStartX * 350, 0
			, 350, 300
			, RGB(255, 255, 255));
	}
}

void CSpin::Release()
{
}

void CSpin::Update_Rect(INFO _rc)
{
	m_tRect.left = (LONG)_rc.fX - 90;
	m_tRect.right = (LONG)_rc.fX + 75;
	m_tRect.top = (LONG)_rc.fY - 110;
	m_tRect.bottom = (LONG)_rc.fY +55;
}

void CSpin::Check_Vector(CTile * _Tile, float _x, float _y)
{
}
