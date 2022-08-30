#include "stdafx.h"
#include "TileEdit.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"

CTileEdit::CTileEdit()
{
}


CTileEdit::~CTileEdit()
{
	Release();
}

void CTileEdit::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile_Sprite.bmp", L"Tile_Sprite");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Town.bmp", L"Stage_Town");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store.bmp", L"Stage_Store");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Field.bmp", L"Stage_Field");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Field2.bmp", L"Stage_Field2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Boss.bmp", L"Stage_Boss_Room");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/GreenField.bmp", L"Stage_Boss_Hard");
	m_pFrameKey = L"Stage_Town";
	m_pPathFile = L"../Image/Tile/Town_Tile.dat";
	CTileMgr::Get_Instance()->Set_Tile(1590/30, 1200/30);
	CScrollMgr::Get_Instance()->Scroll_Lock(1590,1200);
	iX = 1590 / 30;
	iY = 1200 / 30;
}

void CTileEdit::Update()
{
	POINT pt = {};
	iScrollX = (int)(CScrollMgr::Get_Instance()->Get_ScrollX());
	iScrollY = (int)(CScrollMgr::Get_Instance()->Get_ScrollY());
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= iScrollX;
	pt.y -= iScrollY;

	
	if(CKeyMgr::Get_Instacne()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-5);
	if (CKeyMgr::Get_Instacne()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(5);
	if (CKeyMgr::Get_Instacne()->Key_Pressing(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-5);
	if (CKeyMgr::Get_Instacne()->Key_Pressing(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(+5);

	if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON))
		CTileMgr::Get_Instance()->is_Picking_Tile(iX);
	if (CKeyMgr::Get_Instacne()->Key_Down(VK_RBUTTON))
		CTileMgr::Get_Instance()->is_Picking_Tile_Down(iX);
	
	if (CKeyMgr::Get_Instacne()->Key_Down('A'))
		CTileMgr::Get_Instance()->Save_Tile(m_pPathFile);
	if (CKeyMgr::Get_Instacne()->Key_Down('S'))
		CTileMgr::Get_Instance()->Load_Tile(m_pPathFile);

	if (CKeyMgr::Get_Instacne()->Key_Down('1'))
		Change_Scene_Stage();
	if (CKeyMgr::Get_Instacne()->Key_Down('2'))
		Change_Scene_Shop();
	if (CKeyMgr::Get_Instacne()->Key_Down('3'))
		Change_Scene_Field();
	if (CKeyMgr::Get_Instacne()->Key_Down('4'))
		Change_Scene_Field2();
	if (CKeyMgr::Get_Instacne()->Key_Down('5'))
		Change_Scene_Boss_Room();
	if (CKeyMgr::Get_Instacne()->Key_Down('6'))
		Change_Scene_Boss_Hard();

	if (CKeyMgr::Get_Instacne()->Key_Down(VK_BACK))
		Change_Main();

}

void CTileEdit::Late_Update()
{
}

void CTileEdit::Render(HDC _DC)
{
	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, -iScrollX, -iScrollY, SRCCOPY);
	for (auto& Stage : CTileMgr::Get_Instance()->Get_Tile())
		Stage->Render(_DC);
}

void CTileEdit::Release()
{
}

void CTileEdit::Change_Scene_Stage()
{
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->Set_Tile(1590 / 30, 1200 / 30);
	m_pFrameKey = L"Stage_Town";
	m_pPathFile = L"../Image/Tile/Town.Tile.dat";
	CScrollMgr::Get_Instance()->Scroll_Lock(1590, 1200);
	iX = 1590 / 30;
	iY = 1200 / 30;
}

void CTileEdit::Change_Scene_Shop()
{
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->Set_Tile(1390 / 30, 870 / 30);
	m_pFrameKey = L"Stage_Store";
	m_pPathFile = L"../Image/Tile/Store_Tile.dat";
	CScrollMgr::Get_Instance()->Scroll_Lock(1390, 870);
	iX = 1390 / 30;
	iY = 870 / 30;
}

void CTileEdit::Change_Scene_Field()
{
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->Set_Tile(2490 /30, 1290 /30);
	m_pFrameKey = L"Stage_Field";
	m_pPathFile = L"../Image/Tile/Field_Tile.dat";
	CScrollMgr::Get_Instance()->Scroll_Lock(2490, 1290);
	iX = 2490 / 30;
	iY = 1290 / 30;
}

void CTileEdit::Change_Scene_Field2()
{
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->Set_Tile(2490 / 30, 1290 / 30);
	m_pFrameKey = L"Stage_Field2";
	m_pPathFile = L"../Image/Tile/Field2_Tile.dat";
	CScrollMgr::Get_Instance()->Scroll_Lock(2490, 1290);
	iX = 2490 / 30;
	iY = 1290 / 30;
}

void CTileEdit::Change_Scene_Boss_Room()
{
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->Set_Tile(2490 / 30, 1290 / 30);
	m_pFrameKey = L"Stage_Boss_Room";
	m_pPathFile = L"../Image/Tile/Boss_Room_Tile.dat";
	CScrollMgr::Get_Instance()->Scroll_Lock(2490, 1290);
	iX = 2490 / 30;
	iY = 1290 / 30;
}

void CTileEdit::Change_Scene_Boss_Hard()
{
	CTileMgr::Get_Instance()->Release();
	CTileMgr::Get_Instance()->Set_Tile(1620 / 30, 1080 / 30);
	m_pFrameKey = L"Stage_Boss_Hard";
	m_pPathFile = L"../Image/Tile/Boss_Hard_Tile.dat";
	CScrollMgr::Get_Instance()->Scroll_Lock(1620, 1080);
	iX = 1620 / 30;
	iY = 1080 / 30;
}

void CTileEdit::Change_Main()
{
	CSceneMgr::Get_Instance()->Scene_Change(SCENEID::MENU);
}
