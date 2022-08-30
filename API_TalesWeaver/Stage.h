#pragma once
#ifndef __STAGE_H__
#define __STAGE_H__



#include "Scene.h"
class CTile;
class CStage :	public CScene
{
public:
	CStage();
	virtual ~CStage();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool m_bChat;
	bool m_bLockDoor;
	RECT rc1;
	RECT rc2;
	RECT rc3;
};


#endif // !__STAGE_H__
