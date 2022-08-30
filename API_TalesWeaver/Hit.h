#pragma once
#ifndef __HIT_H__
#define __HIT_H__

#include "Effect.h"
class CHit :	public CEffect
{
public:
	CHit();
	virtual ~CHit();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC,const TCHAR* _pFrameKey) override;
	virtual void Release() override;
	virtual void Update_Rect(INFO _rc) override;
	virtual void Check_Vector(CTile* _Tile, float _x, float _y) override;

};


#endif // !__HIT_H__
