#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagINFO
{
	float	fX;
	float	fY;
	int		iCX;
	int		iCY;
}INFO;

typedef struct tagFrame
{
	int		iStartX;
	int		iEndX;
	int		iState;
	DWORD	dwDelay;
	DWORD	dwTime;
}FRAME;
typedef struct tagTILEXY
{
	int		iTileX;
	int		iTileY;

}TILEXY;
typedef struct tagStats
{
	int m_iMax_HP;
	int m_iCur_HP;
	int m_iDefault_HP;

	int m_iMax_MP;
	int m_iCur_MP;
	int m_iDefault_MP;

	int m_iMax_SP;
	int m_iCur_SP;
	int m_iDefault_SP;

	int Attack_Dmg;
	int m_iDefault_Dmg;
	int Attack_Def;
	int m_iDefault_Def;

	float m_fCur_Exp;
	float m_fMax_Exp;
	int	m_iLevel;
}STATS;
typedef struct tagDmg
{
	int m_iDmg;
	bool m_bDmgRender;
	const TCHAR* m_pFrameKey;
}DMGRENDER;

typedef struct tagItem
{
	TCHAR* pInvenName;
	TCHAR* pName;
	int iDmg;
	int iDef;
	int iHP;
	int iMP;
	int iSP;
	int iValue;
	int iCount;
}ITEMINFO;

#endif // !__STRUCT_H__
