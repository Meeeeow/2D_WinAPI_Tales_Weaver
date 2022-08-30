#include "stdafx.h"
#include "MouseMgr.h"
#include "Mouse.h"
#include "ScrollMgr.h"
CMouseMgr* CMouseMgr::m_pInstance = nullptr;

CMouseMgr::CMouseMgr()
	: m_pMouse(nullptr)
{
}


CMouseMgr::~CMouseMgr()
{
	Release();
}

void CMouseMgr::Initialize()
{
	m_pMouse = new CMouse;
}

void CMouseMgr::Update()
{
	m_pMouse->Update();
}

void CMouseMgr::Late_Update()
{
	m_pMouse->Late_Update();
}

void CMouseMgr::Render(HDC _DC)
{
	m_pMouse->Render(_DC);
}

void CMouseMgr::Release()
{
	SAFE_DELETE(m_pMouse);
}
void CMouseMgr::Change_ID(int _iDrawID)
{
	m_pMouse->Change_ID(_iDrawID);
}
