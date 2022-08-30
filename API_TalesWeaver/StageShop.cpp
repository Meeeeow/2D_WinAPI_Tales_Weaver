#include "stdafx.h"
#include "StageShop.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "Player.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "Tile.h"
#include "TileMgr.h"
#include "Mouse.h"
#include "WarpGate.h"
#include "WarpGateMgr.h"
#include "Happy.h"
#include "KeyMgr.h"

CStageShop::CStageShop()
{
}


CStageShop::~CStageShop()
{
	Release();
}

void CStageShop::Initialize()
{
	if (CObjMgr::Get_Instance()->Get_List(OBJID::NPC).empty())
	{
		CObj* pObj = CAFactory<CHappy>::Create();
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::NPC);
	}
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Store.bmp", L"Stage_Store");
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Store_Tile.dat");
	if (CWarpGateMgr::Get_Instance()->Get_List(STAGEID::SHOP).empty())
	{
		CWarpGate* pWarp = CAFactory<CWarpGate>::Create_Warp(980, 780.f,700.f,700.f);
		pWarp->Set_Warp(SCENEID::STAGE);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::SHOP);
	}
}

void CStageShop::Update()
{
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
		if (static_cast<CPlayer*>(iter)->Shop_Stage())
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN))
				static_cast<CPlayer*>(iter)->Clear_Shop_Stage();

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(1390, 870);
}

void CStageShop::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStageShop::Render(HDC _DC)
{

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stage_Store");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, -iScrollX, -iScrollY, SRCCOPY);
	if (m_bTile)
		CTileMgr::Get_Instance()->Render(_DC, 1390 / 30);
	if (m_bHitbox)
		CObjMgr::Get_Instance()->Hitbox_Render(_DC,OBJID::PLAYER);
	CWarpGateMgr::Get_Instance()->Render(_DC,STAGEID::SHOP);
	CObjMgr::Get_Instance()->Monster_Render(_DC, OBJID::NPC);
	CObjMgr::Get_Instance()->Render(_DC);
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (static_cast<CPlayer*>(iter)->Shop_Stage())
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"귀여운 고양이가 쳐다보고 있다. 다가가 보자.");
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CStageShop::Release()
{
}
