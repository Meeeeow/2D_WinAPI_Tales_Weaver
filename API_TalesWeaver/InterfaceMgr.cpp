#include "stdafx.h"
#include "InterfaceMgr.h"
#include "UserInterface.h"
#include "PlayerState.h"
#include "PlayerQuickSlot.h"
#include "PlayerIdentity.h"

CInterfaceMgr* CInterfaceMgr::m_pInstance = nullptr;
CInterfaceMgr::CInterfaceMgr()
{
}


CInterfaceMgr::~CInterfaceMgr()
{
	Release();
}

void CInterfaceMgr::Update(INTERFACEID::ID _eID)
{
	for (auto iter : m_lUI[_eID])
		iter->Update();
}

void CInterfaceMgr::Release()
{
	for (int i = 0; i < INTERFACEID::END; ++i)
	{
		if (m_lUI[i].empty())
			continue;
		for_each(m_lUI[i].begin(), m_lUI[i].end(), Safe_Delete<CUserInterface*>);
		m_lUI[i].clear();
	}
}

void CInterfaceMgr::Render(HDC _DC, INTERFACEID::ID _eID)
{
	for (auto iter : m_lUI[_eID])
		iter->Render(_DC);
}

void CInterfaceMgr::Set_State_Bar(float _hp, float _mp, float _sp, float _xp)
{
	for (auto iter : m_lUI[INTERFACEID::STATE])
		static_cast<CPlayerState*>(iter)->Set_Bar(_hp, _mp, _sp,_xp);
}

void CInterfaceMgr::Set_State_Num(int _hp, int _maxhp, int _mp, int _maxmp, int _sp, int _maxsp, float _xp, float _maxxp)
{
	for (auto iter : m_lUI[INTERFACEID::STATE])
		static_cast<CPlayerState*>(iter)->Set_State_Num(_hp, _maxhp,_mp,_maxmp, _sp,_maxsp, _xp,_maxxp);
}

void CInterfaceMgr::Set_RW(int _a)
{
	for (auto iter : m_lUI[INTERFACEID::STATE])
		static_cast<CPlayerState*>(iter)->Set_Run(_a);
}

void CInterfaceMgr::Set_IdenAll(int _level, int _chp, int _mhp, int _cmp, int _mmp, int _csp, int _msp, float _cxp, float _mxp, int _dmg, int _def)
{
	for (auto iter : m_lUI[INTERFACEID::IDENTITIY])
		static_cast<CPlayerIdentity*>(iter)->Get_Iden(_level, _chp, _mhp, _cmp, _mmp, _csp, _msp, _cxp, _mxp, _dmg, _def);
}

void CInterfaceMgr::Set_P(INTERFACEID::ID _eID)
{
	for (auto iter : m_lUI[_eID])
		iter->Rending();
}
