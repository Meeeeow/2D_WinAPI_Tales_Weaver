#include "stdafx.h"
#include "BlueWolf.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Scene.h"
#include "Mouse.h"
#include "TileMgr.h"
#include "Tile.h"
#include "MouseMgr.h"
#include "WarpGateMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "EffectMgr.h"
#include "Player.h"
#include "Hit.h"
#include "MonsterLifeBar.h"
#include "MonsterDMG.h"
#include "MagicDMG.h"

CBlueWolf::CBlueWolf()
{
	ZeroMemory(&m_tStats, sizeof(m_tStats));
}


CBlueWolf::~CBlueWolf()
{
	Release();
}

void CBlueWolf::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueWolf/BlueWolf_Left_Down.bmp", L"BlueWolf_Left_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueWolf/BlueWolf_Left_Up.bmp", L"BlueWolf_Left_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueWolf/BlueWolf_Right_Down.bmp", L"BlueWolf_Right_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueWolf/BlueWolf_Right_Up.bmp", L"BlueWolf_Right_Up");

	m_tInfo.iCX = 150;
	m_tInfo.iCY = 150;

	m_fSpeed = 1.82f;
	m_bIdle = true;
	m_bTarget_Trace = false;
	m_eCurState = IDLE;
	m_pFrameKey = L"BlueWolf_Left_Down";
	m_iRandomTile = (rand() % (CTileMgr::Get_Instance()->Get_Tile().size()));
	m_tStats.m_iMax_HP = 2500;

	m_tStats.m_iCur_HP = m_tStats.m_iMax_HP;
	m_tStats.Attack_Dmg = 500;
	m_tStats.Attack_Def = 0;
	m_tStats.m_fMax_Exp = 0;
	m_tStats.m_fCur_Exp = m_tStats.m_fMax_Exp;
	m_pLifeBar = new CMonsterLifeBar;
}

int CBlueWolf::Update()
{
	if (m_bDead)
	{
		m_bIdle = false;
		m_eCurState = DEAD;
		if (m_tFrame.iStartX >=1)
		{
			for (auto iter : CObjMgr::Get_Instance()->Get_Player())
				static_cast<CPlayer*>(iter)->Add_Exp(m_tStats.m_fCur_Exp);
			CSoundMgr::Get_Instance()->PlaySound(L"JellyBee_Dead.wav", CSoundMgr::JELLYBEE_DEAD);
			SAFE_DELETE(m_pLifeBar);
			return OBJ_DEAD;
		}
	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS_HARD)
	{
		Update_Rect();
		Update_HitBox();
		Update_Tile_Rect();
		Update_Trace_Range();
		Check_Target_Range();
		Set_Dead();

		static_cast<CMonsterLifeBar*>(m_pLifeBar)->Rect_Update(m_tHitBox);
		Set_Bar();
		if (!m_bTarget_Trace && !m_bHit && m_bIdle)
			Move_Random();
		if (m_bTarget_Trace && !m_bHit && m_bIdle)
			Move_Target();


		Check_Collision();

		Frame_Check();
		Frame_Update();

	}
	return OBJ_NOEVENT;
}

void CBlueWolf::Late_Update()
{
}

