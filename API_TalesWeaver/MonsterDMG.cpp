#include "stdafx.h"
#include "MonsterDMG.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"

CMonsterDMG::CMonsterDMG()
{
}


CMonsterDMG::~CMonsterDMG()
{
	Release();
}

void CMonsterDMG::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg0.bmp", L"MDMG_Zero");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg1.bmp", L"MDMG_One");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg2.bmp", L"MDMG_Two");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg3.bmp", L"MDMG_Three");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg4.bmp", L"MDMG_Four");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg5.bmp", L"MDMG_Five");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg6.bmp", L"MDMG_Six");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg7.bmp", L"MDMG_Seven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg8.bmp", L"MDMG_Eight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/DmgFont/Dmg9.bmp", L"MDMG_Nine");
}

void CMonsterDMG::Update()
{
	int iX = 0;
	++iX;
	m_tRect.left += iX;
	m_tRect.top -= iX;

	if (m_tDeleteTime + 1000 < GetTickCount())
		m_bRender = false;
}

void CMonsterDMG::Render(HDC _DC, const TCHAR * _pFrameKey)
{
	if (m_bRender)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (m_pDmgRender[i]->m_bDmgRender)
			{
				int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
				int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
				HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pDmgRender[i]->m_pFrameKey);

				GdiTransparentBlt(_DC
					, m_tRect.left + iScrollX - (i * 30), m_tRect.top + iScrollY
					, 30, 30
					, hEffectDC
					, 0, 0
					, 30, 30
					, RGB(255, 255, 255));
			}

		}
	}
	Update();
}

void CMonsterDMG::Release()
{
	for (int i = 0; i < 3; ++i)
		SAFE_DELETE(m_pDmgRender[i]);
}

void CMonsterDMG::Update_Rect(INFO _rc)
{
	m_tRect.left = _rc.fX - 20;
	m_tRect.top = _rc.fY - 100;
	m_tRect.right = _rc.fX;
	m_tRect.bottom = _rc.fY - 70;
	m_bRender = true;
}

void CMonsterDMG::Check_Vector(CTile * _Tile, float _x, float _y)
{
}

void CMonsterDMG::Check_Dmg(int _Dmg)
{
	m_tDeleteTime = GetTickCount();

	MaxDmg = _Dmg;
	for (int i = 0; i < 3; ++i)
	{
		m_pDmgRender[i] = new DMGRENDER;

		m_pDmgRender[i]->m_iDmg = MaxDmg % 10;
		m_pDmgRender[i]->m_bDmgRender = true;
		MaxDmg /= 10;

		if (m_pDmgRender[i]->m_iDmg == 0)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Zero";
		else if (m_pDmgRender[i]->m_iDmg == 1)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_One";
		else if (m_pDmgRender[i]->m_iDmg == 2)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Two";
		else if (m_pDmgRender[i]->m_iDmg == 3)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Three";
		else if (m_pDmgRender[i]->m_iDmg == 4)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Four";
		else if (m_pDmgRender[i]->m_iDmg == 5)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Five";
		else if (m_pDmgRender[i]->m_iDmg == 6)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Six";
		else if (m_pDmgRender[i]->m_iDmg == 7)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Seven";
		else if (m_pDmgRender[i]->m_iDmg == 8)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Eight";
		else if (m_pDmgRender[i]->m_iDmg == 9)
			m_pDmgRender[i]->m_pFrameKey = L"MDMG_Nine";
	}
	if (m_pDmgRender[2]->m_iDmg == 0)
		m_pDmgRender[2]->m_bDmgRender = false;
	if (m_pDmgRender[2]->m_iDmg == 0 && m_pDmgRender[1]->m_iDmg == 0)
	{
		m_pDmgRender[2]->m_bDmgRender = false;
		m_pDmgRender[1]->m_bDmgRender = false;
	}
}
