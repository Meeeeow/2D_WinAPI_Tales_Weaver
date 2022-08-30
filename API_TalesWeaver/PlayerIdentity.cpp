#include "stdafx.h"
#include "PlayerIdentity.h"
#include "BmpMgr.h"
#include "InterfaceMgr.h"
#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

CPlayerIdentity::CPlayerIdentity()
{
	ZeroMemory(&rc, sizeof(rc));
}


CPlayerIdentity::~CPlayerIdentity()
{
	Release();
}

void CPlayerIdentity::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/Face.bmp", L"Face");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/Face_lost.bmp", L"Face_lost");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/identity.bmp", L"Iden");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/identity_xp.bmp", L"Iden_xp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Interface/identitybar.bmp", L"Iden_Bar");
	m_bRender = false;
	rc.left = 782;
	rc.top = 0;
	rc.right = 800;
	rc.bottom = 51;
	Iden.left = 481;
	Iden.top = 0;
	Iden.right = 782;
	Iden.bottom = 165;
}

void CPlayerIdentity::Render(HDC _DC)
{
	HDC hBar = CBmpMgr::Get_Instance()->Find_Bmp(L"Iden_Bar");
	if (m_bRender)
	{
		HDC hIDEN = CBmpMgr::Get_Instance()->Find_Bmp(L"Iden");
		HDC hFace = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
		HDC hXp = CBmpMgr::Get_Instance()->Find_Bmp(L"Iden_xp");
		SetBkMode(_DC, TRANSPARENT);
		SetTextColor(_DC, RGB(255, 255, 255));
		TCHAR szLevel[16] = L"";
		TCHAR szHP[32] = L"";
		TCHAR szMP[32] = L"";
		TCHAR szSP[32] = L"";
		TCHAR szXP[32] = L"";
		TCHAR szDMG[32] = L"";
		TCHAR szDEF[32] = L"";
		TCHAR* name = L"¸Þ±¸¹Ö";
		swprintf_s(szLevel, L"%d", m_iLevel);
		swprintf_s(szHP, L" %d / %d", m_iCurrentHp, m_iMaximumHp);
		swprintf_s(szMP, L" %d / %d", m_iCurrentMp, m_iMaximumMp);
		swprintf_s(szSP, L" %d / %d", m_iCurrentSp, m_iMaximumSp);
		swprintf_s(szXP, L" %.1f                %.1f", m_fCurrentXp, m_fMaximumXp);
		swprintf_s(szDMG, L"%d", m_iDmg);
		swprintf_s(szDEF, L"%d", m_iDef);
		GdiTransparentBlt(_DC
			, Iden.left, Iden.top
			, 301, 165
			, hIDEN
			, 0, 0
			, 301, 165
			, RGB(255, 255, 255));
		GdiTransparentBlt(_DC
			, Iden.left + 3, Iden.top + 25
			, 87, 102
			, hFace
			, 0, 0
			, 87, 102
			, RGB(255, 255, 255));
		GdiTransparentBlt(_DC
			, Iden.left + 34, Iden.top + 152
			, m_iXpBar, 2
			, hXp
			, 0, 0
			, 258, 2
			, RGB(255, 255, 255));
		TextOut(_DC, Iden.left + 139, Iden.top + 22, szLevel, lstrlen(szLevel));
		TextOut(_DC, Iden.left + 139, Iden.top + 42, name, lstrlen(name));
		TextOut(_DC, Iden.left + 139, Iden.top + 62, szDMG, lstrlen(szDMG));
		TextOut(_DC, Iden.left + 139, Iden.top + 78, szDEF, lstrlen(szDEF));
		TextOut(_DC, Iden.left + 139, Iden.top + 95, szHP, lstrlen(szHP));
		TextOut(_DC, Iden.left + 139, Iden.top + 108, szMP, lstrlen(szMP));
		TextOut(_DC, Iden.left + 139, Iden.top + 123, szSP, lstrlen(szSP));
		TextOut(_DC, Iden.left + 70, Iden.top + 138, szXP, lstrlen(szXP));
	}
	GdiTransparentBlt(_DC
		, rc.left, rc.top
		, 18, 51
		, hBar
		, m_iBar * 18, 0
		, 18, 51
		, RGB(255, 255, 255));
}

void CPlayerIdentity::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
//	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
//	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (PtInRect(&rc, pt))
		if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON))
		{
			CSoundMgr::Get_Instance()->PlaySound(L"IdenClick.wav", CSoundMgr::UI);
			m_bRender = !m_bRender;
		}

	if (m_bRender)
		m_iBar = 1;
	else
		m_iBar = 0;
}

void CPlayerIdentity::Late_Update()
{
}

void CPlayerIdentity::Release()
{
}

void CPlayerIdentity::Get_Iden(int _level, int _chp, int _mhp, int _cmp, int _mmp, int _csp, int _msp, float _cxp, float _mxp, int _dmg, int _def)
{
	m_iLevel = _level;
	m_iCurrentHp = _chp;
	m_iMaximumHp = _mhp;
	m_iCurrentMp = _cmp;
	m_iMaximumMp = _mmp;
	m_iCurrentSp = _csp;
	m_iMaximumSp = _msp;
	m_fCurrentXp = _cxp;
	m_fMaximumXp = _mxp;
	m_iDmg = _dmg;
	m_iDef = _def;

	if (m_iCurrentHp <= 100)
		m_pFrameKey = L"Face_lost";
	else
		m_pFrameKey = L"Face";

	
	m_iXpBar = m_fCurrentXp / (m_fMaximumXp / 258.f);

}
