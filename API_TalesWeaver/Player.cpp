#include "stdafx.h"

#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"
#include "JellyBee.h"

#include "KeyMgr.h"

#include "BmpMgr.h"

#include "ScrollMgr.h"
#include "Scene.h"
#include "SceneMgr.h"

#include "Mouse.h"
#include "MouseMgr.h"

#include "TileMgr.h"
#include "Tile.h"

#include "WarpGateMgr.h"

#include "SoundMgr.h"

#include "DropItem.h"
#include "Potion.h"
#include "DropItemMgr.h"
#include "DefaultArmor.h"

#include "UserInterface.h"
#include "PlayerState.h"
#include "PlayerQuickSlot.h"
#include "PlayerIdentity.h"
#include "PlayerInventory.h"
#include "InterfaceMgr.h"
#include "InventoryMgr.h"
#include "PlayerEquip.h"
#include "EquipMgr.h"

#include "EffectMgr.h"
#include "Hit.h"
#include "PlayerDMG.h"
#include "MagicDMG.h"
#include "PlayerLevelUp.h"


#include "Spin.h"
#include "Fireball.h"
#include "Explosion.h"

bool CPlayer::m_bFirstInit = false;
CPlayer::CPlayer()
	:m_bIdle(true), m_bRest(false), m_eCurState(END), m_ePreState(END), m_bArmed(false), m_bSuperArmor(false)
	,m_bExplosionCast(false)
{
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Up.bmp", L"Player_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Down.bmp", L"Player_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Left.bmp", L"Player_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Right.bmp", L"Player_Right");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Left_Down.bmp", L"Player_Left_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Right_Down.bmp", L"Player_Right_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Left_Up.bmp", L"Player_Left_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Right_Up.bmp", L"Player_Right_Up");

	if (!m_bFirstInit)
	{
		CInterfaceMgr::Get_Instance()->Add_Object(CAFactory<CPlayerState>::Create_Interface(), INTERFACEID::STATE);
		CInterfaceMgr::Get_Instance()->Add_Object(CAFactory<CPlayerQuickSlot>::Create_Interface(), INTERFACEID::QUICKSLOT);
		CInterfaceMgr::Get_Instance()->Add_Object(CAFactory<CPlayerIdentity>::Create_Interface(), INTERFACEID::IDENTITIY);
		CInterfaceMgr::Get_Instance()->Add_Object(CAFactory<CPlayerInventory>::Create_Interface(), INTERFACEID::INVENTORY);
		CInterfaceMgr::Get_Instance()->Add_Object(CAFactory<CPlayerEquip>::Create_Interface(), INTERFACEID::EQUIPMENT);
		CDropItem* pObj = new CDefaultArmor;
		pObj->Initialize(m_tInfo);
		CDropItemMgr::Get_Instance()->Add_Object(pObj, DROPID::FIELD);
		m_bFirstInit = true;
	}

	m_tRegenDelay = 5000;
	m_tInfo.fX = 700;
	m_tInfo.fY = 500;
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_fSpeed = 1.5f;
	m_eCurState = IDLE;
	m_pFrameKey = L"Player_Down";
	m_bSilverSword = false;
	m_bSilverArmor = false;
	m_tStats.m_iDefault_HP = 250;
	m_tStats.m_iDefault_MP = 250;
	m_tStats.m_iDefault_SP = 1000;
	m_tStats.m_iDefault_Def = 10;
	m_tStats.m_iDefault_Dmg = 100;
	m_tStats.m_iLevel = 1;
	m_tStats.m_fCur_Exp = 0.f;
	m_tStats.m_fMax_Exp = 50.f;

	Player_Stats_Check();

	m_tStats.m_iCur_HP = m_tStats.m_iMax_HP;
	m_tStats.m_iCur_MP = m_tStats.m_iMax_MP;
	m_tStats.m_iCur_SP = m_tStats.m_iMax_SP;

	m_bFirstStage = true;
	m_bSecondStage = true;
	m_bThirdStage = true;
	m_bShopStage = true;
	m_bBossNormalStage = true;
	m_bBossClear = false;
	m_bBossHardStage = true;
}

