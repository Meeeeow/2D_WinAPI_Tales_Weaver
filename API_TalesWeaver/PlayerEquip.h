#pragma once
#ifndef __PLAYEREQUIP_H__
#define __PLAYEREQUIP_H__

#include "UserInterface.h"
class CPlayerEquip :	public CUserInterface
{
public:
	CPlayerEquip();
	virtual ~CPlayerEquip();

	// CUserInterface을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;

private:
	RECT rc;
	RECT Equip;
	int m_iBar;
	POINT m_tStartPos;
	bool m_bHentai;
	DWORD m_tHentai;
};


#endif // !__PLAYEREQUIP_H__