#pragma once
#ifndef __PLAYER_INVENTORY_H__
#define __PLAYER_INVENTORY_H__

#include "UserInterface.h"
class CPlayerInventory :	public CUserInterface
{
public:
	CPlayerInventory();
	virtual ~CPlayerInventory();

	// CUserInterface을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;

private:
	RECT rc;
	RECT Inven;
	int m_iBar;
	POINT m_tStartPos;
};


#endif // !__PLAYER_INVENTORY_H__
