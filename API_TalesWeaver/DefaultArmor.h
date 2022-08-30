#pragma once
#ifndef __DEFAULT_ARMOR_H__
#define __DEFAULT_ARMOR_H__


#include "DropItem.h"
class CDefaultArmor :	public CDropItem
{
public:
	CDefaultArmor();
	virtual ~CDefaultArmor();

	// CDropItem을(를) 통해 상속됨
	virtual void Initialize(INFO _XY) override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	ITEMINFO m_tHead;
	ITEMINFO m_tArmor;
	ITEMINFO m_tShoes;
	ITEMINFO m_tSword;
	ITEMINFO m_tRedRing;
};


#endif // !__DEFAULT_ARMOR_H__
