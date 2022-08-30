#pragma once
#ifndef __WARPGATEMGR_H__
#define __WARPGATEMGR_H__

class CWarpGate;
class CWarpGateMgr
{
public:
private:
	CWarpGateMgr();
	~CWarpGateMgr();

public:
	void Release();
	list<CWarpGate*> Get_List(STAGEID::ID _iD) { return m_pWarpGate[_iD]; }
public:
	static CWarpGateMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CWarpGateMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
public:
	void Render(HDC _DC,STAGEID::ID _iD);
public:
	void Add_Gate(CWarpGate* _pGate, STAGEID::ID _ID);

private:
	static CWarpGateMgr* m_pInstance;
	list<CWarpGate*>	 m_pWarpGate[STAGEID::ID::END];
};


#endif // !__WARPGATEMGR_H__
