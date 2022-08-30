#pragma once
#ifndef __MONSTER_LIFE_BAR_H__
#define __MONSTER_LIFE_BAR_H__

#include "UserInterface.h"
class CMonsterLifeBar :	public CUserInterface
{
public:
	CMonsterLifeBar();
	virtual ~CMonsterLifeBar();

	// CUserInterface을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Render(HDC _DC) override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;

	void Rect_Update(RECT _rc);
	void Set_Bar(float _x);
private:
	float Life_Bar;
};


#endif // !__MONSTER_LIFE_BAR_H__
