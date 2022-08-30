#pragma once
#ifndef __BUTTON_H__

#define __BUTTON_H__



class CBALButton
{
public:
	CBALButton();
	~CBALButton();

public:
	void Set_Pos(float _x, float _y);
	void Update_Rect();
public:
	void Initialize();
	int Update();
	void Late_Update();
	void Render(HDC _DC);

private:
	RECT m_tRect;
	INFO m_tInfo;
	const	TCHAR*	m_pFrameKey;
	int m_ibar;
};



#endif // !__BUTTON_H__
