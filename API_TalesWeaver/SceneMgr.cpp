#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "MainMenu.h"
#include "Stage.h"
#include "Mouse.h"
#include "TileEdit.h"
#include "StageShop.h"
#include "Field.h"
#include "Field2.h"
#include "BossRoom.h"
#include "YouDied.h"
#include "BossHard.h"
CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	:m_pScene(nullptr), m_eCurScene(SCENEID::END), m_ePreScene(SCENEID::END)
{

}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID::ID _eID)
{
	m_eCurScene = _eID;
	
	if (m_ePreScene != m_eCurScene)
	{
		Release();

		switch(m_eCurScene)
		{
		case SCENEID::LOGO:
			m_pScene = new CLogo;
			break;
		case SCENEID::MENU:
			m_pScene = new CMainMenu;
			break;
		case SCENEID::STAGE:
			m_pScene = new CStage;
			break;
		case SCENEID::SHOP:
			m_pScene = new CStageShop;
			break;
		case SCENEID::EDIT:
			m_pScene = new CTileEdit;
			break;
		case SCENEID::FIELD:
			m_pScene = new CField;
			break;
		case SCENEID::FIELD2:
			m_pScene = new CField2;
			break;
		case SCENEID::BOSS:
			m_pScene = new CBossRoom;
			break;
		case SCENEID::BOSS_HARD:
			m_pScene = new CBossHard;
			break;
		case SCENEID::YOUDIED:
			m_pScene = new CYouDied;
			break;
		}
		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	m_pScene->Render(_DC);
}

void CSceneMgr::Release()
{
	SAFE_DELETE(m_pScene);
}

