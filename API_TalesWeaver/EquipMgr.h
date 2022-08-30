#pragma once
class CEquipMgr
{
private:
	CEquipMgr();
	~CEquipMgr();
public:
	void Add_EQUIP(EQUIPID::ID _eID, ITEMINFO _Item);
	void Change_EQUIP(EQUIPID::ID _eID, ITEMINFO _Item);
	void Render(HDC _DC,RECT _rc);
	vector<ITEMINFO> Get_Info(EQUIPID::ID _eID) { return m_vEquipment[_eID]; }
	int Get_Dmg();
	int Get_Def();
	int Get_Hp();
	int Get_Mp();
	int Get_Sp();
public:
	static CEquipMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CEquipMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
private:
	static CEquipMgr* m_pInstance;
	vector<ITEMINFO> m_vEquipment[EQUIPID::END];
};

