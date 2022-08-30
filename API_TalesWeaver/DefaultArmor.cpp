#include "stdafx.h"
#include "DefaultArmor.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "InventoryMgr.h"
#include "DropItemMgr.h"
#include "EquipMgr.h"

CDefaultArmor::CDefaultArmor()
{
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}


CDefaultArmor::~CDefaultArmor()
{
}

void CDefaultArmor::Initialize(INFO _XY)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/Normal_Armor.bmp", L"Default_Armor");
	m_tArmor.iCount = 1;
	m_tArmor.iDef = 10;
	m_tArmor.iDmg = 2;
	m_tArmor.iHP = 20;
	m_tArmor.iMP = 0;
	m_tArmor.iSP = -10;
	m_tArmor.iValue = 0;
	m_tArmor.pInvenName = L"기본 갑옷";
	m_tArmor.pName = L"Default_Armor";

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/Normal_Head.bmp", L"Default_Head");
	m_tHead.iCount = 1;
	m_tHead.iDef = 3;
	m_tHead.iDmg = 0;
	m_tHead.iHP = 5;
	m_tHead.iMP = 0;
	m_tHead.iSP = 5;
	m_tHead.iValue = 0;
	m_tHead.pInvenName = L"기본 투구";
	m_tHead.pName = L"Default_Head";
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/Red_Ring.bmp", L"Default_Ring");
	m_tRedRing.iCount = 1;
	m_tRedRing.iDef = 0;
	m_tRedRing.iDmg = 3;
	m_tRedRing.iHP = 5;
	m_tRedRing.iMP = 10;
	m_tRedRing.iSP = 10;
	m_tRedRing.iValue = 0;
	m_tRedRing.pInvenName = L"레드 링";
	m_tRedRing.pName = L"Default_Ring";
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/Normal_Shoes.bmp", L"Default_Shoes");
	m_tShoes.iCount = 1;
	m_tShoes.iDef = 0;
	m_tShoes.iDmg = 0;
	m_tShoes.iHP = 0;
	m_tShoes.iMP = 0;
	m_tShoes.iSP = 10;
	m_tShoes.iValue = 0;
	m_tShoes.pInvenName = L"기본 신발";
	m_tShoes.pName = L"Default_Shoes";
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/Normal_Sword.bmp", L"Default_Sword");
	m_tSword.iCount = 1;
	m_tSword.iDef = 0;
	m_tSword.iDmg = 10;
	m_tSword.iHP = 0;
	m_tSword.iMP = 0;
	m_tSword.iSP = 0;
	m_tSword.iValue = 0;
	m_tSword.pInvenName = L"기본 검";
	m_tSword.pName = L"Default_Sword";
	//	enum ID{HEAD,ARMOR,SWORD,HAND,SHOES,END};

	CEquipMgr::Get_Instance()->Add_EQUIP(EQUIPID::ARMOR, m_tArmor);
	CEquipMgr::Get_Instance()->Add_EQUIP(EQUIPID::HEAD, m_tHead);
	CEquipMgr::Get_Instance()->Add_EQUIP(EQUIPID::SWORD, m_tSword);
	CEquipMgr::Get_Instance()->Add_EQUIP(EQUIPID::SHOES, m_tShoes);
	CEquipMgr::Get_Instance()->Add_EQUIP(EQUIPID::HAND, m_tRedRing);


}

void CDefaultArmor::Update()
{
}

void CDefaultArmor::Render(HDC _DC)
{
}

void CDefaultArmor::Release()
{
}
