#pragma once
#ifndef __DROPITEMMGR_H__
#define __DROPITEMMGR_H__
class CDropItem;
class CDropItemMgr
{
private:
	CDropItemMgr();
	~CDropItemMgr();
public:
	void Add_Object(CDropItem* _Item,DROPID::ID _eID) { m_lItem[_eID].emplace_back(_Item); }
	void Render(HDC _DC, DROPID::ID _eID);
	void Release();

public:
	static CDropItemMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CDropItemMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CDropItemMgr* m_pInstance;
	list<CDropItem*>	m_lItem[DROPID::END];
};


#endif // !__DROPITEMMGR_H__
