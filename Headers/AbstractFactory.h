#pragma once
#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__

class CObj;
class CTile;
class CWarpGate;
class CEffect;
class CUserInterface;

template <typename T>
class CAFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}
	static CObj* Create_Monster(int _x, int _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		return pObj;
	}
	static CTile* Create(int _x, int _y)
	{
		CTile* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos((int)_x, (int)_y);

		return pObj;
	}
	static CTile* Create(float _x, float _y, int _DrawId)
	{
		CTile* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos((int)_x,(int) _y);
		pObj->Set_DrawID(_DrawId);

		return pObj;
	}

	static CWarpGate* Create_Warp(float _x, float _y, float _fX, float _fY)
	{
		CWarpGate* pObj = new T;
		pObj->Initialize(_x,_y, _fX, _fY);

		return pObj;
	}
	static CEffect* Create_Effect()
	{
		CEffect* pObj = new T;
		pObj->Initialize();

		return pObj;
	}
	static CEffect* Create_Fire(CTile* _Target)
	{
		CEffect *pObj = new T;
		pObj->Initialize();
		pObj->Check_Vector(_Target, 1, 1);

		return pObj;
	}
	static CUserInterface* Create_Interface()
	{
		CUserInterface* pObj = new T;
		pObj->Initialize();

		return pObj;
	}
};

#endif // !__ABSTRACTFACTORY_H__
