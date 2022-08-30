#include "stdafx.h"
#include "JellyBee.h"
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
#include "DropItem.h"
#include "SilverBar.h"
#include "DropItemMgr.h"
#include "Potion.h"



CJellyBee::CJellyBee()
	: m_bIdle(true), m_eCurState(END), m_ePreState(END)

{
	ZeroMemory(&m_tStats, sizeof(m_tStats));
}


CJellyBee::~CJellyBee()
{
	Release();
}

void CJellyBee::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/JellyBee/JellyBee_Left_Down.bmp", L"JellyBee_Left_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/JellyBee/JellyBee_Right_Down.bmp", L"JellyBee_Right_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/JellyBee/JellyBee_Left_Up.bmp", L"JellyBee_Left_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/JellyBee/JellyBee_Right_Up.bmp", L"JellyBee_Right_Up");



	m_tInfo.iCX = 130;
	m_tInfo.iCY = 130;

	m_fSpeed = 0.5f;
	m_bIdle = true;
	m_bTarget_Trace = false;
	m_eCurState = IDLE;
	m_pFrameKey = L"JellyBee_Right_Down";
	m_iRandomTile = (rand() % (CTileMgr::Get_Instance()->Get_Tile().size()));
	m_tStats.m_iMax_HP = 420 - (rand() % 30);
	
	m_tStats.m_iCur_HP = m_tStats.m_iMax_HP;
	m_tStats.Attack_Dmg = (rand() % 25) + 10;
	m_tStats.Attack_Def = (rand() % 10) + 5;
	m_tStats.m_fMax_Exp = (rand() % 50) + 5;
	m_tStats.m_fCur_Exp = m_tStats.m_fMax_Exp;
	m_pLifeBar = new CMonsterLifeBar;
}

int CJellyBee::Update()
{
	if (m_bDead)
	{
		m_eCurState = DEAD;
		if (m_tFrame.iStartX >= 1)
		{
			int Chance = (rand() % 3);
			CDropItem* pObj = new CSilverBar;
			pObj->Initialize(m_tInfo);
			CDropItemMgr::Get_Instance()->Add_Object(pObj,DROPID::FIELD);
			if (Chance == 0)
			{
				CDropItem* pObj = new CPotion;
				pObj->Initialize(m_tInfo);
				static_cast<CPotion*>(pObj)->Get_Name(L"_RedHub", L"»¡°£ Çãºê");
				CDropItemMgr::Get_Instance()->Add_Object(pObj, DROPID::FIELD);
			}
			else if (Chance == 1)
			{
				CDropItem* pObj = new CPotion;
				pObj->Initialize(m_tInfo);
				static_cast<CPotion*>(pObj)->Get_Name(L"_BlueHub", L"ÆÄ¶õ Çãºê");
				CDropItemMgr::Get_Instance()->Add_Object(pObj, DROPID::FIELD);
			}
			else if (Chance == 2)
			{
				CDropItem* pObj = new CPotion;
				pObj->Initialize(m_tInfo);
				static_cast<CPotion*>(pObj)->Get_Name(L"_GreenHub", L"ÃÊ·Ï Çãºê");
				CDropItemMgr::Get_Instance()->Add_Object(pObj, DROPID::FIELD);
			}
			for (auto iter : CObjMgr::Get_Instance()->Get_Player())
				static_cast<CPlayer*>(iter)->Add_Exp(m_tStats.m_fCur_Exp);
			CSoundMgr::Get_Instance()->PlaySound(L"JellyBee_Dead.wav", CSoundMgr::JELLYBEE_DEAD);
			SAFE_DELETE(m_pLifeBar);
			return OBJ_DEAD;
		}
	}

	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD)
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

void CJellyBee::Late_Update()
{
}

void CJellyBee::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hTileDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(_DC
		, m_tRect.left+iScrollX, m_tRect.top+iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hTileDC
		, m_tFrame.iStartX * 150, m_tFrame.iState * 150
		, 150, 150
		, RGB(255, 255, 255));
	CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::HIT, L"Monster_Hit");
	CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::MONSTERDMG, L"NONE");
	CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::MAGICDMG, L"NONE");
	if (m_bAtk)
	{
		SetBkMode(_DC, OPAQUE);
		SetBkColor(_DC, RGB(0, 0, 0));

		TCHAR szBuff[64] = L"";
		swprintf_s(szBuff, L"»ß»ß!");
		TextOut(_DC, m_tHitBox.left + iScrollX, m_tHitBox.top + iScrollY - 30, szBuff, lstrlen(szBuff));
	}
	if (m_bDead)
	{
		SetBkMode(_DC, OPAQUE);
		SetBkColor(_DC, RGB(0, 0, 0));

		TCHAR szBuff[64] = L"";
		swprintf_s(szBuff, L"»ß.....");
		TextOut(_DC, m_tHitBox.left + iScrollX, m_tHitBox.top + iScrollY - 30, szBuff, lstrlen(szBuff));
	}
	m_pLifeBar->Render(_DC);
}

