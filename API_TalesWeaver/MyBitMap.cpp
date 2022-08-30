#include "stdafx.h"
#include "MyBitMap.h"


CMyBitMap::CMyBitMap()
{
}


CMyBitMap::~CMyBitMap()
{
	Release();
}

void CMyBitMap::Release()
{
	SelectObject(m_hMemDC, m_hBitMap_Old);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}

void CMyBitMap::Load_Bmp(const TCHAR * _pFilePath)
{
	HDC hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(NULL, _pFilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (NULL == m_hBitMap)
	{
		MessageBox(g_hWnd, L"이미지 로딩(Load_Bmp) 실패", L"실패", MB_OK);
		return;
	}

	m_hBitMap_Old = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);
	
}
