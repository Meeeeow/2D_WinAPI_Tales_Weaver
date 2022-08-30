#pragma once
#ifndef __MOUSEMGR_H__
#define __MOUSEMGR_H__
class CMouse;
class CMouseMgr
{
private:
	CMouseMgr();
	~CMouseMgr();
public:
	static CMouseMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CMouseMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();
public:
	void Change_ID(int _iDrawID);
private:
	static CMouseMgr*	m_pInstance;
	CMouse*				m_pMouse;
};


#endif // !__MOUSEMGR_H__
