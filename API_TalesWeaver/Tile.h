#pragma once
#ifndef __TILE_H__
#define __TILE_H__

class CPlayer;
class CTile
{
public:
	enum TILEID { IDLE,NOMOVE, GATE, END};
public:
	CTile();
	~CTile();
public:
	void Initialize();
	void Set_Pos(int _x, int _y);
	void Set_DrawID(int _DrawID);
	int Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	const INFO& Get_Info() const { return m_tInfo; }
	const int& Get_DrawID() const { return m_iDrawID; }
	const RECT& Get_Rect() const { return m_tRect; }
	void Setting_DrawID(int _iD) { m_iDrawID = _iD; }

	bool if_Collision_Rect(RECT _coll);
	void bound_Collision_Rect(CObj* _player);
public:
	void Update_Rect();
private:
	int		m_iDrawID;
	INFO	m_tInfo;
	RECT	m_tRect;
};


#endif // !__TILE_H__
