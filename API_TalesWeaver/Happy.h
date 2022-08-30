#pragma once
#ifndef __HAPPY_H__
#define __HAPPY_H__

#include "Obj.h"
class CHappy :	public CObj
{
public:
	enum STATE { IDLE, END};
public:
	CHappy();
	virtual ~CHappy();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void is_Hit_Check(RECT _Rect, int _Dmg) override;
	virtual void is_Magic_Hit_Check(RECT _Rect, int _Dmg) override;
	virtual void Update_HitBox() override;

public:
	void Frame_Check();
	void Frame_Update();

private:
	STATE	m_ePreState;
	STATE	m_eCurState;
	DWORD	m_tTime;
	bool	m_bFirstChat;
	bool	m_bFirstQuest;
	bool	m_bChat;
	bool	m_bSecondChat;
	bool	m_bSecondQuest;
	bool	m_bThirdChat;
	bool	chat1;
	bool	chat2;
	bool	chat3;
};


#endif // !__HAPPY_H__