void CJellyBee::Release()
{
	SAFE_DELETE(m_pLifeBar);
}

void CJellyBee::Update_Trace_Range()
{
	m_tTrace_Range.left = (LONG)(m_tInfo.fX - 150);
	m_tTrace_Range.top = (LONG)(m_tInfo.fY - 150);
	m_tTrace_Range.right = (LONG)(m_tInfo.fX + 150);
	m_tTrace_Range.bottom = (LONG)(m_tInfo.fY + 150);
}

void CJellyBee::Frame_Check()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CJellyBee::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iState = IDLE;
			m_tFrame.dwDelay = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CJellyBee::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 5;
			m_tFrame.iState = WALK;
			m_tFrame.dwDelay = 250;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CJellyBee::ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 16;
			m_tFrame.iState = ATTACK;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CJellyBee::HIT:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iState = HIT;
			m_tFrame.dwDelay = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CJellyBee::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iState = DEAD;
			m_tFrame.dwDelay = 1000;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CJellyBee::Frame_Update()
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
			if (m_tDelay + 5000 < GetTickCount())
			{
				m_tDelay = GetTickCount();
				m_bAtk = true;
			}
		}
	}
}

void CJellyBee::Check_Collision()
{
	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
		if (iter->Get_DrawID() == 1)
			iter->bound_Collision_Rect(this);
}

void CJellyBee::Move_Random()
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
			m_pFrameKey = L"JellyBee_Right_Down";
		else if (ffY < m_tInfo.fY)
			m_pFrameKey = L"JellyBee_Right_Up";
	}
	if (ffX < m_tInfo.fX)
	{
		if (ffY > m_tInfo.fY)
			m_pFrameKey = L"JellyBee_Left_Down";
		else if (ffY < m_tInfo.fY)
			m_pFrameKey = L"JellyBee_Left_Up";
	}
	if (!m_bHit)
	{
		m_tInfo.fX += (m_fSpeed *cosf(m_fAngle));
		m_tInfo.fY -= (m_fSpeed *sinf(m_fAngle));
	}
}

void CJellyBee::Check_Target_Range()
{
	RECT rc = {};
	if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER), &m_tTrace_Range))
		m_bTarget_Trace = true;
	else
		m_bTarget_Trace = false;
}

void CJellyBee::Move_Target()
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
			m_pFrameKey = L"JellyBee_Right_Down";
		else if (CObjMgr::Get_Instance()->Get_INFO().fY < m_tInfo.fY)
			m_pFrameKey = L"JellyBee_Right_Up";
	}
	if (CObjMgr::Get_Instance()->Get_INFO().fX < m_tInfo.fX)
	{
		if (CObjMgr::Get_Instance()->Get_INFO().fY > m_tInfo.fY)
			m_pFrameKey = L"JellyBee_Left_Down";
		else if (CObjMgr::Get_Instance()->Get_INFO().fY < m_tInfo.fY)
			m_pFrameKey = L"JellyBee_Left_Up";
	}
	m_eCurState = WALK;
	m_tInfo.fX += (m_fSpeed *cosf(m_fAngle));
	m_tInfo.fY -= (m_fSpeed *sinf(m_fAngle));
	RECT rc = {};
	if (IntersectRect(&rc, &CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER), &m_tHitBox) && m_bAtk)
		Attack_Target(CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER));
}

