#include "stdafx.h"
#include "BmpMgr.h"
#include "MyBitMap.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;
CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Release()
{
	for (auto& Pair : m_mapBit)
		SAFE_DELETE(Pair.second);
	m_mapBit.clear();
}

void CBmpMgr::Insert_Bmp(const TCHAR * _pFilePath, const TCHAR * _pImageKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStrCmp(_pImageKey));

	if (m_mapBit.end() == iter)
	{
		CMyBitMap* pBmp = new CMyBitMap;
		pBmp->Load_Bmp(_pFilePath);

		m_mapBit.emplace(_pImageKey, pBmp);
	}
}

HDC CBmpMgr::Find_Bmp(const TCHAR * _pImageKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStrCmp(_pImageKey));

	if (m_mapBit.end() == iter)
	{
		const TCHAR* pP = _pImageKey;
		MessageBox(g_hWnd, pP, L"Find_Bmp", MB_OK);
		return nullptr;
	}

	return iter->second->Get_DC();
}
// 문자열 결합하여 어떤 이미지를 못찾았는지 
// swprintf_s