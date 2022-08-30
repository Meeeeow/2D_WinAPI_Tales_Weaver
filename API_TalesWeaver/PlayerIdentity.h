#pragma once
#ifndef __IDENTITY_H__
#define __IDENTITY_HH

#include "UserInterface.h"
class CPlayerIdentity :	public CUserInterface
{
public:
	CPlayerIdentity();
	virtual ~CPlayerIdentity();

	// CUserInterface을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;
public:
	void Get_Iden(int _level, int _chp, int _mhp, int _cmp, int _mmp,
		int _csp, int _msp, float _cxp, float _mxp, int _dmg, int _def);
private:
	RECT rc;
	RECT Iden;
	float m_iXpCur;

	int m_iLevel;
	int m_iCurrentHp;
	int m_iMaximumHp;
	int m_iCurrentMp;
	int m_iMaximumMp;
	int m_iCurrentSp;
	int m_iMaximumSp;
	float m_fCurrentXp;
	float m_fMaximumXp;
	int m_iDmg;
	int m_iDef;
	const TCHAR* m_pFrameKey;
	int m_iBar;
	int m_iXpBar;
};


#endif // !__IDENTITY_H__
