#pragma once
#ifndef __BOSSROOM_H__
#define __BOSSROOM_H__

#include "Scene.h"
class CBossRoom :	public CScene
{
public:
	CBossRoom();
	virtual ~CBossRoom();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
};


#endif // !__BOSSROOM_H__
