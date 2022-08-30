#include "stdafx.h"
#include "InventoryMgr.h"
#include "DropItem.h"
#include "BmpMgr.h"

CInventoryMgr* CInventoryMgr::m_pInstance = nullptr;
CInventoryMgr::CInventoryMgr()
{
}


CInventoryMgr::~CInventoryMgr()
{
	//Release();
}
/*
void CInventoryMgr::Add_Item(INVENID::ID _eID,CDropItem* _Item)
{
	if (m_vInventory[_eID].empty())
		m_vInventory[_eID].emplace_back(_Item);
	else
	{
		for (auto iter : m_vInventory[_eID])
			iter->Add_Count();
	}
}*/

void CInventoryMgr::Add_Item(ITEMINFO _ITEM)
{
	auto iter = find_if(m_vInven.begin(), m_vInven.end(), CFindItem(_ITEM.pInvenName));

	if (iter == m_vInven.end())
	{
		m_vInven.emplace_back(_ITEM);
		return;
	}

	iter->iCount++;
}

int CInventoryMgr::Find_Item_Count(TCHAR * _ITEM)
{
	auto iter = find_if(m_vInven.begin(), m_vInven.end(), CFind_Item_Count(_ITEM));

	if (iter == m_vInven.end())
		return 0;

	return iter->iCount;

}

void CInventoryMgr::Find_Item_Decrease(TCHAR * _ITEM, int _Decrase)
{
	auto iter = find_if(m_vInven.begin(), m_vInven.end(), CFind_Item_Count(_ITEM));

	if (iter == m_vInven.end())
		return;

	iter->iCount -= _Decrase;
	Delete_Null_Item(_ITEM);
}

void CInventoryMgr::Delete_Null_Item(TCHAR* _ITEM)
{
	auto iter = find_if(m_vInven.begin(), m_vInven.end(), CFind_Item_Count(_ITEM));

	if (iter == m_vInven.end())
		return;

	if (iter->iCount <= 0)
	{
		m_vInven.erase(iter);

	}
}

void CInventoryMgr::Release()
{
	//for_each(m_vInven.begin(), m_vInven.end(), Safe_Delete<CDropItem*>);
	m_vInven.clear();
}

void CInventoryMgr::Render2(HDC _DC, RECT _rc)
{
	int j = 0;
	for (auto iter = m_vInven.begin(); iter < m_vInven.end(); ++iter)
	{
		HDC hITEMDC = CBmpMgr::Get_Instance()->Find_Bmp(iter->pName);
		GdiTransparentBlt(_DC
			, _rc.left + 15, _rc.top + 48 + (j * 24)
			, 20, 20
			, hITEMDC
			, 0, 0
			, 20, 20
			, RGB(255, 255, 255));
		TCHAR szName[32] = L"";
		TCHAR szCount[32] = L"";
		swprintf_s(szName, L"%s", iter->pInvenName);
		swprintf_s(szCount, L"%i", iter->iCount);
		TextOut(_DC, _rc.left + 50, _rc.top + (48 + j * 24), szName, lstrlen(szName));
		TextOut(_DC, _rc.left + 300, _rc.top + (48 + j * 24), szCount, lstrlen(szCount));
		++j;
	}
}
