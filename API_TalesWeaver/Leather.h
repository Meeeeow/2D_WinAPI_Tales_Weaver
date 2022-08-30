#pragma once
#ifndef __LEATHER_H__
#define __LEATHER_H__


#include "DropItem.h"
class CLeather :	public CDropItem
{
public:
	CLeather();
	virtual ~CLeather();

	// CDropItem을(를) 통해 상속됨
	virtual void Initialize(INFO _XY) override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};


#endif // !__LEATHER_H__
