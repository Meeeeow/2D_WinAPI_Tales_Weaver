#pragma once
#ifndef __SILVERBAR_H__
#define __SILVERBAR_H__

#include "DropItem.h"
class CSilverBar :	public CDropItem
{
public:
	CSilverBar();
	virtual ~CSilverBar();



	// CDropItem을(를) 통해 상속됨
	virtual void Initialize(INFO _XY) override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

};


#endif // !__SILVERBAR_H__
