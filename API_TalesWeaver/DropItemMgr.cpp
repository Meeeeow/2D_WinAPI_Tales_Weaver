#include "stdafx.h"
#include "DropItemMgr.h"
#include "DropItem.h"

CDropItemMgr* CDropItemMgr::m_pInstance = nullptr;

CDropItemMgr::CDropItemMgr()
{
}


CDropItemMgr::~CDropItemMgr()
{
	Release();
}

void CDropItemMgr::Render(HDC _DC, DROPID::ID _eID)
{
	for (auto iter : m_lItem[_eID])
		iter->Render(_DC);
}

void CDropItemMgr::Release()
{
	
	for (int i = 0; i < DROPID::END; ++i)
	{
		for_each(m_lItem[i].begin(), m_lItem[i].end(), Safe_Delete<CDropItem*>);
		m_lItem[i].clear();
	}
}

