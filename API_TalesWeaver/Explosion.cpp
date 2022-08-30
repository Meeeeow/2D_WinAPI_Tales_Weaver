#include "stdafx.h"
#include "Explosion.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Tile.h"
#include "Obj.h"
#include "JellyBee.h"
#include "SoundMgr.h"
#include "Player.h"
#include "SceneMgr.h"
CExplosion::CExplosion()
{
}


CExplosion::~CExplosion()
{
}

void CExplosion::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Explosion/Player_Explosion.bmp", L"Explosion");
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 28;
	m_tFrame.dwDelay = 700;
}

void CExplosion::Update()
{
	RECT rc = {};
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD)
	{
		if (m_tFrame.iStartX >= 20)
			for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER))
				if (&rc, &iter->Get_Hit_Box(), &m_tRect)
					iter->is_Magic_Hit_Check(m_tRect, iDmg + (rand() % 200));
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD2)
	{
		if (m_tFrame.iStartX >= 20)
			for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER2))
				if (&rc, &iter->Get_Hit_Box(), &m_tRect)
					iter->is_Magic_Hit_Check(m_tRect, iDmg + (rand() % 200));
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS)
	{
		if (m_tFrame.iStartX >= 20)
			for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS))
				if (&rc, &iter->Get_Hit_Box(), &m_tRect)
					iter->is_Magic_Hit_Check(m_tRect, iDmg + (rand() % 200));
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS_HARD)
	{
		if (m_tFrame.iStartX >= 20)
			for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS_HARD))
				if (&rc, &iter->Get_Hit_Box(), &m_tRect)
					iter->is_Magic_Hit_Check(m_tRect, iDmg + (rand() % 200));
	}
}

void CExplosion::Render(HDC _DC, const TCHAR * _pFrameKey)
{
	if (m_bRender)
	{
		Update();
		if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
		{
			++m_tFrame.iStartX;
			m_tFrame.dwTime = GetTickCount();

			if (m_tFrame.iStartX > m_tFrame.iEndX)
			{
				m_tFrame.iStartX = 0;
				m_bRender = false;
				for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER))
					static_cast<CPlayer*>(iter)->Cast_Explosion_Off();
			}
		}

		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Explosion");

		GdiTransparentBlt(_DC
			, m_tRect.left+100 + iScrollX, m_tRect.top + iScrollY
			, 300, 300
			, hEffectDC
			, m_tFrame.iStartX * 300, 0
			, 300, 300
			, RGB(255, 255, 255));
	}
}

void CExplosion::Release()
{

}

void CExplosion::Update_Rect(INFO _rc)
{

}

void CExplosion::Check_Vector(CTile * _Tile, float _x, float _y)
{
}

void CExplosion::Check_Vector(CTile * _Tile, float _x, float _y,int _mana)
{
	m_tRect.left = (LONG)_Tile->Get_Info().fX - 100;
	m_tRect.top = (LONG)_Tile->Get_Info().fY - 100;
	m_tRect.right = (LONG)_Tile->Get_Info().fX + 100;
	m_tRect.bottom = (LONG)_Tile->Get_Info().fY + 100;
	m_tEndPos.x = (LONG)_x;
	m_tEndPos.y = (LONG)_y;
	iDmg = _mana;
}
