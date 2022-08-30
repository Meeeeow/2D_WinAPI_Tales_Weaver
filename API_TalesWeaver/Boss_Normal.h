#pragma once
#ifndef __BOSS_NORMAL_H__
#define __BOSS_NORMAL_H__

#include "Obj.h"
class CBoss_Normal :	public CObj
{
public:
	enum STATE { IDLE, WALK, ATTACK, DEAD, END };
public:
	CBoss_Normal();
	virtual ~CBoss_Normal();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void is_Hit_Check(RECT _Rect, int _Dmg) override;
	virtual void is_Magic_Hit_Check(RECT _Rect, int _Dmg) override;
	virtual void Update_HitBox() override;

public:
	void Update_Trace_Range();

public:
	void Frame_Check();
	void Frame_Update();

public:
	void Check_Collision();
	void Move_Random();
	void Check_Target_Range();
	void Move_Target();
	void Attack_Target(RECT _rc);
	void Set_Bar();

private:
	STATE	m_eCurState;
	STATE	m_ePreState;
	RECT	m_tTrace_Range;
	bool	m_bTarget_Trace;
	bool	m_bIdle;
	bool	m_bAtk;
	size_t	m_iRandomTile;
	DWORD	m_tMoveTime;
	DWORD	m_tDelay;
	CUserInterface* m_pLifeBar;
};


#endif // !__BOSS_NORMAL_H__
