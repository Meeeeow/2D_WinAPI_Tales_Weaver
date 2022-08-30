#pragma once
#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__

class CTile;
class CScene;
class CMouse;
class CSceneMgr
{
public:
private:
	CSceneMgr();
	~CSceneMgr();
public:
	void Scene_Change(SCENEID::ID _eID);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();
	CScene*	Get_Scene() { return m_pScene; }
	SCENEID::ID Get_SceneID() { return m_ePreScene; }
public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void Destory_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CSceneMgr*	m_pInstance;

	CScene*				m_pScene;
	SCENEID::ID				m_ePreScene;
	SCENEID::ID				m_eCurScene;
};


#endif // !__SCENEMGR_H__
