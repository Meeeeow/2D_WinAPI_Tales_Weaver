#pragma once
#ifndef __SILVERARMOR_H__
#define __SILVERARMOR_H__

#include "DropItem.h"
class CSilverArmor :	public CDropItem
{
public:
	CSilverArmor();
	virtual ~CSilverArmor();

	// CDropItem을(를) 통해 상속됨
	virtual void Initialize(INFO _XY) override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__SILVERARMOR_H__
