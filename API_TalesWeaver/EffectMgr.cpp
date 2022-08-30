#include "stdafx.h"
#include "EffectMgr.h"
#include "Effect.h"
#include "Hit.h"
#include "Tile.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;
CEffectMgr::CEffectMgr()
{
}


CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Start_Render(EFFECTID::ID _num)
{
	for (auto iter : m_lEffect[_num])
		iter->Render_Start();
}

void CEffectMgr::Stop_Render(EFFECTID::ID _num)
{
	for (auto iter : m_lEffect[_num])
		iter->Render_Stop();
}

void CEffectMgr::Update_Rect(EFFECTID::ID _num, INFO _rc)
{
	for (auto iter : m_lEffect[_num])
		iter->Update_Rect(_rc);
}

void CEffectMgr::Check_Vector(EFFECTID::ID _num, CTile * _Tile, float _x, float _y)
{
	for (auto iter : m_lEffect[_num])
		iter->Check_Vector(_Tile, _x, _y);
}

void CEffectMgr::Delete_Font(EFFECTID::ID _num)
{
	for_each(m_lEffect[_num].begin(), m_lEffect[_num].end(), Safe_Delete<CEffect*>);
	m_lEffect[_num].clear();
}

void CEffectMgr::Render(HDC _DC, EFFECTID::ID _num, const TCHAR* _pFrameKey)
{
	
	for (auto iter : m_lEffect[_num])
		if(!m_lEffect[_num].empty())
			iter->Render(_DC, _pFrameKey);
}


void CEffectMgr::Release()
{
	for (int i = 0; i < EFFECTID::END; ++i)
	{
		if (m_lEffect[i].empty())
			continue;
		for_each(m_lEffect[i].begin(), m_lEffect[i].end(), Safe_Delete<CEffect*>);
		m_lEffect[i].clear();
	}
}
