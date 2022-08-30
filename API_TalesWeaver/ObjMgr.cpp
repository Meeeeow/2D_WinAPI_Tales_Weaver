#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"
#include "Player.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end(); )
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{

	for (int i = 0; i < OBJID::END; ++i)
		for (auto& pObj : m_listObj[i])
			pObj->Late_Update();
}

void CObjMgr::Render(HDC _DC)
{
	for (auto& pObj : m_listObj[OBJID::PLAYER])
		pObj->Render(_DC);
}

void CObjMgr::Monster_Render(HDC _DC,OBJID::ID _eID)
{
	if (!m_listObj[_eID].empty())
		for (auto& pObj : m_listObj[_eID])
			pObj->Render(_DC);
}

void CObjMgr::Hitbox_Render(HDC _DC, OBJID::ID _eID)
{
	if (m_listObj[_eID].empty())
		return;
	for (auto iter : m_listObj[_eID])
			iter->Render_Hitbox(_DC);
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

void CObjMgr::Release_ID(OBJID::ID _eid)
{
	for_each(m_listObj[_eid].begin(), m_listObj[_eid].end(), Safe_Delete<CObj*>);
	m_listObj[_eid].clear();
}

list<CObj*> CObjMgr::Get_List(OBJID::ID _id)
{
	for (int i = _id; i < OBJID::END; i++)
		return m_listObj[i];
}

list<CObj*> CObjMgr::Get_ListMon()
{
	return list<CObj*>();
}

void CObjMgr::Set_Pos(int _x, int _y)
{
	for (auto iter : m_listObj[OBJID::PLAYER])
		static_cast<CPlayer*>(iter)->Set_Pos(_x, _y);
}

INFO CObjMgr::Get_INFO()
{
	for (auto& pPlayer : m_listObj[OBJID::PLAYER])
	{
		return pPlayer->Get_Info();
	}
}

RECT CObjMgr::Get_Hit_Box(OBJID::ID _iD)
{
	for (auto iter : m_listObj[_iD])
		return iter->Get_Hit_Box();
}
