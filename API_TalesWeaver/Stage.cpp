#include "stdafx.h"
#include "Stage.h"
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
#include "SoundMgr.h"
#include "KeyMgr.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_She.wav");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Town.bmp", L"Stage_Town");
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Town_Tile.dat");
	if (CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER).empty())
	{
		CObj* pObj = CAFactory<CPlayer>::Create();
		CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::PLAYER);
	}
	if (CWarpGateMgr::Get_Instance()->Get_List(STAGEID::TOWN).empty())
	{
		CWarpGate* pWarp = CAFactory<CWarpGate>::Create_Warp(570.f, 600.f,870.f,740.f);
		pWarp->Set_Warp(SCENEID::SHOP);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::TOWN);
		pWarp = CAFactory<CWarpGate>::Create_Warp(540.f, 1140.f, 1480.f ,840.f);
		pWarp->Set_Warp(SCENEID::FIELD);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::TOWN);
	}
	rc1.left = 1230;
	rc1.top = 840;
	rc1.right = 1290;
	rc1.bottom = 900;
	rc2.left = 570;
	rc2.top = 90;
	rc2.right = 930;
	rc2.bottom = 120;
	rc3.left = 1200;
	rc3.top = 450;
	rc3.right = 1260;
	rc3.bottom = 510;
	m_bLockDoor = true;
	
}

void CStage::Update()
{
	RECT rc = {};
	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	for(auto iter : CObjMgr::Get_Instance()->Get_Player())
		if (static_cast<CPlayer*>(iter)->First_Stage())
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN))
				static_cast<CPlayer*>(iter)->Clear_First_Stage();
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (IntersectRect(&rc, &iter->Get_Check_Rect(), &rc1))
			m_bLockDoor = true;
		else if (IntersectRect(&rc, &iter->Get_Check_Rect(), &rc2))
			m_bLockDoor = true;
		else if (IntersectRect(&rc, &iter->Get_Check_Rect(), &rc3))
			m_bLockDoor = true;
		else
			m_bLockDoor = false;
	}
	CScrollMgr::Get_Instance()->Scroll_Lock(1590, 1200);
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CStage::Render(HDC _DC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stage_Town");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, -iScrollX, -iScrollY, SRCCOPY);

	if (m_bTile)
		CTileMgr::Get_Instance()->Render(_DC,1590/30);
	if (m_bHitbox)
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::PLAYER);
	CWarpGateMgr::Get_Instance()->Render(_DC,STAGEID::TOWN);

	CObjMgr::Get_Instance()->Render(_DC);
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (static_cast<CPlayer*>(iter)->First_Stage())
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"굉장히 한적한 마을이다. 주변을 둘러보자.");
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (m_bLockDoor)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"문이 굉장히 굳게 닫혀있다. 밖으로 나가보자.");
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CStage::Release()
{
}
