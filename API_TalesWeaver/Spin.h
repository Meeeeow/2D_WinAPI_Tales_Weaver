#pragma once
#ifndef __SPIN_H__
#define __SPIN_H__
#include "Effect.h"
class CSpin :	public CEffect
{
public:
	CSpin();
	virtual ~CSpin();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC, const TCHAR * _pFrameKey) override;
	virtual void Release() override;
	virtual void Update_Rect(INFO _rc) override;
	virtual void Check_Vector(CTile* _Tile, float _x, float _y) override;

};


#endif // !__SPIN_H__