void CBlueWolf::Render(HDC _DC)
{
	if (!m_bDead)
	{
		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		HDC hTileDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hTileDC
			, m_tFrame.iStartX * 150, m_tFrame.iState * 150
			, 150, 150
			, RGB(255, 255, 255));
		CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::HIT, L"Monster_Hit");
		CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::MONSTERDMG, L"NONE");
		CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::MAGICDMG, L"NONE");
		m_pLifeBar->Render(_DC);
		if (m_bAtk)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"¾ß¿Ë!");
			TextOut(_DC, m_tHitBox.left + iScrollX, m_tHitBox.top + iScrollY + 30, szBuff, lstrlen(szBuff));
		}
		if (m_bDead)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"¹Ö...");
			TextOut(_DC, m_tHitBox.left + iScrollX, m_tHitBox.top + iScrollY + 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CBlueWolf::Release()
{
	SAFE_DELETE(m_pLifeBar);
}

void CBlueWolf::is_Hit_Check(RECT _Rect, int _Dmg)
{
	RECT rc = {};
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (IntersectRect(&rc, &_Rect, &m_tHitBox))
		{
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_BBok.wav", CSoundMgr::GARGOYLE_HIT);
				CEffect* pObj = CAFactory<CHit>::Create_Effect();
				pObj->Update_Rect(m_tInfo);
				pObj->Render_Start();
				CEffectMgr::Get_Instance()->Add_Effect(pObj, EFFECTID::HIT);
				int DMG = _Dmg - m_tStats.Attack_Def;
				m_tStats.m_iCur_HP -= DMG;
				CEffect* ppObj = CAFactory<CMonsterDMG>::Create_Effect();
				static_cast<CMonsterDMG*>(ppObj)->Check_Dmg(DMG);
				ppObj->Update_Rect(m_tInfo);
				CEffectMgr::Get_Instance()->Add_Effect(ppObj, EFFECTID::MONSTERDMG);
		}
	}
}

void CBlueWolf::is_Magic_Hit_Check(RECT _Rect, int _Dmg)
{
	RECT rc = {};
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (IntersectRect(&rc, &_Rect, &m_tHitBox))
		{
			
				CSoundMgr::Get_Instance()->PlaySound(L"Hit_BBok.wav", CSoundMgr::GARGOYLE_HIT);
				CEffect* pObj = CAFactory<CHit>::Create_Effect();
				pObj->Update_Rect(m_tInfo);
				pObj->Render_Start();
				CEffectMgr::Get_Instance()->Add_Effect(pObj, EFFECTID::HIT);

				int Dmg = _Dmg - m_tStats.Attack_Def;
				m_tStats.m_iCur_HP -= Dmg;
				CEffect* ppObj = CAFactory<CMagicDMG>::Create_Effect();
				static_cast<CMagicDMG*>(ppObj)->Check_Dmg(Dmg);
				ppObj->Update_Rect(m_tInfo);
				CEffectMgr::Get_Instance()->Add_Effect(ppObj, EFFECTID::MAGICDMG);
		}
	}
}

void CBlueWolf::Update_HitBox()
{
	m_tHitBox.left = (LONG)(m_tRect.left);
	m_tHitBox.top = (LONG)(m_tRect.top);
	m_tHitBox.right = (LONG)(m_tRect.right);
	m_tHitBox.bottom = (LONG)(m_tRect.bottom);
}

void CBlueWolf::Update_Trace_Range()
{
	m_tTrace_Range.left = (LONG)(m_tHitBox.left - 90);
	m_tTrace_Range.top = (LONG)(m_tHitBox.top - 90);
	m_tTrace_Range.right = (LONG)(m_tHitBox.right + 90);
	m_tTrace_Range.bottom = (LONG)(m_tHitBox.bottom + 90);
}

void CBlueWolf::Frame_Check()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CBlueWolf::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 5;
			m_tFrame.iState = IDLE;
			m_tFrame.dwDelay = 350;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CBlueWolf::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 5;
			m_tFrame.iState = WALK;
			m_tFrame.dwDelay = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CBlueWolf::ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 7;
			m_tFrame.iState = ATTACK;
			m_tFrame.dwDelay = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CBlueWolf::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iState = DEAD;
			m_tFrame.dwDelay = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBlueWolf::Frame_Update()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;

			m_bHit = false;
			m_bIdle = true;
			if (m_tDelay + 2000 < GetTickCount())
			{
				m_tDelay = GetTickCount();
				m_bAtk = true;
			}
		}
	}
}

void CBlueWolf::Check_Collision()
{
	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
		if (iter->Get_DrawID() == 1)
			iter->bound_Collision_Rect(this);
}

