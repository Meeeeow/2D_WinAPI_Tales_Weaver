#pragma once
#ifndef __INVENTORY_MGR_H__
#define __INVENTORY_MGR_H__
class CDropItem;
class CInventoryMgr
{
private:
	CInventoryMgr();
	~CInventoryMgr();

public:
	void Add_Item(ITEMINFO _ITEM);
	int Find_Item_Count(TCHAR* _ITEM);
	void Find_Item_Decrease(TCHAR* _ITEM,int _Decrase);
	void Delete_Null_Item(TCHAR* _ITEM);
	void Release();
	void Render2(HDC _DC, RECT _rc);
public:
	static CInventoryMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CInventoryMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
private:
	static CInventoryMgr* m_pInstance;
	vector<ITEMINFO>	m_vInven;
};


#endif // !__INVENTORY_MGR_H__
