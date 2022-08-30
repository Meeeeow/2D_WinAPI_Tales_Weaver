#pragma once
#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "Effect.h"
class CFireball :	public CEffect
{
public:
	CFireball();
	virtual ~CFireball();

	// CEffect을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC, const TCHAR * _pFrameKey) override;
	virtual void Release() override;
	virtual void Update_Rect(INFO _rc) override;
	virtual void Check_Vector(CTile * _Tile, float _x, float _y) override;

	void FireBall_Update();
private:
	const TCHAR* m_pFrameKey;
	float m_fAngle;
};


#endif // !__FIREBALL_H__
