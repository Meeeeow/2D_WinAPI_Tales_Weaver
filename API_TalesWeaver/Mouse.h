#pragma once
#ifndef __MOUSE_H__
#define __MOUSE_H__

class CMouse
{
public:
	enum STATE { IDLE, CLICK, NOMOVE, GATE, ENEMY, MAGIC,END};
public:
	CMouse();
	~CMouse();
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();
public:
	void Update_Rect();
public:
	void Frame_Check();
	void Frame_Update();
public:
	void Change_ID(int _iD);
private:
	RECT	m_tRect;
	INFO	m_tInfo;
	STATE	m_ePreState;
	STATE	m_eCurState;
	FRAME	m_tFrame;
	POINT	pt = {};

};


#endif // !__MOUSE_H__
