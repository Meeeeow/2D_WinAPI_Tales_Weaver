#include "stdafx.h"
#include "BALButton.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CBALButton::CBALButton()
{
}


CBALButton::~CBALButton()
{
}

void CBALButton::Set_Pos(float _x, float _y)
{
	m_tRect.left = _x;
	m_tRect.top = _y;
	m_tRect.right = _x + 50;
	m_tRect.bottom = _y + 30;
}

void CBALButton::Update_Rect()
{
	
}

void CBALButton::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	m_pFrameKey = L"Start";
	m_ibar = 0;
}

int CBALButton::Update()
{
	POINT pt = {};
	RECT rc = {};
	GetCursorPos(&pt);

	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"OntheMenu.wav",CSoundMgr::BUTTON);
		m_ibar = 1;
	}
	else
		m_ibar = 0;


	return 0;
}

void CBALButton::Late_Update()
{

}

void CBALButton::Render(HDC _DC)
{
	HDC hButton = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top
		, 50, 30
		, hButton
		, m_ibar * 50, 0
		, 50, 30
		, RGB(255, 255, 255));
}
