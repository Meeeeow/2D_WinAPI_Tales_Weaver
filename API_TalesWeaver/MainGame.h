#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CMouse;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC		m_hDC;

	int		m_iFPS;
	DWORD	dwTime;
};


#endif // !__MAINGAME_H__