int CPlayer::Update()
{
	if (m_bDead)
	{


		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::YOUDIED);
		return OBJ_DEAD;
	}
	Update_Rect();
	Update_HitBox();
	Update_Tile_Rect();

	CInterfaceMgr::Get_Instance()->Update(INTERFACEID::IDENTITIY);
	CInterfaceMgr::Get_Instance()->Update(INTERFACEID::INVENTORY);
	CInterfaceMgr::Get_Instance()->Update(INTERFACEID::EQUIPMENT);

	Key_Check();
	OffSet();
	Player_Regen();
	Player_Stats_Check();
	Set_State();
	
	Check_Level_Up();

	Armed_Check();
	Frame_Check();
	Frame_Update();
	Set_Dead();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tFrame.iStartX * 150, m_tFrame.iState * 150
		, 150, 150
		, RGB(255, 255, 255));
	if (m_bHit)
		CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::HIT, L"Player_Hit");
	if (m_bSpin)
		CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::SPIN, L"Player_Spin_Effect");
	if (m_bExplosionCast)
		CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::EXPLOSION, L"NONE");
	CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::FIREBALL, L"NONE");
	CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::PLAYERDMG, L"NONE");
	if (m_bExplosionCast)
	{
		SetBkMode(_DC, OPAQUE);
		SetBkColor(_DC, RGB(0, 0, 0));

		TCHAR szBuff[64] = L"";
		if (m_bCasting1)
		{
			swprintf_s(szBuff, L"내 이름은 메구밍!");
			TextOut(_DC, m_tHitBox.left + iScrollX , m_tHitBox.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
		if (m_bCasting2 &&m_bCastingSpell + 3000 < GetTickCount())
		{
			m_bCasting1 = false;
			//홍마족 제일의 마법사이자 폭렬 마법을 다루는 자
			swprintf_s(szBuff, L"홍마족 제일의 마법사이자 폭렬 마법을 다루는 자! 내 힘을 똑똑히 봐둬라!");
			TextOut(_DC, m_tHitBox.left + iScrollX - 200, m_tHitBox.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
		if (!m_bCasting1 && m_bCasting3 && m_bCastingSpell + 13000 < GetTickCount())
		{
			m_bCasting2 = false;
			swprintf_s(szBuff, L"익스플로전!");
			TextOut(_DC, m_tHitBox.left + iScrollX , m_tHitBox.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
	CEffectMgr::Get_Instance()->Render(_DC, EFFECTID::LEVELUP,L"NONE");

	// 인터페이스 렌더
	CInterfaceMgr::Get_Instance()->Render(_DC, INTERFACEID::QUICKSLOT);
	CInterfaceMgr::Get_Instance()->Render(_DC, INTERFACEID::STATE);
	CInterfaceMgr::Get_Instance()->Render(_DC, INTERFACEID::IDENTITIY);
	CInterfaceMgr::Get_Instance()->Render(_DC, INTERFACEID::INVENTORY);
	CInterfaceMgr::Get_Instance()->Render(_DC, INTERFACEID::EQUIPMENT);

}

void CPlayer::Release()
{
}
void CPlayer::Armed_Check()
{
	if (!m_bArmed)
		m_fSpeed = 1.5f;
	else
		m_fSpeed = 2.5f;
}
void CPlayer::Key_Check()
{
	RECT rc = {};
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
#ifdef _DEBUG

	if (CKeyMgr::Get_Instacne()->Key_Down(VK_F1))
		m_tStats.m_iCur_HP -= 300;
	if (CKeyMgr::Get_Instacne()->Key_Down(VK_F2))
	{
		m_tStats.m_iDefault_Def += 100;
		m_tStats.m_iDefault_Dmg += 500;
		m_tStats.m_iDefault_HP += 1500;
		m_tStats.m_iDefault_MP += 1500;
		m_tStats.m_iDefault_SP += 1500;
	}
	if (CKeyMgr::Get_Instacne()->Key_Down(VK_F3))
		m_tStats.m_fCur_Exp += 500.f;
	if (CKeyMgr::Get_Instacne()->Key_Down(VK_F4))
		CSceneMgr::Get_Instance()->Scene_Change(SCENEID::BOSS_HARD);
#endif // _DEBUG

	//타일
	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
	{

		if (PtInRect(&iter->Get_Rect(), pt))
		{
			if (iter->Get_DrawID() == 0)
			{
				// 이동
				if ((CKeyMgr::Get_Instacne()->Key_Down(VK_RBUTTON) || CKeyMgr::Get_Instacne()->Key_Pressing(VK_RBUTTON)) && m_bIdle && !m_bRest)
				{
					CMouseMgr::Get_Instance()->Change_ID(0);
					// 무빙 타일 복수 존재 방지
					for (auto iter2 : CTileMgr::Get_Instance()->Get_Tile())
					{
						if (iter2->Get_DrawID() == 2)
							iter2->Setting_DrawID(0);
						if (iter2->Get_DrawID() != 2)
							iter->Setting_DrawID(2);
					}
				}
			}
			// 이동 불가 타일 확인
			else if (iter->Get_DrawID() == 1)
			{
				CMouseMgr::Get_Instance()->Change_ID(2);
			}
			else if (iter->Get_DrawID() == 2)
			{

			}
		}
	}

	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
	{
		if (PtInRect(&iter->Get_Rect(), pt) )
		{
			//공격
			if (CKeyMgr::Get_Instacne()->Key_Down(VK_LBUTTON) && !m_bExplosionTarget && !m_bRest)
			{
				if (m_bArmed && !m_bRest)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYERRUN);
					Player_Attack_Position(iter);
					// 목표 타일 제거
					for (auto iter2 : CTileMgr::Get_Instance()->Get_Tile())
						if (iter2->Get_DrawID() == 2)
							iter2->Setting_DrawID(0);
				}
			}
			// 스킬 S 파이어 볼
			else if (CKeyMgr::Get_Instacne()->Key_Down('S') && m_bIdle && m_tStats.m_iCur_MP >= 50 &&!m_bRest)
			{
				m_bIdle = false;
				m_tStats.m_iCur_MP -= 50;
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYERRUN);
				CSoundMgr::Get_Instance()->PlaySound(L"Player_FB_Shoot.wav", CSoundMgr::PLAYERFB);
				CEffect* pObj = CAFactory<CFireball>::Create_Effect();
				pObj->Check_Vector(iter, m_tInfo.fX, m_tInfo.fY);
				ShotFireball(iter);
				CEffectMgr::Get_Instance()->Add_Effect(pObj, EFFECTID::FIREBALL);
			}
			// 스킬 D 익스플로젼 캐스팅
			else if (m_bExplosionTarget)
			{
				m_bIdle = false;
				m_eCurState = EXPLOSION;
				Target_Explosion(iter,pt);
				m_bExplosionTarget = false;

			}
			// 수행 중인 입력이 없거나 추가 입력 없을 시 IDLE
			else if (m_bIdle)
			{
				for (auto iter2 : CTileMgr::Get_Instance()->Get_Tile())
				{
					if (!m_bArmed && m_bIdle && !m_bRest && iter2->Get_DrawID() != 4)
						m_eCurState = IDLE;
					else if (m_bArmed && m_bIdle && !m_bRest && iter2->Get_DrawID() != 4)
						m_eCurState = ARMED_IDLE;
				}
			}
		}
	}
	
	// 타일 렌더
	if (CKeyMgr::Get_Instacne()->Key_Down('T'))
		CScene::See_Tile();
	// 히트 박스 렌더
	if (CKeyMgr::Get_Instacne()->Key_Down('B'))
		CScene::See_Hitbox();
	// 무기 착용 / 비착용
	if (CKeyMgr::Get_Instacne()->Key_Down('R'))
	{
		if (!m_bArmed)
		{
			m_bArmed = !m_bArmed;
			m_eCurState = ARMED_IDLE;
		}
		else
		{
			m_bArmed = !m_bArmed;
			m_eCurState = IDLE;
		}
	}
	if (CKeyMgr::Get_Instacne()->Key_Down('1') && CInventoryMgr::Get_Instance()->Find_Item_Count(L"빨간 허브"))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Potion.wav", CSoundMgr::PLAYERPOTION);
		CInventoryMgr::Get_Instance()->Find_Item_Decrease(L"빨간 허브", 1);
		m_tStats.m_iCur_HP += m_tStats.m_iMax_HP/5;
	}
	if (CKeyMgr::Get_Instacne()->Key_Down('2')&& CInventoryMgr::Get_Instance()->Find_Item_Count(L"파란 허브"))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Potion.wav", CSoundMgr::PLAYERPOTION);
		CInventoryMgr::Get_Instance()->Find_Item_Decrease(L"파란 허브", 1);
		m_tStats.m_iCur_MP += m_tStats.m_iMax_MP /5;
	}
	if (CKeyMgr::Get_Instacne()->Key_Down('3') && CInventoryMgr::Get_Instance()->Find_Item_Count(L"초록 허브"))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Potion.wav", CSoundMgr::PLAYERPOTION);
		CInventoryMgr::Get_Instance()->Find_Item_Decrease(L"초록 허브", 1);
		m_tStats.m_iCur_SP += m_tStats.m_iMax_SP / 5;
	}
	// 쉬기
	if (CKeyMgr::Get_Instacne()->Key_Down('C'))
	{
		if (!m_bRest && !m_bArmed)
		{
			m_bRest = true;
			m_eCurState = REST;
		}
		else if (m_bRest && !m_bArmed)
		{
			m_bRest = false;
			m_eCurState = IDLE;
		}
	}
	// 스킬 A 스핀
	if (CKeyMgr::Get_Instacne()->Key_Down('A') && m_bIdle && m_tStats.m_iCur_SP >= 100)
	{
		for (auto iter2 : CTileMgr::Get_Instance()->Get_Tile())
		{
			if (iter2->Get_DrawID() == 2)
			{
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYERRUN);
				m_tStats.m_iCur_SP -= 100;
				iter2->Setting_DrawID(0);
			}
		}
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Spin.wav", CSoundMgr::PLAYERATK);
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYERRUN);

		CEffectMgr::Get_Instance()->Update_Rect(EFFECTID::SPIN, m_tInfo);
		CEffectMgr::Get_Instance()->Start_Render(EFFECTID::SPIN);
		m_eCurState = SPIN;
		m_bIdle = false;
		m_bSpin = true;
		m_bSuperArmor = true;
	}
	
	// 스킬 D 익스플로젼
	if (CKeyMgr::Get_Instacne()->Key_Down('D') && !m_bRest)
		if (!m_bExplosionTarget)
			m_bExplosionTarget = !m_bExplosionTarget;
	// 익스플로젼 사용시 마우스 변경
	if (m_bExplosionTarget)
		CMouseMgr::Get_Instance()->Change_ID(5);
	if (m_bSpin)
		Player_Skill_Spin();
	
	// 이동 확인
	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
		if (iter->Get_DrawID() == 2)
			Player_Move(iter);

	// 충돌 확인
	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
		if (iter->Get_DrawID() == 1)
			iter->bound_Collision_Rect(this);

	for (auto iter : CTileMgr::Get_Instance()->Get_Tile())
		if (iter->Get_DrawID() == 4)
		{
			if (PtInRect(&iter->Get_Rect(), pt))
			{
				CMouseMgr::Get_Instance()->Change_ID(3);

				if (CKeyMgr::Get_Instacne()->Key_Down(VK_RBUTTON) || CKeyMgr::Get_Instacne()->Key_Pressing(VK_RBUTTON))
				{
	// 무빙 타일 복수 존재 방지
					for (auto iter2 : CTileMgr::Get_Instance()->Get_Tile())
						if (iter2->Get_DrawID() == 2)
							iter2->Setting_DrawID(0);

					Player_Move(iter);
				}
			}
		}
	if (CKeyMgr::Get_Instacne()->Key_Down('P'))
		CInterfaceMgr::Get_Instance()->Set_P(INTERFACEID::IDENTITIY);
	if (CKeyMgr::Get_Instacne()->Key_Down('I'))
		CInterfaceMgr::Get_Instance()->Set_P(INTERFACEID::INVENTORY);
	if (CKeyMgr::Get_Instacne()->Key_Down('E'))
		CInterfaceMgr::Get_Instance()->Set_P(INTERFACEID::EQUIPMENT);
	if (m_bArmed)
		CInterfaceMgr::Get_Instance()->Set_RW(0);
	if(!m_bArmed)
		CInterfaceMgr::Get_Instance()->Set_RW(1);

}
// 오프셋
void CPlayer::OffSet()
{
	int iOffSetX = WINCX / 2;
	int iOffSetY = WINCY / 2;

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetX < (int)m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetX - (m_tInfo.fX + iScrollX));
	if (iOffSetX > (int)m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetX - (m_tInfo.fX + iScrollX));

	if (iOffSetY < (int)m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetY - (m_tInfo.fY + iScrollY));
	if (iOffSetY > (int)m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetY - (m_tInfo.fY + iScrollY));

}
// 플레이어 이동 상세
void CPlayer::Player_Move(CTile* _targetTile)
{
	if (!m_bIdle)
		return;
	if (!m_bArmed)
		m_eCurState = WALK;
	else
		m_eCurState = ARMED_WALK;
	
	if (m_tStats.m_iCur_SP <= 0)
	{
		m_bArmed = false;
		m_eCurState = WALK;
	}
	float fX = _targetTile->Get_Info().fX - m_tInfo.fX;
	float fY = _targetTile->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDia);
	if (_targetTile->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1;
	if (_targetTile->Get_Rect().left > m_tCheckTile.left)
	{
		if(_targetTile->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _targetTile->Get_Rect().bottom)
			m_pFrameKey = L"Player_Right";
		else if (_targetTile->Get_Rect().top > m_tCheckTile.top)
			m_pFrameKey = L"Player_Right_Down";
		else if (_targetTile->Get_Rect().bottom < m_tCheckTile.bottom)
			m_pFrameKey = L"Player_Right_Up";
	}
	if (_targetTile->Get_Rect().left < m_tCheckTile.left)
	{
		if (_targetTile->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _targetTile->Get_Rect().bottom)
			m_pFrameKey = L"Player_Left";
		else if (_targetTile->Get_Rect().top > m_tCheckTile.top)
			m_pFrameKey = L"Player_Left_Down";
		else if (_targetTile->Get_Rect().bottom < m_tCheckTile.bottom)
			m_pFrameKey = L"Player_Left_Up";
	}
	if (_targetTile->Get_Rect().top > m_tCheckTile.top)
	{
		if (_targetTile->Get_Rect().left < m_tCheckTile.left && _targetTile->Get_Rect().right > m_tCheckTile.right)
			m_pFrameKey = L"Player_Down";
	}
	if (_targetTile->Get_Rect().top < m_tCheckTile.top)
	{
		if (_targetTile->Get_Rect().left < m_tCheckTile.left && _targetTile->Get_Rect().right > m_tCheckTile.right)
			m_pFrameKey = L"Player_Up";
	}
	if(m_eCurState == ARMED_WALK)
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Run.wav", CSoundMgr::PLAYERRUN);
	else if(m_eCurState == WALK)
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk.wav", CSoundMgr::PLAYERRUN);


	if (m_eCurState == ARMED_WALK)
		m_tStats.m_iCur_SP -= 1;

	m_tInfo.fX += (m_fSpeed *cosf(m_fAngle));
	m_tInfo.fY -= (m_fSpeed *sinf(m_fAngle));
	if (_targetTile->if_Collision_Rect(m_tCheckTile))
	{
		m_eCurState = IDLE;
		_targetTile->Setting_DrawID(0);
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYERRUN);
	}
}
// 플레이어 공격 위치 상세
void CPlayer::Player_Attack_Position(CTile* _targetTile)
{
	if (!m_bIdle)
		return;

	CMouseMgr::Get_Instance()->Change_ID(4);
	m_bIdle = false;
	m_eCurState = ATTACK;

	RECT rc = {};
	// 플레이어 방향 조절
	if (_targetTile->Get_Rect().left > m_tCheckTile.left)
	{
		rc.left = m_tHitBox.left;
		rc.right = m_tHitBox.right + 60;

		if (_targetTile->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _targetTile->Get_Rect().bottom)
		{
			rc.top = m_tHitBox.top-60;
			rc.bottom = m_tHitBox.bottom+60;
			m_pFrameKey = L"Player_Right";
		}
		else if (_targetTile->Get_Rect().top > m_tCheckTile.top)
		{
			rc.top = m_tHitBox.top +60;
			rc.bottom = m_tHitBox.bottom-90;
			m_pFrameKey = L"Player_Right_Down";
		}
		else if (_targetTile->Get_Rect().bottom < m_tCheckTile.bottom)
		{
			rc.top = m_tHitBox.top-90;
			rc.bottom = m_tHitBox.bottom+60;
			m_pFrameKey = L"Player_Right_Up";
		}
	}
	if (_targetTile->Get_Rect().left < m_tCheckTile.left)
	{
		rc.left = m_tHitBox.left-60;
		rc.right = m_tHitBox.right;

		if (_targetTile->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _targetTile->Get_Rect().bottom)
		{
			rc.top = m_tHitBox.top - 60;
			rc.bottom = m_tHitBox.bottom + 60;
			m_pFrameKey = L"Player_Left";
		}
		else if (_targetTile->Get_Rect().top > m_tCheckTile.top)
		{
			rc.top = m_tHitBox.top + 60;
			rc.bottom = m_tHitBox.bottom - 90;
			m_pFrameKey = L"Player_Left_Down";
		}
		else if (_targetTile->Get_Rect().bottom < m_tCheckTile.bottom)
		{
			rc.top = m_tHitBox.top - 90;
			rc.bottom = m_tHitBox.bottom + 60;
			m_pFrameKey = L"Player_Left_Up";
		}
	}
	if (_targetTile->Get_Rect().top > m_tCheckTile.top)
		if (_targetTile->Get_Rect().left < m_tCheckTile.left && _targetTile->Get_Rect().right > m_tCheckTile.right)
		{
			rc.left = (LONG)(m_tInfo.fX - 30);
			rc.right = (LONG)(m_tInfo.fX + 30);
			rc.top = (LONG)(m_tInfo.fY);
			rc.bottom = (LONG)(m_tInfo.fY + 60);
			m_pFrameKey = L"Player_Down";
		}
	if (_targetTile->Get_Rect().top < m_tCheckTile.top)
		if (_targetTile->Get_Rect().left < m_tCheckTile.left && _targetTile->Get_Rect().right > m_tCheckTile.right)
		{
			rc.left = (LONG)(m_tInfo.fX - 30);
			rc.right = (LONG)(m_tInfo.fX + 30);
			rc.top = (LONG)(m_tInfo.fY-60);
			rc.bottom = (LONG)(m_tInfo.fY);
			m_pFrameKey = L"Player_Up";
		}


	CSoundMgr::Get_Instance()->PlaySound(L"Player_Attack.wav", CSoundMgr::PLAYERATK);
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD)
		for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER))
			iter->is_Hit_Check(rc, m_tStats.Attack_Dmg);
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD2)
		for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER2))
			iter->is_Hit_Check(rc, m_tStats.Attack_Dmg);
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS)
		for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS))
			iter->is_Hit_Check(rc, m_tStats.Attack_Dmg);
	if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS_HARD)
		for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS_HARD))
			iter->is_Hit_Check(rc, m_tStats.Attack_Dmg);
}
// 플레이어 스킬 스핀 상세
void CPlayer::Player_Skill_Spin()
{
	RECT rc = {};
	rc.left = (LONG)(m_tHitBox.left -50);
	rc.top = (LONG)(m_tHitBox.top - 50);
	rc.right = (LONG)(m_tHitBox.right + 50);
	rc.bottom = (LONG)(m_tHitBox.bottom + 50);
	if (m_tSpinDelay + 250 < GetTickCount())
	{
		if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD)
			for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER))
			{
			iter->is_Hit_Check(rc, (m_tStats.Attack_Dmg / 3) + (rand() % 30));
			m_tSpinDelay = GetTickCount();
			}
		else if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::FIELD2)
			for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::MONSTER2))
			{
				iter->is_Hit_Check(rc, (m_tStats.Attack_Dmg / 3) + (rand() % 30));
				m_tSpinDelay = GetTickCount();
			}
		else if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS)
			for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS))
			{
				iter->is_Hit_Check(rc, (m_tStats.Attack_Dmg / 3) + (rand() % 30));
				m_tSpinDelay = GetTickCount();
			}
		else if (CSceneMgr::Get_Instance()->Get_SceneID() == SCENEID::BOSS_HARD)
			for (auto& iter : CObjMgr::Get_Instance()->Get_List(OBJID::BOSS_HARD))
			{
				iter->is_Hit_Check(rc, (m_tStats.Attack_Dmg / 3) + (rand() % 30));
				m_tSpinDelay = GetTickCount();
			}
	}
}
// 플레이어 피격 확인
void CPlayer::is_Hit_Check(RECT _Rect, int _Dmg)
{
	RECT rc = {};

	if (IntersectRect(&rc, &_Rect, &m_tHitBox))
	{
		if (!m_bSuperArmor)
		{
			m_eCurState = HIT;
			m_bIdle = false;

		}
		if (!m_bSilverArmor)
		{
			m_bHit = true;
			int DMG = _Dmg - m_tStats.Attack_Def;
			if (DMG <= 0)
				DMG = 1;



			CEffect* pObj = CAFactory<CHit>::Create_Effect();
			pObj->Update_Rect(m_tInfo);
			CEffectMgr::Get_Instance()->Add_Effect(pObj, EFFECTID::HIT);
			m_tStats.m_iCur_HP -= DMG;
			CEffectMgr::Get_Instance()->Start_Render(EFFECTID::HIT);
			CEffectMgr::Get_Instance()->Update_Rect(EFFECTID::HIT, m_tInfo);
			CEffect* ppObj = CAFactory<CPlayerDMG>::Create_Effect();
			static_cast<CPlayerDMG*>(ppObj)->Check_Dmg(DMG);
			ppObj->Update_Rect(m_tInfo);
			CEffectMgr::Get_Instance()->Add_Effect(ppObj, EFFECTID::PLAYERDMG);
		}
		else if (m_bSilverArmor)
		{
			m_bHit = true;
			int DMG = (_Dmg/3) - m_tStats.Attack_Def;
			if (DMG <= 0)
				DMG = 1;



			CEffect* pObj = CAFactory<CHit>::Create_Effect();
			pObj->Update_Rect(m_tInfo);
			CEffectMgr::Get_Instance()->Add_Effect(pObj, EFFECTID::HIT);
			m_tStats.m_iCur_HP -= DMG;
			CEffectMgr::Get_Instance()->Start_Render(EFFECTID::HIT);
			CEffectMgr::Get_Instance()->Update_Rect(EFFECTID::HIT, m_tInfo);
			CEffect* ppObj = CAFactory<CPlayerDMG>::Create_Effect();
			static_cast<CPlayerDMG*>(ppObj)->Check_Dmg(DMG);
			ppObj->Update_Rect(m_tInfo);
			CEffectMgr::Get_Instance()->Add_Effect(ppObj, EFFECTID::PLAYERDMG);
		}
	}
}
void CPlayer::is_Magic_Hit_Check(RECT _Rect, int _Dmg)
{
	RECT rc = {};
	if (IntersectRect(&rc, &_Rect, &m_tHitBox))
	{
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
// 플레이어 휴식
void CPlayer::Player_Regen()
{
	if (m_tRegenDelay + m_tRegenTime < GetTickCount())
	{
		if (m_bRest)
		{
			m_tStats.m_iCur_HP += 300;
			m_tStats.m_iCur_MP += 300;
			m_tStats.m_iCur_SP += 300;
		}
		else if (!m_bRest)
		{
			m_tStats.m_iCur_HP += 50;
			m_tStats.m_iCur_MP += 50;
			m_tStats.m_iCur_SP += 50;
		}
		m_tRegenTime = GetTickCount();
	}
	if (m_tStats.m_iCur_HP >= m_tStats.m_iMax_HP)
		m_tStats.m_iCur_HP = m_tStats.m_iMax_HP;
	if (m_tStats.m_iCur_MP >= m_tStats.m_iMax_MP)
		m_tStats.m_iCur_MP = m_tStats.m_iMax_MP;
	if (m_tStats.m_iCur_SP >= m_tStats.m_iMax_SP)
		m_tStats.m_iCur_SP = m_tStats.m_iMax_SP;
}
// 레벨 업 체크
void CPlayer::Check_Level_Up()
{
	if (m_tStats.m_fCur_Exp >= m_tStats.m_fMax_Exp)
	{
		m_tStats.m_fCur_Exp -= m_tStats.m_fMax_Exp;
		m_tStats.m_fMax_Exp *= 1.5;

		++m_tStats.m_iLevel;
		CEffectMgr::Get_Instance()->Start_Render(EFFECTID::LEVELUP);
		m_tStats.m_iDefault_HP += 15 + (rand()%10+1)*5;
		m_tStats.m_iDefault_MP += 10 + (rand()%5+1)*5;
		m_tStats.m_iDefault_SP += 50 + (rand()%10+1)*5;
		m_tStats.m_iDefault_Def += 1 + (rand() % 3+1)*2;
		m_tStats.m_iDefault_Dmg += 3 + (rand() % 7+1)*2;

		m_tStats.Attack_Dmg = m_tStats.m_iDefault_Dmg + CEquipMgr::Get_Instance()->Get_Dmg();
		m_tStats.Attack_Def = m_tStats.m_iDefault_Def + CEquipMgr::Get_Instance()->Get_Def();
		m_tStats.m_iMax_HP = m_tStats.m_iDefault_HP + CEquipMgr::Get_Instance()->Get_Hp();
		m_tStats.m_iMax_MP = m_tStats.m_iDefault_MP + CEquipMgr::Get_Instance()->Get_Mp();
		m_tStats.m_iMax_SP = m_tStats.m_iDefault_SP + CEquipMgr::Get_Instance()->Get_Sp();

		m_tStats.m_iCur_HP = m_tStats.m_iMax_HP;
		m_tStats.m_iCur_MP = m_tStats.m_iMax_MP;
		m_tStats.m_iCur_SP = m_tStats.m_iMax_SP;

	}
}
void CPlayer::Player_Stats_Check()
{
	m_tStats.Attack_Dmg = m_tStats.m_iDefault_Dmg + CEquipMgr::Get_Instance()->Get_Dmg();
	m_tStats.Attack_Def = m_tStats.m_iDefault_Def + CEquipMgr::Get_Instance()->Get_Def();
	m_tStats.m_iMax_HP = m_tStats.m_iDefault_HP + CEquipMgr::Get_Instance()->Get_Hp();
	m_tStats.m_iMax_MP = m_tStats.m_iDefault_MP + CEquipMgr::Get_Instance()->Get_Mp();
	m_tStats.m_iMax_SP = m_tStats.m_iDefault_SP + CEquipMgr::Get_Instance()->Get_Sp();
}
// 파이어볼 위치 조정
void CPlayer::ShotFireball(CTile * _Endpos)
{
	float fX = _Endpos->Get_Info().fX - m_tInfo.fX;
	float fY = _Endpos->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	m_fAngle = acosf(fX / fDia);

	m_eCurState = ATTACK;

	if (_Endpos->Get_Info().fY > m_tInfo.fY)
		m_fAngle *= -1;
	if (_Endpos->Get_Rect().left > m_tCheckTile.left)
	{
		if (_Endpos->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _Endpos->Get_Rect().bottom)
			m_pFrameKey = L"Player_Right";
		else if (_Endpos->Get_Rect().top > m_tCheckTile.top)
			m_pFrameKey = L"Player_Right_Down";
		else if (_Endpos->Get_Rect().bottom < m_tCheckTile.bottom)
			m_pFrameKey = L"Player_Right_Up";
	}
	if (_Endpos->Get_Rect().left < m_tCheckTile.left)
	{
		if (_Endpos->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _Endpos->Get_Rect().bottom)
			m_pFrameKey = L"Player_Left";
		else if (_Endpos->Get_Rect().top > m_tCheckTile.top)
			m_pFrameKey = L"Player_Left_Down";
		else if (_Endpos->Get_Rect().bottom < m_tCheckTile.bottom)
			m_pFrameKey = L"Player_Left_Up";
	}
	if (_Endpos->Get_Rect().top > m_tCheckTile.top)
	{
		if (_Endpos->Get_Rect().left < m_tCheckTile.left && _Endpos->Get_Rect().right > m_tCheckTile.right)
			m_pFrameKey = L"Player_Down";
	}
	if (_Endpos->Get_Rect().top < m_tCheckTile.top)
	{
		if (_Endpos->Get_Rect().left < m_tCheckTile.left && _Endpos->Get_Rect().right > m_tCheckTile.right)
			m_pFrameKey = L"Player_Up";
	}
}
void CPlayer::Target_Explosion(CTile * _TargetPos, POINT _pt)
{
	if (!m_bExplosionCast)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Player_Explosion_Cast.wav", CSoundMgr::PLAYERFB);
		CEffect* m_Temp = CAFactory<CExplosion>::Create_Effect();
		static_cast<CExplosion*>(m_Temp)->Check_Vector(_TargetPos,(float) _pt.x,(float) _pt.y,m_tStats.m_iCur_MP);
		m_Temp->Render_Start();
		m_tStats.m_iCur_MP = 0;
		CEffectMgr::Get_Instance()->Add_Effect(m_Temp, EFFECTID::EXPLOSION);
		m_bCasting1 = true;
		m_bCasting2 = true;
		m_bCasting3 = true;
		m_bCastingSpell = GetTickCount();
	}
	m_bExplosionCast = true;
	m_bSuperArmor = true;
	if (_TargetPos->Get_Rect().left > m_tCheckTile.left)
	{
		if (_TargetPos->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _TargetPos->Get_Rect().bottom)
			m_pFrameKey = L"Player_Right";
		else if (_TargetPos->Get_Rect().top > m_tCheckTile.top)
			m_pFrameKey = L"Player_Right_Down";
		else if (_TargetPos->Get_Rect().bottom < m_tCheckTile.bottom)
			m_pFrameKey = L"Player_Right_Up";
	}
	if (_TargetPos->Get_Rect().left < m_tCheckTile.left)
	{
		if (_TargetPos->Get_Rect().top < m_tCheckTile.top && m_tCheckTile.bottom < _TargetPos->Get_Rect().bottom)
			m_pFrameKey = L"Player_Left";
		else if (_TargetPos->Get_Rect().top > m_tCheckTile.top)
			m_pFrameKey = L"Player_Left_Down";
		else if (_TargetPos->Get_Rect().bottom < m_tCheckTile.bottom)
			m_pFrameKey = L"Player_Left_Up";
	}
	if (_TargetPos->Get_Rect().top > m_tCheckTile.top)
	{
		if (_TargetPos->Get_Rect().left < m_tCheckTile.left && _TargetPos->Get_Rect().right > m_tCheckTile.right)
			m_pFrameKey = L"Player_Down";
	}
	if (_TargetPos->Get_Rect().top < m_tCheckTile.top)
	{
		if (_TargetPos->Get_Rect().left < m_tCheckTile.left && _TargetPos->Get_Rect().right > m_tCheckTile.right)
			m_pFrameKey = L"Player_Up";
	}
}
void CPlayer::Cast_Explosion_Off()
{
	m_bExplosionCast = false;
}
void CPlayer::Add_Exp(float _Exp)
{
	m_tStats.m_fCur_Exp += _Exp;

}
// 라이프바 조절
void CPlayer::Set_State()
{
	float iHP = (m_tStats.m_iMax_HP / 84.f);
	float iMP = (m_tStats.m_iMax_MP / 84.f);
	float iSP = (m_tStats.m_iMax_SP / 84.f);
	float iXP = (m_tStats.m_fMax_Exp / 107.f);

	CInterfaceMgr::Get_Instance()->Set_State_Bar(((float)m_tStats.m_iCur_HP / iHP), ((float)m_tStats.m_iCur_MP / iMP), ((float)m_tStats.m_iCur_SP / iSP),((float)m_tStats.m_fCur_Exp / iXP));
	CInterfaceMgr::Get_Instance()->Set_State_Num(
		m_tStats.m_iCur_HP, m_tStats.m_iMax_HP
		, m_tStats.m_iCur_MP, m_tStats.m_iMax_MP
		, m_tStats.m_iCur_SP, m_tStats.m_iMax_SP
		, m_tStats.m_fCur_Exp, m_tStats.m_fMax_Exp);

	CInterfaceMgr::Get_Instance()->Set_IdenAll(m_tStats.m_iLevel, m_tStats.m_iCur_HP, m_tStats.m_iMax_HP, m_tStats.m_iCur_MP, m_tStats.m_iMax_MP
		, m_tStats.m_iCur_SP, m_tStats.m_iMax_SP, m_tStats.m_fCur_Exp, m_tStats.m_fMax_Exp, m_tStats.Attack_Dmg, m_tStats.Attack_Def);
}
// 플레이어 히트 박스 업데이트
void CPlayer::Update_HitBox()
{
	m_tHitBox.left = (LONG)(m_tRect.left);
	m_tHitBox.top = (LONG)(m_tRect.top-15);
	m_tHitBox.right = (LONG)(m_tRect.right -30);
	m_tHitBox.bottom = (LONG)(m_tRect.bottom -30);
}
// 플레이어 프레임 체크
void CPlayer::Frame_Check()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CPlayer::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 10;
			m_tFrame.iState = IDLE;
			m_tFrame.dwDelay = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 10;
			m_tFrame.iState = WALK;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::REST:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 0;
			m_tFrame.iState = REST;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::ARMED_IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iState = ARMED_IDLE;
			m_tFrame.dwDelay = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::ARMED_WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 20;
			m_tFrame.iState = ARMED_WALK;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iState = ATTACK;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::SPIN:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 14;
			m_tFrame.iState = SPIN;
			m_tFrame.dwDelay = 80;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::HIT:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 0;
			m_tFrame.iState = HIT;
			m_tFrame.dwDelay = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CPlayer::EXPLOSION:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 9;
			m_tFrame.iState = EXPLOSION;
			m_tFrame.dwDelay = 1700;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}
// 플레이어 프레임 업데이트
void CPlayer::Frame_Update()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;

			// 특정 행동들 초기화
			if(!m_bIdle)
				m_bIdle = !m_bIdle;
			if (m_bHit)
				m_bHit = !m_bHit;
			if (m_bSpin)
				m_bSpin = !m_bSpin;
			if (m_bSuperArmor)
				m_bSuperArmor = !m_bSuperArmor;
		}
	}
}



