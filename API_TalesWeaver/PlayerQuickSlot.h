#pragma once
#ifndef __QUICKSLOT_H__
#define __QUICKSLOT_H__

#include "UserInterface.h"
class CPlayerQuickSlot :	public CUserInterface
{
public:
	CPlayerQuickSlot();
	virtual ~CPlayerQuickSlot();

	// CUserInterface을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;


};


#endif // !__QUICKSLOT_H__
