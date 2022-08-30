#include "stdafx.h"
#include "Potion.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "InventoryMgr.h"
#include "DropItemMgr.h"


CPotion::CPotion()
{
}


CPotion::~CPotion()
{
}

void CPotion::Initialize(INFO _XY)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/_RedHub.bmp", L"_RedHub");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/_BlueHub.bmp", L"_BlueHub");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/QuickSlot/_GreenHub.bmp", L"_GreenHub");
	m_tRect.left = _XY.fX - 42;
	m_tRect.top = _XY.fY - 42;
	m_tRect.bottom = _XY.fY - 22;
	m_tRect.right = _XY.fX - 22;

}

void CPotion::Update()
{
	RECT rc = {};
	for (auto iter : CObjMgr::Get_Instance()->Get_Player())
	{
		if (IntersectRect(&rc, &iter->Get_Hit_Box(), &m_tRect))
		{
			CInventoryMgr::Get_Instance()->Add_Item(m_tItem);
			m_bRender = false;
		}
	}
}

void CPotion::Render(HDC _DC)
{
	if (m_bRender)
	{
		Update();

		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		HDC hDropDC = CBmpMgr::Get_Instance()->Find_Bmp(m_tItem.pName);

		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, 20, 20
			, hDropDC
			, 0, 0
			, 20, 20
			, RGB(255, 255, 255));
	}
}

void CPotion::Release()
{
}

void CPotion::Get_Name(TCHAR * _pName, TCHAR * _pInvenName)
{
	m_tItem.pName = _pName;
	m_tItem.pInvenName = _pInvenName;
	m_tItem.iCount = 1;
	m_bRender = true;
}
