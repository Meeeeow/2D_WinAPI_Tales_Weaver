#include "stdafx.h"
#include "BossHard.h"
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
#include "BlueWolf.h"
#include "Boss_Hard.h"

CBossHard::CBossHard()
{

}


CBossHard::~CBossHard()
{
	Release();
}

void CBossHard::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Its_Over.wav");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/GreenField.bmp", L"Stage_Boss_Hard");
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Boss_Hard_Tile.dat");
	if (CObjMgr::Get_Instance()->Get_List(OBJID::BOSS_HARD).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CBoss_Hard>::Create_Monster(810, 540), OBJID::BOSS_HARD);
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CBlueWolf>::Create_Monster(700, 540), OBJID::BOSS_HARD);
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CBlueWolf>::Create_Monster(900, 440), OBJID::BOSS_HARD);
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CBlueWolf>::Create_Monster(700, 700), OBJID::BOSS_HARD);
	}

	
}

void CBossHard::Update()
{
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
		if (static_cast<CPlayer*>(iter)->Boss_Hard_Stage())
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN))
				static_cast<CPlayer*>(iter)->Clear_Boss_Hard_Stage();

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(1620, 1080);
	
}

void CBossHard::Late_Update()
{
}

void CBossHard::Render(HDC _DC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stage_Boss_Hard");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, -iScrollX, -iScrollY, SRCCOPY);

	if (m_bTile)
		CTileMgr::Get_Instance()->Render(_DC, 1620 / 30);
	if (m_bHitbox)
	{
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::BOSS_HARD);
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::PLAYER);
	}
	CWarpGateMgr::Get_Instance()->Render(_DC, STAGEID::BOSS_HARD);
	CObjMgr::Get_Instance()->Monster_Render(_DC, OBJID::BOSS_HARD);
	CObjMgr::Get_Instance()->Render(_DC);

	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (static_cast<CPlayer*>(iter)->Boss_Hard_Stage())
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"저 녀석이 이 일의 원흉인 것 같다.");
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CBossHard::Release()
{
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::BOSSFIRE);
}
