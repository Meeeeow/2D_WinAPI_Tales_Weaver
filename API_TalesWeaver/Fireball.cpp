#include "stdafx.h"
#include "Fireball.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Tile.h"
#include "Obj.h"
#include "JellyBee.h"
#include "SoundMgr.h"
#include "SceneMgr.h"

CFireball::CFireball()
{
}


CFireball::~CFireball()
{
}

void CFireball::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Down.bmp", L"FB_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Up.bmp", L"FB_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Right_Down.bmp", L"FB_Right_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Left_Down.bmp", L"FB_Left_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Right_Up.bmp", L"FB_Right_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Left_Up.bmp", L"FB_Left_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Right.bmp", L"FB_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Fireball/FireBall_Left.bmp", L"FB_Left");
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 3;
	m_tFrame.dwDelay = 200;
	
}

void CFireball::Update()
{
	
	m_tStartPos.x += (5.5f * cosf(m_fAngle));
	m_tStartPos.y -= (5.5f * sinf(m_fAngle));

	m_tRect.left = m_tStartPos.x - 30;
	m_tRect.top = m_tStartPos.y - 30;
	m_tRect.right = m_tStartPos.x + 30;
	m_tRect.bottom = m_tStartPos.y + 30;
	RECT rc = {};
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD)
	{
		for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER))
		{
			if (IntersectRect(&rc, &iter->Get_Hit_Box(), &m_tRect))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Player_FB_Kwang.wav", CSoundMgr::PLAYERFBB);

				m_bRender = false;
				iter->is_Magic_Hit_Check(m_tRect, 150 + (rand() % 50));
			}
		}
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD2)
	{
		for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER2))
		{
			if (IntersectRect(&rc, &iter->Get_Hit_Box(), &m_tRect))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Player_FB_Kwang.wav", CSoundMgr::PLAYERFBB);

				m_bRender = false;
				iter->is_Magic_Hit_Check(m_tRect, 150 + (rand() % 50));
			}
		}
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS)
	{
		for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS))
		{
			if (IntersectRect(&rc, &iter->Get_Hit_Box(), &m_tRect))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Player_FB_Kwang.wav", CSoundMgr::PLAYERFBB);

				m_bRender = false;
				iter->is_Magic_Hit_Check(m_tRect, 150 + (rand() % 50));
			}
		}
	}
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS_HARD)
	{
		for (auto iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS_HARD))
		{
			if (IntersectRect(&rc, &iter->Get_Hit_Box(), &m_tRect))
			{
				CSoundMgr::Get_Instance()->PlaySound(L"Player_FB_Kwang.wav", CSoundMgr::PLAYERFBB);

				m_bRender = false;
				iter->is_Magic_Hit_Check(m_tRect, 150 + (rand() % 50));
			}
		}
	}
}

void CFireball::Render(HDC _DC, const TCHAR * _pFrameKey)
{
	if (m_bRender)
	{
		Update();
		FireBall_Update();

		int iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
		HDC hEffectDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, 60, 60
			, hEffectDC
			, m_tFrame.iStartX * 150, 0
			, 150, 150
			, RGB(255, 255, 255));
	}
}

void CFireball::Release()
{
}

void CFireball::Update_Rect(INFO _rc)
{
}

void CFireball::Check_Vector(CTile * _Tile, float _x, float _y)
{
	m_tEndPos.x = _Tile->Get_Info().fX;
	m_tEndPos.y = _Tile->Get_Info().fY;
	m_tStartPos.x = _x;
	m_tStartPos.y = _y;
	m_bRender = true;
	if (m_tEndPos.x > m_tStartPos.x)
	{
		if (m_tEndPos.y - 30 < m_tStartPos.y && m_tEndPos.y + 30 > m_tStartPos.y)
			m_pFrameKey = L"FB_Right";
		else if (m_tEndPos.y > m_tStartPos.y)
			m_pFrameKey = L"FB_Right_Down";
		else if (m_tEndPos.y < m_tStartPos.y)
			m_pFrameKey = L"FB_Right_Up";
	}
	if (m_tEndPos.x < m_tStartPos.x)
	{
		if (m_tEndPos.y - 30 < m_tStartPos.y && m_tEndPos.y + 30 > m_tStartPos.y)
			m_pFrameKey = L"FB_Left";
		else if (m_tEndPos.y > m_tStartPos.y)
			m_pFrameKey = L"FB_Left_Down";
		else if (m_tEndPos.y < m_tStartPos.y)
			m_pFrameKey = L"FB_Left_Up";
	}
	if (m_tEndPos.y > m_tStartPos.y)
	{
		if (m_tEndPos.x - 30 < m_tStartPos.x && m_tEndPos.x + 30 > m_tStartPos.x)
			m_pFrameKey = L"FB_Down";
	}
	if (m_tEndPos.y < m_tStartPos.y)
	{
		if (m_tEndPos.x - 30 < m_tStartPos.x && m_tEndPos.x + 30 > m_tStartPos.x)
			m_pFrameKey = L"FB_Up";
	}
	float fX = m_tEndPos.x - m_tStartPos.x;
	float fY = m_tEndPos.y - m_tStartPos.y;
	float fDia = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDia);
	if (m_tEndPos.y > m_tStartPos.y)
		m_fAngle *= -1;
}

void CFireball::FireBall_Update()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX > m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;
		}
	}
}

