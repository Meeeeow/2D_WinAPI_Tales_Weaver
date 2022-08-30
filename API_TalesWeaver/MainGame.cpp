#include "stdafx.h"
#include "MainGame.h"

#include "Obj.h"
#include "Player.h"
#include "ObjMgr.h"

#include "TileMgr.h"

#include "KeyMgr.h"

#include "BmpMgr.h"

#include "ScrollMgr.h"

#include "SceneMgr.h"

#include "Mouse.h"
#include "MouseMgr.h"

#include "WarpGateMgr.h"

#include "Effect.h"
#include "EffectMgr.h"

#include "SoundMgr.h"

#include "InterfaceMgr.h"
#include "DropItemMgr.h"
#include "InventoryMgr.h"
#include "EquipMgr.h"

CMainGame::CMainGame()
	:m_iFPS(0), dwTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Background.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Background.bmp", L"BackBuffer");
	CSceneMgr::Get_Instance()->Scene_Change(SCENEID::LOGO);
	CMouseMgr::Get_Instance()->Initialize();
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
	CMouseMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CMouseMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	if (SCENEID::LOGO == CSceneMgr::Get_Instance()->Get_SceneID() || SCENEID::YOUDIED == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Back");
	HDC hBackBufferDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BackBuffer");

	BitBlt(hBackBufferDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hBackBufferDC);
	CMouseMgr::Get_Instance()->Render(hBackBufferDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);

#ifdef _DEBUG
	++m_iFPS;

	if (dwTime + 1000 < GetTickCount())
	{
		TCHAR	szFPS[64] = L"";
		swprintf_s(szFPS, L"내가 만들어가는 이야기 'Tales Weaver'  [FPS: %d]", m_iFPS);
		SetWindowText(g_hWnd, szFPS);

		m_iFPS = 0;
		dwTime = GetTickCount();
	}
#endif // _DEBUG
}

void CMainGame::Release()
{

	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CMouseMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CSceneMgr::Destory_Instance();
	CWarpGateMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CInterfaceMgr::Destroy_Instance();
	CDropItemMgr::Destroy_Instance();
	CInventoryMgr::Destroy_Instance();
	CEquipMgr::Destroy_Instance();
	CEffectMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
