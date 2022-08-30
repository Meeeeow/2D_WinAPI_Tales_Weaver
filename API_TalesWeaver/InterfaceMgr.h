#pragma once
#ifndef __INTERFACEMGR_H__
#define __INTERFACEMGR_H__
class CUserInterface;
class CInterfaceMgr
{
private:
	CInterfaceMgr();
	~CInterfaceMgr();
public:
	void Add_Object(CUserInterface* _pObj, INTERFACEID::ID _eID) { m_lUI[_eID].emplace_back(_pObj); }
	void Update(INTERFACEID::ID _eID);
	void Release();
	void Render(HDC _DC,INTERFACEID::ID _eID);

public:
	void Set_State_Bar(float _hp, float _mp, float _sp, float _xp);
	void Set_State_Num(int _hp, int _maxhp, int _mp, int _maxmp, int _sp, int _maxsp, float _xp, float _maxxp);
	void Set_RW(int _a);
	void Set_IdenAll(int _level, int _chp, int _mhp, int _cmp, int _mmp,
		int _csp, int _msp, float _cxp, float _mxp, int _dmg, int _def);
	void Set_P(INTERFACEID::ID _eID);
public:
	static CInterfaceMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CInterfaceMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
private:
	static CInterfaceMgr* m_pInstance;
	list<CUserInterface*> m_lUI[INTERFACEID::END];
};


#endif // !__INTERFACEMGR_H__
