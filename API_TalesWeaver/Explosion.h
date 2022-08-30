#pragma once
#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "Effect.h"
class CExplosion :	public CEffect
{
public:
	CExplosion();
	virtual ~CExplosion();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC, const TCHAR * _pFrameKey) override;
	virtual void Release() override;
	virtual void Update_Rect(INFO _rc) override;
	virtual void Check_Vector(CTile * _Tile, float _x, float _y) override;
	void Check_Vector(CTile * _Tile, float _x, float _y, int _mana);

	int iDmg;
};


#endif // !__EXPLOSION_H__
