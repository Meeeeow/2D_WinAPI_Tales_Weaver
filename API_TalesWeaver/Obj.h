#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;
	virtual void is_Hit_Check(RECT _Rect, int _Dmg) = 0;
	virtual void is_Magic_Hit_Check(RECT _Rect, int _Dmg) = 0;
public:
	void Set_Dead();
	virtual void Update_HitBox() = 0;

	RECT Get_Hit_Box() { return m_tHitBox; }

public:
	void Update_Rect();
	void Update_Tile_Rect();
	const INFO& Get_Info() const { return m_tInfo; }
	const RECT& Get_Rect() const { return m_tRect; }

public:
	void Set_PosX(int X) { m_tInfo.fX += X; }
	void Set_PosY(int Y) { m_tInfo.fY += Y; }
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	RECT Get_Check_Rect() { return m_tCheckTile; }

public:
	void Render_Hitbox(HDC _DC);

protected:
	INFO	m_tInfo;
	RECT	m_tRect;

	float	m_fSpeed;
	float	m_fAngle;

	bool	m_bDead;
	
	FRAME	m_tFrame;
	const	TCHAR*	m_pFrameKey;

	RECT	m_tHitBox;
	bool	m_bHit;

	RECT	m_tCheckTile;
	STATS	m_tStats;
};


#endif // !__OBJ_H__
