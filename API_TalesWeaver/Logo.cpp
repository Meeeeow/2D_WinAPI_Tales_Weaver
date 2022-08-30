#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"
#include "Effect.h"
#include "Hit.h"
#include "Spin.h"
#include "PlayerLevelUp.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();
	CEffectMgr::Get_Instance()->Add_Effect(CAFactory<CPlayerLevelUp>::Create_Effect(), EFFECTID::LEVELUP);
	CEffectMgr::Get_Instance()->Add_Effect(CAFactory<CHit>::Create_Effect(), EFFECTID::HIT);
	CEffectMgr::Get_Instance()->Add_Effect(CAFactory<CSpin>::Create_Effect(), EFFECTID::SPIN);
	m_hVideo = MCIWndCreate(g_hWnd, NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR
		, L"../Image/Logo/Intro.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

}

void CLogo::Update()
{
	if(CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN))
		MCIWndPlay(m_hVideo);
}

void CLogo::Late_Update()
{
	if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN)
		|| MCIWndGetPosition(m_hVideo) >= MCIWndGetLength(m_hVideo))
	{
		MCIWndClose(m_hVideo);

		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::MENU);
		return;
	}
}

void CLogo::Render(HDC _DC)
{
	//HDC hLogoDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Logo");

	//BitBlt(_DC, 0, 0, WINCX, WINCY, hLogoDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
	//MCIWndClose(m_hVideo);
}
