#pragma once
#ifndef __YOUDIED_H__
#define __YOUDIED_H__

#include "Scene.h"
class CYouDied :	public CScene
{
public:
	CYouDied();
	virtual ~CYouDied();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
private:
	HWND	m_hVideo;

};


#endif // !__YOUDIED_H__
