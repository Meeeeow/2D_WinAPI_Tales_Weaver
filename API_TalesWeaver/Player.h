#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Obj.h"
class CTile;
class CMouse;
class CPlayer :	public CObj
{
public:
	enum STATE {IDLE, WALK, REST, ARMED_IDLE , ARMED_WALK, ATTACK, SPIN ,HIT,EXPLOSION,END };
public:
	CPlayer();
	virtual ~CPlayer();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
public:
	void Armed_Check();
	void Key_Check();
	void OffSet();

public:
	void Set_State();
public:
	virtual void Update_HitBox();
public:
	void Frame_Check();
	void Frame_Update();
public:
	void Player_Move(CTile* _targetTile);
	void Player_Attack_Position(CTile* _targetTile);
	void Player_Skill_Spin();
	virtual void is_Hit_Check(RECT _Rect, int _Dmg) override;
	virtual void is_Magic_Hit_Check(RECT _Rect, int _Dmg) override;
	void Player_Regen();
	void Check_Level_Up();
	void Player_Stats_Check();
public:
	void ShotFireball(CTile* _Endpos);
	void Target_Explosion(CTile* _TargetPos,POINT _pt);
	void Cast_Explosion_Off();
	void Add_Exp(float _Exp);
	bool if_Player_SilverSword() { if (m_bSilverSword) { return true; } return false; }
	bool if_Player_SilverArmor() { return m_bSilverArmor; }
	void Get_Player_SilverSword() { m_bSilverSword = true; }
	void Get_Player_SilverArmor() { m_bSilverArmor = true; }

	bool First_Stage() { return m_bFirstStage; }
	void Clear_First_Stage() { m_bFirstStage = false; }
	bool Second_Stage() { return m_bSecondStage; }
	void Clear_Second_Stage() { m_bSecondStage = false; }
	bool Third_Stage() { return m_bThirdStage; }
	void Clear_Third_Stage() { m_bThirdStage = false; }
	bool Shop_Stage() { return m_bShopStage; }
	void Clear_Shop_Stage() { m_bShopStage = false; }
	bool Boss_Normal_Stage() { return m_bBossNormalStage; }
	void Clear_Boss_Normal_Stage() { m_bBossNormalStage = false; }
	bool Boss_Check() { return m_bBossClear; }
	void Clear_Boss() { m_bBossClear = true; }
	bool Boss_Hard_Stage() { return m_bBossHardStage; }
	void Clear_Boss_Hard_Stage() { m_bBossHardStage = false; }

private:
	bool	m_bIdle;
	bool	m_bRest;
	bool	m_bArmed;
	STATE	m_ePreState;
	STATE	m_eCurState;
	bool	m_bSuperArmor;
	bool	m_bSilverSword;
	bool	m_bSilverArmor;
	DWORD	m_tRegenTime;
	DWORD	m_tRegenDelay;
	DWORD	m_tSpinDelay;
	bool	m_bBossClear;
private: //스킬
	bool	m_bExplosionTarget;
	bool	m_bExplosionCast;
	bool	m_bSpin;
	
private: // 대화
	bool	m_bFirstStage;
	bool	m_bSecondStage;
	bool	m_bThirdStage;
	bool	m_bShopStage;
	bool	m_bBossNormalStage;
	bool	m_bBossHardStage;
	DWORD	m_bCastingSpell;
	bool	m_bCasting1;
	bool	m_bCasting2;
	bool	m_bCasting3;
	static bool m_bFirstInit;
};


#endif // !__PLAYER_H__
