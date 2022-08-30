#pragma once
#ifndef __TILEMGR_H__
#define __TILEMGR_H__
class CTile;
class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	void Update();
	void Set_Tile(int x, int y);
	void Render(HDC _DC,int tileX);
	void Release();

public:
	void is_Picking_Tile(int _X);
	void is_Picking_Tile_Down(int _X);
	void Load_Tile(const TCHAR* _pPath);
	void Save_Tile(const TCHAR* _pPath);
	void Find_Tile(int _id);
	void is_Tile_Reset(CTile* _pTile);
	size_t is_Tile_Size() { return m_PreTile.size(); }
public:
	void Pre_Tile(vector<CTile*>& _pTile) { m_PreTile = _pTile; }
	vector<CTile*>& Get_Tile() { return m_PreTile; }
	CTile* Get_Tile_N(size_t _size) { return m_PreTile[_size]; }
public:
	static CTileMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}


private:
	static CTileMgr*				m_pInstance;
	vector<CTile*>					m_PreTile;

};


#endif // !__TILEMGR_H__
