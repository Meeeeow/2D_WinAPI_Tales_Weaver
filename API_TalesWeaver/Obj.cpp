#include "stdafx.h"
#include "Obj.h"
#include "EffectMgr.h"
#include "ScrollMgr.h"

CObj::CObj()
	: m_fSpeed(0.f), m_fAngle(0.f), m_bDead(false),  m_bHit(false)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tHitBox, sizeof(m_tHitBox));
}


CObj::~CObj()
{
}

void CObj::Set_Dead()
{
	if (m_tStats.m_iCur_HP <= 0)
		m_bDead = true;
}



void CObj::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CObj::Update_Tile_Rect()
{
	m_tCheckTile.left = (LONG)(m_tInfo.fX - 5);
	m_tCheckTile.top = (LONG)(m_tInfo.fY - 5);
	m_tCheckTile.right = (LONG)(m_tInfo.fX + 5);
	m_tCheckTile.bottom = (LONG)(m_tInfo.fY + 5);
}


void CObj::Render_Hitbox(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(_DC, myPen);
	Rectangle(_DC, m_tHitBox.left +iScrollX, m_tHitBox.top + iScrollY, m_tHitBox.right + iScrollX, m_tHitBox.bottom + iScrollY);
	SelectObject(_DC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(_DC, oldPen);
	DeleteObject(myPen);

}
