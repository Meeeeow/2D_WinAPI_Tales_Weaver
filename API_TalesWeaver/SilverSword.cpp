#include "stdafx.h"
#include "SilverSword.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "InventoryMgr.h"
#include "DropItemMgr.h"

CSilverSword::CSilverSword()
{
	ZeroMemory(&m_tItem, sizeof(m_tItem));
}


CSilverSword::~CSilverSword()
{
}

void CSilverSword::Initialize(INFO _XY)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/SilverSword.bmp", L"SilverSword");
	m_tRect.left = _XY.fX - 10;
	m_tRect.top = _XY.fY - 10;
	m_tRect.right = _XY.fX + 10;
	m_tRect.bottom = _XY.fY + 10;
	m_bRender = true;
	m_tItem.pInvenName = L"휘황찬란 은검";
	m_tItem.pName = L"SilverSword";
	m_tItem.iHP = 50;
	m_tItem.iDmg = 50;
	m_tItem.iCount = 1;
}

void CSilverSword::Update()
{
}

void CSilverSword::Render(HDC _DC)
{
}

void CSilverSword::Release()
{
}