void CJellyBee::Attack_Target(RECT _rc)
{
	if (!m_bIdle && !m_bAtk)
		return;

	m_eCurState = ATTACK;

	RECT rc = {};
	if (_rc.right > m_tHitBox.left)
	{
		rc.left = m_tHitBox.left - 60;
		rc.right = m_tHitBox.right+30;
		rc.top = m_tHitBox.top;
		rc.bottom = m_tHitBox.bottom;
		if (_rc.top < m_tHitBox.top)
		{
			rc.top = m_tHitBox.top - 60;
			rc.bottom = m_tHitBox.bottom+30;
			m_pFrameKey = L"JellyBee_Right_Up";
		}
		else if (_rc.bottom > m_tHitBox.bottom)
		{
			rc.top = m_tHitBox.top-30;
			rc.bottom = m_tHitBox.bottom + 60;
			m_pFrameKey = L"JellyBee_Right_Down";
		}
	}
	if (_rc.left < m_tHitBox.right)
	{
		rc.left = m_tHitBox.left-30;
		rc.right = m_tHitBox.right + 60;
		rc.top = m_tHitBox.top;
		rc.bottom = m_tHitBox.bottom;
		if (_rc.top < m_tHitBox.top)
		{
			rc.top = m_tHitBox.top - 60;
			rc.bottom = m_tHitBox.bottom+30;
			m_pFrameKey = L"JellyBee_Left_Up";
		}
		else if (_rc.bottom > m_tHitBox.bottom)
		{
			rc.top = m_tHitBox.top-30;
			rc.bottom = m_tHitBox.bottom + 60;
			m_pFrameKey = L"JellyBee_Left_Down";
		}
	}
	if (m_tFrame.iStartX == 13)
	{
		m_bAtk = false;
		m_bIdle = false;
		CSoundMgr::Get_Instance()->PlaySound(L"JellyBee_Attack.wav", CSoundMgr::JELLYBEE_ATK);
		for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::PLAYER))
			static_cast<CPlayer*>(iter)->is_Hit_Check(rc, m_tStats.Attack_Dmg);
	}
	

}

void CJellyBee::Set_Bar()
{
	float fHP = ((float)m_tStats.m_iMax_HP / 52.f);
	static_cast<CMonsterLifeBar*>(m_pLifeBar)->Set_Bar((float)m_tStats.m_iCur_HP / fHP);
}

void CJellyBee::Update_HitBox()
{
	m_tHitBox.left = (LONG)(m_tRect.left-10);
	m_tHitBox.top = (LONG)(m_tRect.top-10);
	m_tHitBox.right = (LONG)(m_tRect.right-95);
	m_tHitBox.bottom = (LONG)(m_tRect.bottom-85);
}

void CJellyBee::is_Hit_Check(RECT _Rect, int _Dmg)
{
	RECT rc = {};
	if (IntersectRect(&rc, &_Rect, &m_tHitBox))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"JellyBee_Hit.wav", CSoundMgr::JELLYBEE_HIT);

		m_bHit = true;
		m_bIdle = false;
		CEffect* pObj = CAFactory<CHit>::Create_Effect();
		pObj->Update_Rect(m_tInfo);
		pObj->Render_Start();
		CEffectMgr::Get_Instance()->Add_Effect(pObj, EFFECTID::HIT);
		m_eCurState = HIT;
		int DMG = _Dmg - m_tStats.Attack_Def;
		if (DMG <= 0)
			DMG = 1;
		m_tStats.m_iCur_HP -= DMG;
		CEffect* ppObj = CAFactory<CMonsterDMG>::Create_Effect();
		static_cast<CMonsterDMG*>(ppObj)->Check_Dmg(DMG);
		ppObj->Update_Rect(m_tInfo);
		CEffectMgr::Get_Instance()->Add_Effect(ppObj, EFFECTID::MONSTERDMG);
	}
}

void CJellyBee::is_Magic_Hit_Check(RECT _Rect, int _Dmg)
{
	RECT rc = {};
	if (IntersectRect(&rc, &_Rect, &m_tHitBox))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"JellyBee_Hit.wav", CSoundMgr::JELLYBEE_HIT);
		m_bHit = true;
		m_bIdle = false;
		CEffect* pObj = CAFactory<CHit>::Create_Effect();
		pObj->Update_Rect(m_tInfo);
		pObj->Render_Start();
		CEffectMgr::Get_Instance()->Add_Effect(pObj, EFFECTID::HIT);

		m_eCurState = HIT;
		m_tStats.m_iCur_HP -= _Dmg;
		CEffect* ppObj = CAFactory<CMagicDMG>::Create_Effect();
		static_cast<CMagicDMG*>(ppObj)->Check_Dmg(_Dmg);
		ppObj->Update_Rect(m_tInfo);
		CEffectMgr::Get_Instance()->Add_Effect(ppObj, EFFECTID::MAGICDMG);
	}
}
