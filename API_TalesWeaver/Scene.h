#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__


class CTile;
class CScene
{
public:
	CScene();
	~CScene();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;


public:
	static void See_Tile()
	{
		if (!m_bTile)
			m_bTile = !m_bTile;
		else if (m_bTile)
			m_bTile = !m_bTile;
	}
	static void See_Hitbox()
	{
		if (!m_bHitbox)
			m_bHitbox = !m_bHitbox;
		else if (m_bHitbox)
			m_bHitbox = !m_bHitbox;
	}
protected:
	static bool			m_bTile;
	static bool			m_bHitbox;
};


#endif // !__SCENE_H__

