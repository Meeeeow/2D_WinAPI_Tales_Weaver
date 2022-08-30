#include "stdafx.h"
#include "PlayerEquip.h"
#include "BmpMgr.h"
#include "InterfaceMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "InventoryMgr.h"
#include "EquipMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "SoundMgr.h"

CPlayerEquip::CPlayerEquip()
{
}


CPlayerEquip::~CPlayerEquip()
{
}

void CPlayerEquip::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/equipbar.bmp", L"Equipbar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/equip.bmp", L"Equip");
	rc.left = 782;
	rc.top = 103;
	rc.right = 800;
	rc.bottom = 154;
	Equip.left = 587;
	Equip.top = 103;
	Equip.right = 782;
	Equip.bottom = 285;
	m_iBar = 0;
	m_bRender = false;
	m_bHentai = false;
}

void CPlayerEquip::Render(HDC _DC)
{
	int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hBar = CBmpMgr::Get_Instance()->Find_Bmp(L"Equipbar");
	if (m_bRender)
	{
		HDC hInven = CBmpMgr::Get_Instance()->Find_Bmp(L"Equip");
		GdiTransparentBlt(_DC
			, Equip.left, Equip.top
			, 195, 182
			, hInven
			, 0, 0
			, 195, 182
			, RGB(255, 255, 255));
		CEquipMgr::Get_Instance()->Render(_DC, Equip);
	}
	if (m_bHentai)
	{
		for (auto iter : CObjMgr::Get_Instance()->Get_Player())
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));
			TCHAR szBuff[64] = L"변태도 아니고, 밖에서 옷을 벗을 순 없어.";
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
			if (m_tHentai + 3000 < GetTickCount())
			{
				m_bHentai = false;
			}
		}
	}
	GdiTransparentBlt(_DC
		, rc.left, rc.top
		, 18, 51
		, hBar
		, m_iBar * 18, 0
		, 18, 51
		, RGB(255, 255, 255));
}

void CPlayerEquip::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&rc, pt))
		if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"IdenClick.wav", CSoundMgr::UI);
			m_bRender = !m_bRender;
		}
	if (m_bRender)
	{
		if (PtInRect(&Equip, pt))
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_RBUTTON))
			{
				m_bHentai = true;
				m_tHentai = GetTickCount();
			}
	}

	if (m_bRender)
		m_iBar = 1;
	else
		m_iBar = 0;
}

void CPlayerEquip::Late_Update()
{
}

void CPlayerEquip::Release()
{
}
