#pragma once
#ifndef __PLAYERSTATE_H__
#define __PLAYERSTATE_H__


#include "UserInterface.h"
class CPlayerState :	public CUserInterface
{
public:
	CPlayerState();
	virtual ~CPlayerState();


	// CUserInterface을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;

	void Set_Bar(float _hp, float _mp, float _sp, float _xp);
	void Set_State_Num(int _hp, int _maxhp, int _mp, int _maxmp, int _sp, int _maxsp, float _xp, float _maxxp);
	void Set_Run(int _a);
private:
	int iRW;
	float m_iHpCur;
	float m_iMpCur;
	float m_iSpCur;
	float m_iXpCur;

	int m_fiCurrentHp;
	int m_fiMaximumHp;
	int m_fiCurrentMp;
	int m_fiMaximumMp;
	int m_fiCurrentSp;
	int m_fiMaximumSp;
	float m_fiCurrentXp;
	float m_fiMaximumXp;
	const TCHAR* m_pFrameKey;
};


#endif // !__PLAYERSTATE_H__
