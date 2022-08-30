#include "stdafx.h"
#include "YouDied.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"
#include "Effect.h"
#include "Hit.h"
#include "Spin.h"

CYouDied::CYouDied()
{
}


CYouDied::~CYouDied()
{
	Release();
}

void CYouDied::Initialize()
{
	CSoundMgr::Get_Instance()->StopAll();

	m_hVideo = MCIWndCreate(g_hWnd, NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR
		, L"../Image/Logo/You_Dead.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

void CYouDied::Update()
{
}

void CYouDied::Late_Update()
{
	if (CKeyMgr::Get_Instacne()->Key_Down(VK_RETURN)
		|| MCIWndGetPosition(m_hVideo) >= MCIWndGetLength(m_hVideo))
	{
		Release();
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::STAGE);
		return;
	}
}

void CYouDied::Render(HDC _DC)
{
}

void CYouDied::Release()
{
	MCIWndClose(m_hVideo);
}
