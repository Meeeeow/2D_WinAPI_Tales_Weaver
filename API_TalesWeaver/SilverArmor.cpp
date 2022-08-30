#include "stdafx.h"
#include "SilverArmor.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "InventoryMgr.h"
#include "DropItemMgr.h"
#include "EquipMgr.h"

CSilverArmor::CSilverArmor()
{
}


CSilverArmor::~CSilverArmor()
{
}

void CSilverArmor::Initialize(INFO _XY)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/Silver_Armor.bmp", L"Silver_Armor");
	m_tItem.iCount = 1;
	m_tItem.iDef = 10;
	m_tItem.iDmg = 5;
	m_tItem.iHP = 50;
	m_tItem.iMP = 50;
	m_tItem.iSP = 50;
	m_tItem.iValue = 0;
	m_tItem.pInvenName = L"¹ÝÂ¦¹ÝÂ¦ Àº °©¿Ê";
	m_tItem.pName = L"Silver_Armor";
}

void CSilverArmor::Update()
{
}

void CSilverArmor::Render(HDC _DC)
{
}

void CSilverArmor::Release()
{
}
