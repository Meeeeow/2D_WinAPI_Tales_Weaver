#include "stdafx.h"
#include "Field2.h"
#include "BmpMgr.h"
#include "WarpGate.h"
#include "WarpGateMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"
#include "Gargoyle.h"
#include "Player.h"
#include "KeyMgr.h"
#include "DropItemMgr.h"

CField2::CField2()
{
}


CField2::~CField2()
{
	Release();
}

void CField2::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Field2.bmp", L"Stage_Field2");
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Field2_Tile.dat");
	if (CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER2).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CGargoyle>::Create_Monster(1104, 800), OBJID::MONSTER2);
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CGargoyle>::Create_Monster(1800, 650), OBJID::MONSTER2);
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CGargoyle>::Create_Monster(1255, 800), OBJID::MONSTER2);
	}
	if (CWarpGateMgr::Get_Instance()->Get_List(STAGEID::FIELD2).empty())
	{
		CWarpGate* pWarp = CAFactory<CWarpGate>::Create_Warp(1710.f, 890.f, 690.f, 500.f);
		pWarp->Set_Warp(SCENEID::FIELD);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::FIELD2);
		pWarp = CAFactory<CWarpGate>::Create_Warp(1150.f, 360.f, 1600.f, 800.f);
		pWarp->Set_Warp(SCENEID::BOSS);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::FIELD2);
	}
	m_dGenCool = GetTickCount();
}

void CField2::Update()
{
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
		if (static_cast<CPlayer*>(iter)->Third_Stage())
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN))
				static_cast<CPlayer*>(iter)->Clear_Third_Stage();

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(2490, 1290);

	if (m_dGenCool + 11000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CGargoyle>::Create_Monster(1100 + rand() % 400, 500 + rand() % 200), OBJID::MONSTER2);
		m_dGenCool = GetTickCount();
	}
}

void CField2::Late_Update()
{
}

void CField2::Render(HDC _DC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stage_Field2");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, -iScrollX, -iScrollY, SRCCOPY);

	if (m_bTile)
		CTileMgr::Get_Instance()->Render(_DC, 2490 / 30);
	if (m_bHitbox)
	{
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::MONSTER2);
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::PLAYER);
	}

	CWarpGateMgr::Get_Instance()->Render(_DC, STAGEID::FIELD2);
	CObjMgr::Get_Instance()->Monster_Render(_DC,OBJID::MONSTER2);
	CDropItemMgr::Get_Instance()->Render(_DC, DROPID::FIELD2);
	CObjMgr::Get_Instance()->Render(_DC);
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (static_cast<CPlayer*>(iter)->Third_Stage())
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"아까 그 고양이가 말한 가고일 인 것 같다. 외피가 단단해보인다.");
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CField2::Release()
{
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::MAGICDMG);
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::PLAYERDMG);
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::MONSTERDMG);
}
