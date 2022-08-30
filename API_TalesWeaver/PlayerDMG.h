#pragma once
#ifndef __PLAYERDMG_H__
#define __PLAYERDMG_H__

#include "Effect.h"
class CPlayerDMG :	public CEffect
{
public:
	CPlayerDMG();
	virtual ~CPlayerDMG();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC, const TCHAR * _pFrameKey) override;
	virtual void Release() override;
	virtual void Update_Rect(INFO _rc) override;
	virtual void Check_Vector(CTile * _Tile, float _x, float _y) override;

	void Check_Dmg(int _Dmg);
private:
	int MaxDmg;
	DMGRENDER*	m_pDmgRender[3];
	DWORD m_tDeleteTime;
};


#endif // !__PLAYERDMG_H__
