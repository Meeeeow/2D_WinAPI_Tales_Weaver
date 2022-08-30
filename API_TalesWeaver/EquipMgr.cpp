#include "stdafx.h"
#include "EquipMgr.h"
#include "BmpMgr.h"

CEquipMgr* CEquipMgr::m_pInstance = nullptr;
CEquipMgr::CEquipMgr()
{
}


CEquipMgr::~CEquipMgr()
{
}

void CEquipMgr::Add_EQUIP(EQUIPID::ID _eID, ITEMINFO _Item)
{
	if(m_vEquipment[_eID].empty())
		m_vEquipment[_eID].emplace_back(_Item);

}

void CEquipMgr::Change_EQUIP(EQUIPID::ID _eID, ITEMINFO _Item)
{
	if (!m_vEquipment[_eID].empty())
	{
		m_vEquipment[_eID].pop_back();
		m_vEquipment[_eID].emplace_back(_Item);
	}
}

void CEquipMgr::Render(HDC _DC, RECT _rc)
{
	for (int i = 0; i < EQUIPID::END; ++i)
	{
		for (auto iter : m_vEquipment[i])
		{
			HDC hITEMDC = CBmpMgr::Get_Instance()->Find_Bmp(iter.pName);
			GdiTransparentBlt(_DC
				, _rc.left + 5, _rc.top + 28 + (i * 31)
				, 20, 20
				, hITEMDC
				, 0, 0
				, 20, 20
				, RGB(255, 255, 255));
			TCHAR szName[32] = L"";
			swprintf_s(szName, L"%s", iter.pInvenName);
			TextOut(_DC, _rc.left + 50, _rc.top + (28 + i * 30), szName, lstrlen(szName));
		}
	}
}

int CEquipMgr::Get_Dmg()
{
	int Dmg = 0;
	for (int i = 0; i < EQUIPID::END; ++i)
	{
		for (auto iter : m_vEquipment[i])
			Dmg += iter.iDmg;
	}
	return Dmg;
}

int CEquipMgr::Get_Def()
{
	int Def = 0;
	for (int i = 0; i < EQUIPID::END; ++i)
	{
		for (auto iter : m_vEquipment[i])
			Def += iter.iDef;
	}
	return Def;
}

int CEquipMgr::Get_Hp()
{
	int Hp = 0;
	for (int i = 0; i < EQUIPID::END; ++i)
	{
		for (auto iter : m_vEquipment[i])
			Hp += iter.iHP;
	}
	return Hp;
}

int CEquipMgr::Get_Mp()
{
	int Mp = 0;
	for (int i = 0; i < EQUIPID::END; ++i)
	{
		for (auto iter : m_vEquipment[i])
			Mp += iter.iMP;
	}
	return Mp;
}

int CEquipMgr::Get_Sp()
{
	int Sp = 0;
	for (int i = 0; i < EQUIPID::END; ++i)
	{
		for (auto iter : m_vEquipment[i])
			Sp += iter.iSP;
	}
	return Sp;
}
