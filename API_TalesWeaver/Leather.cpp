#include "stdafx.h"
#include "Leather.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "InventoryMgr.h"
#include "DropItemMgr.h"


CLeather::CLeather()
{
}


CLeather::~CLeather()
{
}

void CLeather::Initialize(INFO _XY)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Drop_Item/Gargoyle_Leather.bmp", L"Gargoyle_Leather");
	m_tRect.left = _XY.fX - 10;
	m_tRect.top = _XY.fY - 10;
	m_tRect.bottom = _XY.fY;
	m_tRect.right = _XY.fX;
	m_tItem.pInvenName = L"°¡°íÀÏ °¡Á×";
	m_tItem.pName = L"Gargoyle_Leather";
	m_tItem.iCount = 1;
	m_bRender = true;

}

void CLeather::Update()
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

void CLeather::Render(HDC _DC)
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

void CLeather::Release()
{
}
