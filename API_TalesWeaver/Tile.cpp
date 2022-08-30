#include "stdafx.h"
#include "Tile.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "Obj.h"

CTile::CTile()
	:m_iDrawID(0)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));

}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile_Sprite.bmp", L"Tile_Sprite");
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;
}

void CTile::Set_Pos(int _x, int _y)
{
	m_tInfo.fX = (float)_x;
	m_tInfo.fY = (float)_y;
}

void CTile::Set_DrawID(int _DrawID)
{
	m_iDrawID += _DrawID;
	if (m_iDrawID >= 5)
		m_iDrawID = 0;
	if (m_iDrawID <= -1)
		m_iDrawID = 5;
}

int CTile::Update()
{
	Update_Rect();
	return 0;
}

void CTile::Late_Update()
{

}

void CTile::Render(HDC _DC)
{
	Update_Rect();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hTileDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Tile_Sprite");

	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hTileDC
		, m_iDrawID * TILECX, 0
		, 30, 30
		, RGB(255, 255, 255));

	/*BitBlt(_DC
	, m_tRect.left + iScrollX, m_tRect.top + iScrollY
	, m_tInfo.iCX, m_tInfo.iCY
	, hTileDC
	, m_iDrawID * TILECX, 0
	, SRCCOPY);
	*/
}

void CTile::Release()
{
}

bool CTile::if_Collision_Rect(RECT _coll)
{
	RECT rc= {};
	if (IntersectRect(&rc, &m_tRect, &_coll))
		return true;
	return false;
}

void CTile::bound_Collision_Rect(CObj* _player)
{
	float Move_X = 0.f, Move_Y = 0.f;
	RECT rc = {};
	if (m_iDrawID == 1 &&IntersectRect(&rc, &_player->Get_Check_Rect(), &m_tRect))
	{
		float fX = abs(m_tInfo.fX - _player->Get_Info().fX);
		float fY = abs(m_tInfo.fY - _player->Get_Info().fY);
		float fSumX = (float)((5 + m_tInfo.iCX) >> 1);
		float fSumY = (float)((5 + m_tInfo.iCY) >> 1);

		if (fSumX > fX && fSumY > fY)
		{
			Move_X = fSumX - fX;
			Move_Y = fSumY - fY;
			if (Move_X < Move_Y)
			{
				if (_player->Get_Info().fX > m_tInfo.fX)
					_player->Set_PosX((int)fX/2);
				else
					_player->Set_PosX((int)-fX/2);
			}
			else
			{
				if (_player->Get_Info().fY > m_tInfo.fY)
					_player->Set_PosY((int)fY/2);
				else
					_player->Set_PosY((int)-fY/2);
			}
		}
	}
}


void CTile::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}
