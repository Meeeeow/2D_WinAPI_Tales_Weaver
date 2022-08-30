#include "stdafx.h"
#include "WarpGate.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"

CWarpGate::CWarpGate()
{
}


CWarpGate::~CWarpGate()
{
}

void CWarpGate::Initialize(float _x, float _y, float _fX, float _fY)
{
	m_tInfo.fX = _x;
	m_tInfo.fY = _y;
	m_tPosition.x = (LONG)_fX;
	m_tPosition.y = (LONG)_fY;
	m_tInfo.iCX = 90;
	m_tInfo.iCY = 120;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/WarpGate/WarpGate_Sprite.bmp", L"WARPGATE");
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 22;
	m_tFrame.dwDelay = 100;
	m_tFrame.dwTime = GetTickCount();

	Update_Rect();
}

void CWarpGate::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

void CWarpGate::Frame_Update()
{

	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;
		}
	}
}

void CWarpGate::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Frame_Update();
	HDC hGateDC = CBmpMgr::Get_Instance()->Find_Bmp(L"WARPGATE");

	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, 90, 120
		, hGateDC
		, m_tFrame.iStartX * 150, 0
		, 90, 120
		, RGB(255, 255, 255));
	Stage_Move();
}

void CWarpGate::Stage_Move()
{
	RECT rc = {};
	
	if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER), &m_tRect))
	{
		for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER))
			iter->Set_Pos((float)m_tPosition.x, (float)m_tPosition.y);
		CSceneMgr::Get_Instance()->Scene_Change(WarpStage);
	}
}

