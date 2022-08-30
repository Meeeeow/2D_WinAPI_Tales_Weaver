#include "stdafx.h"
#include "Hit.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

CHit::CHit()
{
	ZeroMemory(&m_tEndPos, sizeof(m_tEndPos));
	ZeroMemory(&m_tStartPos, sizeof(m_tStartPos));
}


CHit::~CHit()
{
}

void CHit::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Hit.bmp", L"Player_Hit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster_Hit.bmp", L"Monster_Hit");
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 3;
	m_tFrame.dwDelay = 100;
}

void CHit::Update()
{
}

void CHit::Render(HDC _DC,const TCHAR* _pFrameKey)
{
	if (m_bRender)
	{
		Frame_Update();

		int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Bmp(_pFrameKey);

		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, 90, 120
			, hEffectDC
			, m_tFrame.iStartX * 150, 0
			, 90, 120
			, RGB(255, 255, 255));
	}

}

void CHit::Release()
{
}

void CHit::Update_Rect(INFO _rc)
{
	m_tRect.left = _rc.fX - 100;
	m_tRect.right = _rc.fX +40 ;
	m_tRect.top = _rc.fY - 105;
	m_tRect.bottom = _rc.fY +40;
}

void CHit::Check_Vector(CTile * _Tile, float _x, float _y)
{
}
