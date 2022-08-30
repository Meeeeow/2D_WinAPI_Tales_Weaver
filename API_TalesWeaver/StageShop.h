#pragma once
#ifndef __STAGE_SHOP_H__
#define __STAGE_SHOP_H__
#include "Scene.h"


class CStageShop :	public CScene
{
public:
	CStageShop();
	virtual ~CStageShop();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:

};


#endif // !__STAGE_SHOP_H__
