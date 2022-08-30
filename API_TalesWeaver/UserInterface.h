#pragma once
#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

class CUserInterface
{
public:
	CUserInterface();
	~CUserInterface();

public:
	virtual void Initialize() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Release() = 0;

	void Rending() { m_bRender = !m_bRender; }
	
protected:
	RECT m_tRect;
	INFO m_tInfo;
	bool m_bRender;

};


#endif // !__USERINTERFACE_H__
