#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
}

void CTileMgr::Update()
{
	for (auto iter : m_PreTile)
		iter->Update();
}

void CTileMgr::Set_Tile(int x, int y)
{
	m_PreTile.reserve(x*y);
	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			float fX = (float)(TILECX >> 1) + (j * TILECX);
			float fY = (float)(TILECY >> 1) + (i * TILECY);
			CTile* pTile = CAFactory<CTile>::Create((int)fX,(int)fY);
			m_PreTile.emplace_back(pTile);
		}
	}
}

void CTileMgr::Render(HDC _DC,int tileX)
{
	int		iScrollX = abs((int)CScrollMgr::Get_Instance()->Get_ScrollX());
	int		iScrollY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY());

	int iCullX = iScrollX / TILECX;
	int iCullY = iScrollY / TILECY;

	int iCullEndX = iCullX + (WINCX / TILECX)+2;
	int iCullEndY = iCullY + (WINCY / TILECY)+2;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int iIdx = i * tileX + j;

			if (0 > iIdx || m_PreTile.size() <= (size_t)iIdx)
				continue;

			m_PreTile[iIdx]->Render(_DC);
		}
	}

}

void CTileMgr::Release()
{
	for_each(m_PreTile.begin(), m_PreTile.end(), Safe_Delete<CTile*>);
	m_PreTile.clear();
}
void CTileMgr::is_Picking_Tile(int _X)
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	
	int x = pt.x / TILECX;
	int y = pt.y / TILECY;

	int iIdx = y * _X + x;

	if (0 > iIdx || m_PreTile.size() <= (size_t)iIdx)
		return;

	m_PreTile[iIdx]->Set_DrawID(1);
}
void CTileMgr::is_Picking_Tile_Down(int _X)
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	int x = pt.x / TILECX;
	int y = pt.y / TILECY;

	int iIdx = y * _X + x;

	if (0 > iIdx || m_PreTile.size() <= (size_t)iIdx)
		return;

	m_PreTile[iIdx]->Set_DrawID(-1);
}

void CTileMgr::Load_Tile(const TCHAR* _pPath)
{
	HANDLE hFile = CreateFile(_pPath, GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();

	DWORD	dwByte = 0;
	INFO	tTemp = {};
	int		iDrawID = 0;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CTile* pTile = CAFactory<CTile>::Create(tTemp.fX, tTemp.fY, iDrawID);
		m_PreTile.emplace_back(pTile);

	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"불러오기 성공!", L"성공", MB_OK);
}

void CTileMgr::Save_Tile(const TCHAR* _pPath)
{
	HANDLE hFile = CreateFile(_pPath, GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패!", L"실패", MB_OK);
		return;
	}

	DWORD	dwByte = 0;

	for (auto& pTile : m_PreTile)
	{
			WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
			WriteFile(hFile, &pTile->Get_DrawID(), sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공!", L"성공", MB_OK);
}

void CTileMgr::Find_Tile(int _id)
{
	for (auto iter : m_PreTile)
	{
		if (iter->Get_DrawID() == 4)
			is_Tile_Reset(iter);
	}
	
}

void CTileMgr::is_Tile_Reset(CTile * _pTile)
{
	_pTile->Setting_DrawID(0);
}

