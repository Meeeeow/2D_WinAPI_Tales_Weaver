#include "stdafx.h"
#include "PlayerLevelUp.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"
#include "Player.h"
#include "ObjMgr.h"
CPlayerLevelUp::CPlayerLevelUp()
{
}


CPlayerLevelUp::~CPlayerLevelUp()
{
}

void CPlayerLevelUp::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/LevelUp/LevelUp.bmp", L"LevelUp");
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 29;
	m_tFrame.dwDelay = 100;
}

void CPlayerLevelUp::Update()
{
}

void CPlayerLevelUp::Render(HDC _DC, const TCHAR * _pFrameKey)
{
	if (m_bRender)
	{
		Frame_Update();

		int iScrollX = (int)(CScrollMgr::Get_Instance()->Get_ScrollX());
		int iScrollY = (int)(CScrollMgr::Get_Instance()->Get_ScrollY());
		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Bmp(L"LevelUp");
		for (auto iter : CObjMgr::Get_Instance()->Get_Player())
		{
			GdiTransparentBlt(_DC
				, iter->Get_Hit_Box().left + iScrollX - 10, iter->Get_Hit_Box().top + iScrollY - 60
				, 150, 100
				, hEffectDC
				, m_tFrame.iStartX * 250, 0
				, 250, 200
				, RGB(255, 255, 255));
		}
	}
}

void CPlayerLevelUp::Release()
{
}

void CPlayerLevelUp::Update_Rect(INFO _rc)
{
}

void CPlayerLevelUp::Check_Vector(CTile * _Tile, float _x, float _y)
{
}
