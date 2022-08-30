#include "stdafx.h"
#include "PlayerInventory.h"
#include "BmpMgr.h"
#include "InterfaceMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "InventoryMgr.h"
#include "SoundMgr.h"
CPlayerInventory::CPlayerInventory()
{
}


CPlayerInventory::~CPlayerInventory()
{
	Release();
}

void CPlayerInventory::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/invenbar.bmp", L"Invenbar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/inven.bmp", L"Inven");
	rc.left = 782;
	rc.top = 52;
	rc.right = 800;
	rc.bottom = 103;
	Inven.left = 439;
	Inven.top = 52;
	Inven.right = 766;
	Inven.bottom = 450;
	// 343 398
	m_bRender = false;
}

void CPlayerInventory::Render(HDC _DC)
{
	HDC hBar = CBmpMgr::Get_Instance()->Find_Bmp(L"Invenbar");
	if (m_bRender)
	{
		HDC hInven = CBmpMgr::Get_Instance()->Find_Bmp(L"Inven");
		GdiTransparentBlt(_DC
			, Inven.left, Inven.top
			, 343, 398
			, hInven
			, 0, 0
			, 343, 398
			, RGB(255, 255, 255));
		CInventoryMgr::Get_Instance()->Render2(_DC, Inven);
	}
	GdiTransparentBlt(_DC
		, rc.left, rc.top
		, 18, 51
		, hBar
		, m_iBar * 18, 0
		, 18, 51
		, RGB(255, 255, 255));
}

void CPlayerInventory::Update()
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
		m_iBar = 1;
	else
		m_iBar = 0;
}

void CPlayerInventory::Late_Update()
{
}

void CPlayerInventory::Release()
{
}
