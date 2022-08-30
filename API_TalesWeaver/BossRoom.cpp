#include "stdafx.h"
#include "BossRoom.h"
#include "BmpMgr.h"
#include "WarpGate.h"
#include "WarpGateMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"
#include "Boss_Normal.h"
#include "Gargoyle.h"
#include "Player.h"
#include "KeyMgr.h"
#include "DropItemMgr.h"

CBossRoom::CBossRoom()
{
}


CBossRoom::~CBossRoom()
{
	Release();
}

void CBossRoom::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Fresh_Blood.wav");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Boss.bmp", L"Stage_Boss_Room");
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Boss_Room_Tile.dat");
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (static_cast<CPlayer*>(iter)->Boss_Normal_Stage())
			if (CObjMgr::Get_Instance()->Get_List(OBJID::BOSS).empty())
				CObjMgr::Get_Instance()->Add_Object(CAFactory<CBoss_Normal>::Create_Monster(1245, 645), OBJID::BOSS);
	}

	if (CWarpGateMgr::Get_Instance()->Get_List(STAGEID::BOSS).empty())
	{
		CWarpGate* pWarp = CAFactory<CWarpGate>::Create_Warp(1740.f, 920.f, 690.f, 900.f);
		pWarp->Set_Warp(SCENEID::FIELD2);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::BOSS);
	}
}

void CBossRoom::Update()
{
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
		if (static_cast<CPlayer*>(iter)->Boss_Normal_Stage())
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN))
				static_cast<CPlayer*>(iter)->Clear_Boss_Normal_Stage();

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(2490, 1290);
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (!static_cast<CPlayer*>(iter)->Boss_Check()&& CObjMgr::Get_Instance()->Get_List(OBJID::BOSS).empty())
		{
			static_cast<CPlayer*>(iter)->Clear_Boss();
			CWarpGate* pWarp = CAFactory<CWarpGate>::Create_Warp(800.f, 600.f, 1400.f, 900.f);
			pWarp->Set_Warp(SCENEID::BOSS_HARD);
			CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::BOSS);
		}
	}
}

void CBossRoom::Late_Update()
{
}

void CBossRoom::Render(HDC _DC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stage_Boss_Room");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, -iScrollX, -iScrollY, SRCCOPY);

	if (m_bTile)
		CTileMgr::Get_Instance()->Render(_DC, 2490 / 30);
	if (m_bHitbox)
	{
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::BOSS);
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::PLAYER);
	}
	CDropItemMgr::Get_Instance()->Render(_DC, DROPID::BOSS_ROOM);
	CWarpGateMgr::Get_Instance()->Render(_DC, STAGEID::BOSS);
	CObjMgr::Get_Instance()->Monster_Render(_DC, OBJID::BOSS);
	CObjMgr::Get_Instance()->Render(_DC);

	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (static_cast<CPlayer*>(iter)->Boss_Normal_Stage())
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"저 해골 녀석을 해치우면 앞으로 나아갈 수 있을 것 같다.");
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CBossRoom::Release()
{
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::MAGICDMG);
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::PLAYERDMG);
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::MONSTERDMG);
}
