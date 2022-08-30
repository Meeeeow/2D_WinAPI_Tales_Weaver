#pragma once
#ifndef __MAINMENU_H__
#define __MAINMENU_H__



#include "Scene.h"
class CBALButton;
class CMainMenu :	public CScene
{
public:
	CMainMenu();
	virtual ~CMainMenu();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	RECT Start;
	int iStart;
	RECT Credit;
	int iCredit;
	RECT Exit;
	int iExit;
};


#endif // !__MAINMENU_H__

