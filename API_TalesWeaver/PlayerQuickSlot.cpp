#include "stdafx.h"
#include "PlayerQuickSlot.h"
#include "BmpMgr.h"
#include "InterfaceMgr.h"
#include "ScrollMgr.h"
#include "InventoryMgr.h"

CPlayerQuickSlot::CPlayerQuickSlot()
{
}


CPlayerQuickSlot::~CPlayerQuickSlot()
{
}

void CPlayerQuickSlot::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/Quick_Slot.bmp", L"Quick_Slot");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/ICON_Spin.bmp", L"ICON_Spin");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/ICON_Fireball.bmp", L"ICON_Fireball");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/ICON_Explosion.bmp", L"ICON_Explosion");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/RedHub.bmp", L"RedHub");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/BlueHub.bmp", L"BlueHub");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/GreenHub.bmp", L"GreenHub");

	m_tRect.bottom =600;
	m_tRect.top = 600 - 86;
	m_tRect.left = 0;
	m_tRect.right = 103;
	m_bRender = false;
}

void CPlayerQuickSlot::Render(HDC _DC)
{
	HDC hSlot = CBmpMgr::Get_Instance()->Find_Bmp(L"Quick_Slot");
	HDC hConA = CBmpMgr::Get_Instance()->Find_Bmp(L"ICON_Spin");
	HDC hConB = CBmpMgr::Get_Instance()->Find_Bmp(L"ICON_Fireball");
	HDC hConC = CBmpMgr::Get_Instance()->Find_Bmp(L"ICON_Explosion");
	HDC hHubR = CBmpMgr::Get_Instance()->Find_Bmp(L"RedHub");
	HDC hHubB = CBmpMgr::Get_Instance()->Find_Bmp(L"BlueHub");
	HDC hHubG = CBmpMgr::Get_Instance()->Find_Bmp(L"GreenHub");
	
	GdiTransparentBlt(_DC
		, m_tRect.left,m_tRect.top
		, 103, 86
		, hSlot
		, 0, 0
		, 103, 86
		, RGB(255, 255, 255));
	GdiTransparentBlt(_DC
		, m_tRect.left + 10, m_tRect.top + 15
		, 24, 24
		, hConA
		, 0, 0
		, 24, 24
		, RGB(255, 255, 255));
	GdiTransparentBlt(_DC
		, m_tRect.left + 40, m_tRect.top + 15
		, 24, 24
		, hConB
		, 0, 0
		, 24, 24
		, RGB(255, 255, 255));
	GdiTransparentBlt(_DC
		, m_tRect.left + 70, m_tRect.top + 15
		, 24, 24
		, hConC
		, 0, 0
		, 24, 24
		, RGB(255, 255, 255));
	GdiTransparentBlt(_DC
		, m_tRect.left + 10, m_tRect.top + 59
		, 24, 24
		, hHubR
		, 0, 0
		, 24, 24
		, RGB(255, 255, 255));
	TCHAR rHub[32] = L"";
	swprintf_s(rHub, L"%d", CInventoryMgr::Get_Instance()->Find_Item_Count(L"빨간 허브"));
	TextOut(_DC, m_tRect.left + 15, m_tRect.top + 59, rHub, lstrlen(rHub));
	GdiTransparentBlt(_DC
		, m_tRect.left + 40, m_tRect.top + 59
		, 24, 24
		, hHubB
		, 0, 0
		, 24, 24
		, RGB(255, 255, 255));
	TCHAR bHub[32] = L"";
	swprintf_s(bHub, L"%d", CInventoryMgr::Get_Instance()->Find_Item_Count(L"파란 허브"));
	TextOut(_DC, m_tRect.left + 45, m_tRect.top + 59, bHub, lstrlen(bHub));
	GdiTransparentBlt(_DC
		, m_tRect.left + 70, m_tRect.top + 59
		, 24, 24
		, hHubG
		, 0, 0
		, 24, 24
		, RGB(255, 255, 255));
	TCHAR gHub[32] = L"";
	swprintf_s(gHub, L"%d", CInventoryMgr::Get_Instance()->Find_Item_Count(L"초록 허브"));
	TextOut(_DC, m_tRect.left + 75, m_tRect.top + 59, gHub, lstrlen(gHub));

}

void CPlayerQuickSlot::Update()
{
}

void CPlayerQuickSlot::Late_Update()
{
}

void CPlayerQuickSlot::Release()
{
}
