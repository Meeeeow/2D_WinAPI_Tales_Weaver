#pragma once
#ifndef __EFFECT_H__
#define __EFFECT_H__

class CEffect
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC _DC,const TCHAR* _pFrameKey) = 0;
	virtual void Release() = 0;
	virtual	void Update_Rect(INFO _rc) = 0;

	void Frame_Update();
	void Render_Start() { m_bRender = true; }
	void Render_Stop() { m_bRender = false; }

	virtual void Check_Vector(CTile* _Tile, float _x, float _y) = 0;

protected:
	RECT m_tRect;
	FRAME m_tFrame;
	bool m_bRender;

	POINT m_tEndPos;
	POINT m_tStartPos;

};


#endif // !__EFFECT_H__
