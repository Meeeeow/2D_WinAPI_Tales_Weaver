#include "stdafx.h"
#include "Field.h"
#include "BmpMgr.h"
#include "WarpGate.h"
#include "WarpGateMgr.h"
#include "TileMgr.h"
#include "Tile.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "JellyBee.h"
#include "EffectMgr.h"
#include "DropItemMgr.h"
#include "KeyMgr.h"
#include "Player.h"

CField::CField()
{

}


CField::~CField()
{
	Release();
}

void CField::Initialize()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Fresh_Blood.wav");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Field.bmp", L"Stage_Field");
	CTileMgr::Get_Instance()->Load_Tile(L"../Image/Tile/Field_Tile.dat");
	if (CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER).empty())
	{
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CJellyBee>::Create_Monster(1104, 800), OBJID::MONSTER);
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CJellyBee>::Create_Monster(2000, 800), OBJID::MONSTER);
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CJellyBee>::Create_Monster(1255, 800), OBJID::MONSTER);
	}
	if (CWarpGateMgr::Get_Instance()->Get_List(STAGEID::FIELD).empty())
	{
		CWarpGate* pWarp = CAFactory<CWarpGate>::Create_Warp(1740.f, 920.f, 720.f, 900.f);
		pWarp->Set_Warp(SCENEID::STAGE);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::FIELD);
		pWarp = CAFactory<CWarpGate>::Create_Warp(830.f, 390.f, 1600.f, 800.f);
		pWarp->Set_Warp(SCENEID::FIELD2);
		CWarpGateMgr::Get_Instance()->Add_Gate(pWarp, STAGEID::FIELD);
	}
	m_dGenCool = GetTickCount();
}

void CField::Update()
{
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
		if (static_cast<CPlayer*>(iter)->Second_Stage())
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN))
				static_cast<CPlayer*>(iter)->Clear_Second_Stage();

	CObjMgr::Get_Instance()->Update();
	CTileMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock(2490, 1290);

	if (m_dGenCool + 15000 < GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(CAFactory<CJellyBee>::Create_Monster(1100 + rand()%400, 500+rand()%200), OBJID::MONSTER);
		m_dGenCool = GetTickCount();
	}
}

void CField::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CField::Render(HDC _DC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stage_Field");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, -iScrollX, -iScrollY, SRCCOPY);

	if (m_bTile)
		CTileMgr::Get_Instance()->Render(_DC, 2490 / 30);
	if (m_bHitbox)
	{
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::PLAYER);
		CObjMgr::Get_Instance()->Hitbox_Render(_DC, OBJID::MONSTER);
	}

	CWarpGateMgr::Get_Instance()->Render(_DC, STAGEID::FIELD);
	CObjMgr::Get_Instance()->Monster_Render(_DC,OBJID::MONSTER);
	CDropItemMgr::Get_Instance()->Render(_DC,DROPID::FIELD);
	CObjMgr::Get_Instance()->Render(_DC);
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (static_cast<CPlayer*>(iter)->Second_Stage())
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"±Í¿©¿î Á©¸®»ßµéÀÌ ÀÖ´Ù. Á×ÀÌ°í ¾ÕÀ¸·Î ³ª¾Æ°¡º¸ÀÚ.");
			TextOut(_DC, iter->Get_Hit_Box().left + iScrollX, iter->Get_Hit_Box().top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CField::Release()
{
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::MAGICDMG);
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::PLAYERDMG);
	CEffectMgr::Get_Instance()->Delete_Font(EFFECTID::MONSTERDMG);
}
