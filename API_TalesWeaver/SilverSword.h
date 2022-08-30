#pragma once
#ifndef __SILVERSWORD_H__
#define __SILVERSWORD_H__

#include "DropItem.h"
class CSilverSword :	public CDropItem
{
public:
	CSilverSword();
	virtual ~CSilverSword();

	// CDropItem을(를) 통해 상속됨
	virtual void Initialize(INFO _XY) override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__SILVERSWORD_H__
