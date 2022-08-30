#include "stdafx.h"
#include "MonsterLifeBar.h"
#include "BmpMgr.h"
#include "InterfaceMgr.h"
#include "ScrollMgr.h"


CMonsterLifeBar::CMonsterLifeBar()
{
	Initialize();
}


CMonsterLifeBar::~CMonsterLifeBar()
{
}

void CMonsterLifeBar::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/m_hpbar.bmp", L"HP_bar_empty");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/m_hp.bmp", L"HP_bar");
	Life_Bar = 50.f;
	m_bRender = false;
}

void CMonsterLifeBar::Render(HDC _DC)
{
	HDC hHP = CBmpMgr::Get_Instance()->Find_Bmp(L"HP_bar");
	HDC hHPBar = CBmpMgr::Get_Instance()->Find_Bmp(L"HP_bar_empty");
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, 52, 5
		, hHPBar
		, 0, 0
		, 52, 5
		, RGB(255, 255, 255));
	GdiTransparentBlt(_DC
		, m_tRect.left + 1 + iScrollX, m_tRect.top +1 + iScrollY
		, Life_Bar, 3
		, hHP
		, 0, 0
		, 50, 3
		, RGB(255, 255, 255));
}

void CMonsterLifeBar::Update()
{
}

void CMonsterLifeBar::Late_Update()
{
}

void CMonsterLifeBar::Release()
{
}

void CMonsterLifeBar::Rect_Update(RECT _rc)
{
	m_tRect.left = _rc.left;
	m_tRect.top = _rc.bottom + 10;
	m_tRect.right = _rc.left + 52;
	m_tRect.bottom = _rc.bottom + 15;
}

void CMonsterLifeBar::Set_Bar(float _x)
{
	Life_Bar = _x;
}
