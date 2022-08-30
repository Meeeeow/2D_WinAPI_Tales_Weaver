#include "stdafx.h"
#include "WarpGateMgr.h"
#include "WarpGate.h"

CWarpGateMgr* CWarpGateMgr::m_pInstance = nullptr;
CWarpGateMgr::CWarpGateMgr()
{
}


CWarpGateMgr::~CWarpGateMgr()
{
	Release();
}

void CWarpGateMgr::Release()
{
	for (int i = 0; i < STAGEID::END; ++i)
	{
		for_each(m_pWarpGate[i].begin(), m_pWarpGate[i].end(), Safe_Delete<CWarpGate*>);
		m_pWarpGate[i].clear();
	}
}

void CWarpGateMgr::Render(HDC _DC, STAGEID::ID _iD)
{
		
	for (auto iter : m_pWarpGate[_iD])
	{
		iter->Render(_DC);
	}
}

void CWarpGateMgr::Add_Gate(CWarpGate * _pGate, STAGEID::ID _ID)
{
	m_pWarpGate[_ID].emplace_back(_pGate);

}
