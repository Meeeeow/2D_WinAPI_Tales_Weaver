#pragma once
#ifndef __BITMAP_H__
#define __BITMAP_H__


class CMyBitMap
{
public:
	CMyBitMap();
	~CMyBitMap();

public:
	void Release();

public:
	HDC	Get_DC() { return m_hMemDC; }
	void Load_Bmp(const TCHAR* _pFilePath);

private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitMap;
	HBITMAP		m_hBitMap_Old;
};


#endif // !__BITMAP_H__
