#pragma once
#ifndef __WARPGATE_H__
#define __WARPGATE_H__

class CWarpGate
{
public:
	CWarpGate();
	~CWarpGate();

	void Initialize(float _x, float _y, float _fX, float _fY);
	void Set_Warp(SCENEID::ID _iD) { WarpStage = _iD; }
	void Update_Rect();
	void Frame_Update();

	void Render(HDC _DC);

	void Stage_Move();
	RECT Get_Rect() { return m_tRect; }
private:
	RECT m_tRect;
	INFO m_tInfo;
	FRAME m_tFrame;
	SCENEID::ID WarpStage;
	POINT m_tPosition;
};




#endif // !__WARPGATE_H__
