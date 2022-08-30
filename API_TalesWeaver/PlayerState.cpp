#include "stdafx.h"
#include "PlayerState.h"
#include "BmpMgr.h"
#include "InterfaceMgr.h"
#include "ScrollMgr.h"

CPlayerState::CPlayerState()
{
}


CPlayerState::~CPlayerState()
{
	Release();
}

void CPlayerState::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/Player_State.bmp", L"Player_State");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/Player_State_lost.bmp", L"Player_State_lost");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/State_Hp.bmp", L"State_Hp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/State_Mp.bmp", L"State_Mp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/State_Sp.bmp", L"State_Sp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/State_Xp.bmp", L"State_Xp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/runwalk.bmp", L"runwalk");
	m_tRect.left = 0;
	m_tRect.top = 0;
	m_tRect.right = 186;
	m_tRect.bottom = 107;
	m_iHpCur = 84.f;
	m_iMpCur = 84.f;
	m_iSpCur = 84.f;
	m_iXpCur = 0.f;
	m_fiCurrentHp = 0;
	m_fiMaximumHp = 0;
	m_fiCurrentMp = 0;
	m_fiMaximumMp = 0;
	m_fiCurrentSp = 0;
	m_fiMaximumSp = 0;
	m_fiCurrentXp = 0;
	m_fiMaximumXp = 0;
	iRW = 0;
	m_bRender = false;
	m_pFrameKey = L"Player_State";

}

void CPlayerState::Render(HDC _DC)
{

	HDC hState = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	HDC hHp = CBmpMgr::Get_Instance()->Find_Bmp(L"State_Hp");
	HDC hMp = CBmpMgr::Get_Instance()->Find_Bmp(L"State_Mp");
	HDC hSp = CBmpMgr::Get_Instance()->Find_Bmp(L"State_Sp");
	HDC hXp = CBmpMgr::Get_Instance()->Find_Bmp(L"State_Xp");
	HDC hRW = CBmpMgr::Get_Instance()->Find_Bmp(L"runwalk");
	SetBkMode(_DC, TRANSPARENT);
	SetTextColor(_DC, RGB(255, 255, 255));
	TCHAR szHP[32] = L"";
	TCHAR szMP[32] = L"";
	TCHAR szSP[32] = L"";
	TCHAR szXP[32] = L"";
	swprintf_s(szHP, L" %d / %d", m_fiCurrentHp, m_fiMaximumHp);
	swprintf_s(szMP, L" %d / %d", m_fiCurrentMp, m_fiMaximumMp);
	swprintf_s(szSP, L" %d / %d", m_fiCurrentSp, m_fiMaximumSp);
	swprintf_s(szXP, L" %.1f / %.1f", m_fiCurrentXp, m_fiMaximumXp);
	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top 
		, 186, 107
		, hState
		, 0, 0
		, 186, 107
		, RGB(255, 255, 255));
	GdiTransparentBlt(_DC
		, 31, 64
		, 12, 11
		, hRW
		, iRW * 12, 0
		, 12, 11
		, RGB(255, 255, 255));
	GdiTransparentBlt(_DC
		, 98,21
		, m_iHpCur, 14
		, hHp
		, 0, 0
		, 84, 14
		, RGB(255, 255, 255));
	TextOut(_DC, 98, 21, szHP, lstrlen(szHP));
	GdiTransparentBlt(_DC
		, 98, 36
		, m_iMpCur, 14
		, hMp
		, 0, 0
		, 84, 14
		, RGB(255, 255, 255));
	TextOut(_DC, 98, 36, szMP, lstrlen(szMP));
	GdiTransparentBlt(_DC
		, 98, 51
		, m_iSpCur, 14
		, hSp
		, 0, 0
		, 84, 14
		, RGB(255, 255, 255));
	TextOut(_DC, 98, 51, szSP, lstrlen(szSP));
	GdiTransparentBlt(_DC
		, 74, 68
		, m_iXpCur, 4
		, hXp
		, 0, 0
		, 107, 4
		, RGB(255, 255, 255));
	TextOut(_DC, 74, 68, szXP, lstrlen(szXP));
	

}

void CPlayerState::Update()
{
}

void CPlayerState::Late_Update()
{
}

void CPlayerState::Release()
{
}

void CPlayerState::Set_Bar(float _hp, float _mp, float _sp, float _xp)
{
	m_iHpCur = _hp;
	m_iMpCur = _mp;
	m_iSpCur = _sp;
	m_iXpCur = _xp;
}

void CPlayerState::Set_State_Num(int _hp, int _maxhp, int _mp, int _maxmp, int _sp, int _maxsp, float _xp, float _maxxp)
{
	m_fiCurrentHp = _hp;
	m_fiMaximumHp = _maxhp;
	m_fiCurrentMp = _mp;
	m_fiMaximumMp = _maxmp;
	m_fiCurrentSp = _sp;
	m_fiMaximumSp = _maxsp;
	m_fiCurrentXp = _xp;
	m_fiMaximumXp = _maxxp;

	if (m_fiCurrentHp <= 100)
		m_pFrameKey = L"Player_State_lost";
	else
		m_pFrameKey = L"Player_State";
}

void CPlayerState::Set_Run(int _a)
{
	iRW = _a;
}