void CBlueWolf::Move_Random()
{
	if (m_tMoveTime + 3000 < GetTickCount())
	{
		m_iRandomTile = (rand() % (CTileMgr::Get_Instance()->Get_Tile().size()));

		m_eCurState = WALK;
		m_bIdle = false;
		m_tMoveTime = GetTickCount();
	}
	auto iter = CTileMgr::Get_Instance()->Get_Tile_N(m_iRandomTile);

	float ffX = iter->Get_Info().fX;
	float ffY = iter->Get_Info().fY;


	float fX = ffX - m_tInfo.fX;
	float fY = ffY - m_tInfo.fY;

	float fDia = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDia);

	if (ffY > m_tInfo.fY)
		m_fAngle *= -1;

	if (ffX > m_tInfo.fX)
	{
		if (ffY > m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Right_Down";
		else if (ffY < m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Right_Up";
	}
	if (ffX < m_tInfo.fX)
	{
		if (ffY > m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Left_Down";
		else if (ffY < m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Left_Up";
	}
	if (!m_bHit)
	{
		m_tInfo.fX += (m_fSpeed *cosf(m_fAngle));
		m_tInfo.fY -= (m_fSpeed *sinf(m_fAngle));
	}
}

void CBlueWolf::Check_Target_Range()
{
	RECT rc = {};
	if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER), &m_tTrace_Range))
		m_bTarget_Trace = true;
	else
		m_bTarget_Trace = false;
}

void CBlueWolf::Move_Target()
{
	float ffX = CObjMgr::Get_Instance()->Get_INFO().fX - m_tInfo.fX;
	float ffY = CObjMgr::Get_Instance()->Get_INFO().fY - m_tInfo.fY;

	float fDia = sqrtf(ffX * ffX + ffY * ffY);

	m_fAngle = acosf(ffX / fDia);

	if (CObjMgr::Get_Instance()->Get_INFO().fY > m_tInfo.fY)
		m_fAngle *= -1;

	if (CObjMgr::Get_Instance()->Get_INFO().fX > m_tInfo.fX)
	{
		if (CObjMgr::Get_Instance()->Get_INFO().fY > m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Right_Down";
		else if (CObjMgr::Get_Instance()->Get_INFO().fY < m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Right_Up";
	}
	if (CObjMgr::Get_Instance()->Get_INFO().fX < m_tInfo.fX)
	{
		if (CObjMgr::Get_Instance()->Get_INFO().fY > m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Left_Down";
		else if (CObjMgr::Get_Instance()->Get_INFO().fY < m_tInfo.fY)
			m_pFrameKey = L"BlueWolf_Left_Up";
	}

	m_eCurState = WALK;
	m_tInfo.fX += (m_fSpeed *cosf(m_fAngle));
	m_tInfo.fY -= (m_fSpeed *sinf(m_fAngle));
	RECT rc = {};
	if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER), &m_tHitBox) && m_bAtk)
		Attack_Target(CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER));
}

void CBlueWolf::Attack_Target(RECT _rc)
{
	if (!m_bIdle && !m_bAtk)
		return;

	m_eCurState = ATTACK;

	RECT rc = {};
	rc.left = m_tTrace_Range.left + 100;
	rc.top = m_tTrace_Range.top + 100;
	rc.right = m_tTrace_Range.right + 200;
	rc.bottom = m_tTrace_Range.bottom + 200;
	if (_rc.right > m_tHitBox.right)
	{
		if (_rc.top < m_tHitBox.top)
			m_pFrameKey = L"BlueWolf_Right_Up";
		else if (_rc.bottom > m_tHitBox.bottom)
			m_pFrameKey = L"BlueWolf_Right_Down";
	}
	if (_rc.right < m_tHitBox.right)
	{
		if (_rc.top < m_tHitBox.top)
			m_pFrameKey = L"BlueWolf_Left_Up";
		else if (_rc.bottom > m_tHitBox.bottom)
			m_pFrameKey = L"BlueWolf_Left_Down";
	}
	m_bAtk = false;
	m_bIdle = false;
	for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER))
		static_cast<CPlayer*>(iter)->is_Hit_Check(rc, m_tStats.Attack_Dmg);
}

void CBlueWolf::Set_Bar()
{
	float fHP = ((float)m_tStats.m_iMax_HP / 104.f);
	static_cast<CMonsterLifeBar*>(m_pLifeBar)->Set_Bar((float)m_tStats.m_iCur_HP / fHP);
}
