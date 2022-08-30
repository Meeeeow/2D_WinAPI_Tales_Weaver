#pragma once
#ifndef __FIELD2_H__
#define __FIELD2_H__

#include "Scene.h"
class CField2 :	public CScene
{
public:
	CField2();
	virtual ~CField2();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	DWORD m_dGenCool;

};


#endif // !__FIELD2_H__
