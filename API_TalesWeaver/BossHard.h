#pragma once
#ifndef __BOSSROOM_HARD_H__
#define __BOSSROOM_HARD_H__

#include "Scene.h"
class CBossHard :	public CScene
{
public:
	CBossHard();
	virtual ~CBossHard();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__BOSSROOM_HARD_H__
