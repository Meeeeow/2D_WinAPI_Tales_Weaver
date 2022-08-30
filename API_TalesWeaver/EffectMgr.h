#pragma once
#ifndef __EFFECTMGR_H__
#define __EFFECTMGR_H__

class CEffect;
class CTile;
class CEffectMgr
{
private:
	CEffectMgr();
	~CEffectMgr();

public:
	void Add_Effect(CEffect* _effect, EFFECTID::ID _num) { m_lEffect[_num].emplace_back(_effect); }
	void Render(HDC _DC, EFFECTID::ID _num, const TCHAR* _pFrameKey);
	void Release();

public:
	void Start_Render(EFFECTID::ID _num);
	void Stop_Render(EFFECTID::ID _num);
	void Update_Rect(EFFECTID::ID _num, INFO _rc);
	void Check_Vector(EFFECTID::ID _num,CTile* _Tile, float _x, float _y);
	void Delete_Font(EFFECTID::ID _num);
public:
	static CEffectMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CEffectMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CEffectMgr* m_pInstance;
	list<CEffect*>	m_lEffect[EFFECTID::END];
};


#endif // !__EFFECTMGR_H__
