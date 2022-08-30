#pragma once
#ifndef __LEVELUP_H__
#define __LEVELUP_H__

#include "Effect.h"
class CPlayerLevelUp :	public CEffect
{
public:
	CPlayerLevelUp();
	virtual ~CPlayerLevelUp();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC, const TCHAR * _pFrameKey) override;
	virtual void Release() override;
	virtual void Update_Rect(INFO _rc) override;
	virtual void Check_Vector(CTile * _Tile, float _x, float _y) override;
};


#endif // !__LEVELUP_H__
