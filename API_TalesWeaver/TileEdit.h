#pragma once
#ifndef __TILEEDIT_H__
#define __TILEEDIT_H__



#include "Scene.h"
class CTile;
class CTileEdit :	public CScene
{
public:
	CTileEdit();
	virtual ~CTileEdit();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	void Change_Scene_Stage();
	void Change_Scene_Shop();
	void Change_Scene_Field();
	void Change_Scene_Field2();
	void Change_Scene_Boss_Room();
	void Change_Scene_Boss_Hard();
	void Change_Main();
private:
	int					iScrollX;
	int					iScrollY;
	const TCHAR*		m_pFrameKey;
	const TCHAR*		m_pPathFile;
	int					iX;
	int					iY;
};


#endif // !__TILEEDIT_H__