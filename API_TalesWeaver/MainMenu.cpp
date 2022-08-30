#include "stdafx.h"
#include "MainMenu.h"
#include "BALButton.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "BmpMgr.h"
#include "BALButton.h"

CMainMenu::CMainMenu()
{
}


CMainMenu::~CMainMenu()
{
	Release();
}

void CMainMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Logo/MainGame.bmp", L"Main");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Credit.bmp", L"Credit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"BGM_Town.wav");
	iStart = 0;
	iCredit = 0;
	iExit = 0;

	Start.left = 100;
	Start.top = 500;
	Start.right = 200;
	Start.bottom = 530;
	Credit.left = 350;
	Credit.top = 500;
	Credit.right = 450;
	Credit.bottom = 530;
	Exit.left = 600;
	Exit.top = 500;
	Exit.right = 700;
	Exit.bottom = 530;
}

void CMainMenu::Update()
{
	POINT pt = {};
	RECT rc = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (PtInRect(&Start, pt))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OntheMenu.wav", CSoundMgr::BUTTON);
		iStart = 1;
		if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"ClicktheMenu.wav", CSoundMgr::CLICKBUTTON);
			CSceneMgr::Get_Instance()->Scene_Change(SCENEID::STAGE);
		}

	}
	else
		iStart = 0;

	if (PtInRect(&Credit, pt))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OntheMenu.wav", CSoundMgr::BUTTON);
		iCredit = 1;
		if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"ClicktheMenu.wav", CSoundMgr::CLICKBUTTON);
			CSceneMgr::Get_Instance()->Scene_Change(SCENEID::EDIT);
		}

	}
	else
		iCredit = 0;

	if (PtInRect(&Exit, pt))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OntheMenu.wav", CSoundMgr::BUTTON);
		iExit = 1;
		if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"ClicktheMenu.wav", CSoundMgr::CLICKBUTTON);
			DestroyWindow(g_hWnd);
		}
	}
	else
		iExit = 0;
	if(CKeyMgr::Get_Instacne()->Key_Down('A'))
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::STAGE);
	if(CKeyMgr::Get_Instacne()->Key_Down('S'))
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::EDIT);

}

void CMainMenu::Late_Update()
{
}

void CMainMenu::Render(HDC _DC)
{

	HDC hStageDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Main");
	BitBlt(_DC, 0, 0, WINCX, WINCY, hStageDC, 0, 0, SRCCOPY);

	HDC hButton = CBmpMgr::Get_Instance()->Find_Bmp(L"Start");
	GdiTransparentBlt(_DC
		, Start.left, Start.top
		, 100, 30
		, hButton
		, iStart * 100, 0
		, 100, 30
		, RGB(255, 255, 255));
	HDC hButton2 = CBmpMgr::Get_Instance()->Find_Bmp(L"Credit");
	GdiTransparentBlt(_DC
		, Credit.left, Credit.top
		, 100, 30
		, hButton2
		, iCredit * 100, 0
		, 100, 30
		, RGB(255, 255, 255));
	HDC hButton3 = CBmpMgr::Get_Instance()->Find_Bmp(L"Exit");
	GdiTransparentBlt(_DC
		, Exit.left, Exit.top
		, 100, 30
		, hButton3
		, iExit * 100, 0
		, 100, 30
		, RGB(255, 255, 255));
}

void CMainMenu::Release()
{
}
