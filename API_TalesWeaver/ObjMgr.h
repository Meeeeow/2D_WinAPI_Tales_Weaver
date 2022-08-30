#pragma once
#ifndef __OBJMGR_H__
#define __OBJMGR_H__
class CObj;
class CPlayer;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(CObj* _pObj, OBJID::ID _eID) { m_listObj[_eID].emplace_back(_pObj); }
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Monster_Render(HDC _DC,OBJID::ID _eID);
	void Hitbox_Render(HDC _DC ,OBJID::ID _eID);
	void Release();
	void Release_ID(OBJID::ID _eid);

	list<CObj*> Get_Player() { return m_listObj[OBJID::PLAYER]; }
	list<CObj*> Get_List(OBJID::ID _id);
	list<CObj*> Get_ListMon();
	void Set_Pos(int _x, int _y);
	INFO Get_INFO();
	RECT Get_Hit_Box(OBJID::ID _iD);
public:
	static CObjMgr*	Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
private:
	static CObjMgr*		m_pInstance;
	list<CObj*>			m_listObj[OBJID::END];
};


#endif // !__OBJMGR_H__
