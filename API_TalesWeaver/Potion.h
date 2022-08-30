#pragma once
#ifndef __POTION_H__
#define __POTION_H__



#include "DropItem.h"
class CPotion :	public CDropItem
{
public:
	CPotion();
	virtual ~CPotion();

	// CDropItem을(를) 통해 상속됨
	virtual void Initialize(INFO _XY) override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	void Get_Name(TCHAR* _pName, TCHAR* _pInvenName);
};


#endif // !__POTION_H__
