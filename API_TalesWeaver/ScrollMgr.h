#pragma once
#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	void Set_ScrollX(float _x) { m_fScrollX += _x; }
	void Set_ScrollY(float _y) { m_fScrollY += _y; }

public:
	float Get_ScrollX() const { return m_fScrollX; }
	float Get_ScrollY() const { return m_fScrollY; }

public:
	void Scroll_Lock(int _Max_X_Size , int _Max_Y_Size);

public:
	static CScrollMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
private:
	static CScrollMgr*	m_pInstance;

	float		m_fScrollX;
	float		m_fScrollY;
};



#endif // !__SCROLLMGR_H__
