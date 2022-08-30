#pragma once
#ifndef __BOSSFIRE_H__
#define __BOSSFIRE_H__

#include "Effect.h"
class CBossFire :	public CEffect
{
public:
	CBossFire();
	virtual ~CBossFire();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC, const TCHAR * _pFrameKey) override;
	virtual void Release() override;
	virtual void Update_Rect(INFO _rc) override;
	virtual void Check_Vector(CTile * _Tile, float _x, float _y) override;


};


#endif // !__BOSSFIRE_H__
