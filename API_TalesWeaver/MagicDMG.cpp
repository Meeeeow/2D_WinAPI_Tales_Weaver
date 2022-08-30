#include "stdafx.h"
#include "MagicDMG.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "EffectMgr.h"

CMagicDMG::CMagicDMG()
{
}


CMagicDMG::~CMagicDMG()
{
	Release();
}

void CMagicDMG::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg0.bmp", L"MagicDMG_Zero");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg1.bmp", L"MagicDMG_One");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg2.bmp", L"MagicDMG_Two");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg3.bmp", L"MagicDMG_Three");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg4.bmp", L"MagicDMG_Four");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg5.bmp", L"MagicDMG_Five");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg6.bmp", L"MagicDMG_Six");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg7.bmp", L"MagicDMG_Seven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg8.bmp", L"MagicDMG_Eight");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Damage/MagicDmgFont/Dmg9.bmp", L"MagicDMG_Nine");
}

void CMagicDMG::Update()
{
	int iX = 0;
	++iX;
	m_tRect.left += iX;
	m_tRect.top -= iX;

	if (m_tDeleteTime + 1000 < GetTickCount())
		m_bRender = false;
}

void CMagicDMG::Render(HDC _DC, const TCHAR * _pFrameKey)
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

void CMagicDMG::Release()
{
	for (int i = 0; i < 3; ++i)
		SAFE_DELETE(m_pDmgRender[i]);
}

void CMagicDMG::Update_Rect(INFO _rc)
{
	m_tRect.left = _rc.fX - 20;
	m_tRect.top = _rc.fY - 100;
	m_tRect.right = _rc.fX;
	m_tRect.bottom = _rc.fY - 70;
	m_bRender = true;
}

void CMagicDMG::Check_Vector(CTile * _Tile, float _x, float _y)
{
}

void CMagicDMG::Check_Dmg(int _Dmg)
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
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Zero";
		else if (m_pDmgRender[i]->m_iDmg == 1)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_One";
		else if (m_pDmgRender[i]->m_iDmg == 2)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Two";
		else if (m_pDmgRender[i]->m_iDmg == 3)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Three";
		else if (m_pDmgRender[i]->m_iDmg == 4)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Four";
		else if (m_pDmgRender[i]->m_iDmg == 5)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Five";
		else if (m_pDmgRender[i]->m_iDmg == 6)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Six";
		else if (m_pDmgRender[i]->m_iDmg == 7)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Seven";
		else if (m_pDmgRender[i]->m_iDmg == 8)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Eight";
		else if (m_pDmgRender[i]->m_iDmg == 9)
			m_pDmgRender[i]->m_pFrameKey = L"MagicDMG_Nine";
	}
	if (m_pDmgRender[2]->m_iDmg == 0)
		m_pDmgRender[2]->m_bDmgRender = false;
	if (m_pDmgRender[2]->m_iDmg == 0 && m_pDmgRender[1]->m_iDmg == 0)
	{
		m_pDmgRender[2]->m_bDmgRender = false;
		m_pDmgRender[1]->m_bDmgRender = false;
	}
}
