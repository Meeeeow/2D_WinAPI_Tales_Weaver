#pragma once
#ifndef __FIELD_H__
#define __FIELD_H__


#include "Scene.h"
class CField :	public CScene
{
public:
	CField();
	virtual ~CField();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	DWORD m_dGenCool;

};


#endif // !__FIELD_H__
