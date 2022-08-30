#include "stdafx.h"
#include "BossFire.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "Player.h"
#include "Tile.h"

CBossFire::CBossFire()
{
	ZeroMemory(&m_tEndPos, sizeof(m_tEndPos));
	ZeroMemory(&m_tStartPos, sizeof(m_tStartPos));
}


CBossFire::~CBossFire()
{
	Release();
}

void CBossFire::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Hard/Boss_Hard_Skill.bmp", L"Hard_Skill");
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 5;
	m_tFrame.dwDelay = 100;
}

void CBossFire::Update()
{
	RECT rc = {};
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS_HARD)
	{
		for (auto iter : CObjMgr::Get_Instance()->Get_Player())
			if (&rc, &static_cast<CPlayer*>(iter)->Get_Hit_Box(), &m_tRect)
				if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
					static_cast<CPlayer*>(iter)->is_Magic_Hit_Check(m_tRect,(rand() % 20));
	}
}

void CBossFire::Render(HDC _DC, const TCHAR * _pFrameKey)
{
	if (m_bRender)
	{
		Update();
		if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
		{
			++m_tFrame.iStartX;
			m_tFrame.dwTime = GetTickCount();
			if (m_tFrame.iStartX > m_tFrame.iEndX)
				m_tFrame.iStartX = 0;
		}

		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Hard_Skill");

		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, 30, 30
			, hEffectDC
			, m_tFrame.iStartX * 30, 0
			, 30, 30
			, RGB(255, 255, 255));
	}
}

void CBossFire::Release()
{
}

void CBossFire::Update_Rect(INFO _rc)
{
}

void CBossFire::Check_Vector(CTile * _Tile, float _x, float _y)
{
	m_tRect.left = _Tile->Get_Rect().left;
	m_tRect.top = _Tile->Get_Rect().top;
	m_tRect.right = _Tile->Get_Rect().right;
	m_tRect.bottom = _Tile->Get_Rect().bottom;
	m_bRender = true;
}
