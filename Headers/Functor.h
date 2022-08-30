#pragma once
#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

class CStrCmp
{
public:
	CStrCmp(const TCHAR* _pString) : m_pString(_pString) {}

public:
	template<typename T>
	bool operator()(T& _Dst)
	{
		return !lstrcmp(_Dst.first, m_pString);
	}

private:
	const TCHAR*	m_pString;
};
class CFindItem
{
public:
	CFindItem(const TCHAR* _pName) : m_pName(_pName) {}
public:
	//template<ITEMINFO>
	bool operator()(ITEMINFO _Dst)
	{
		return !lstrcmp(_Dst.pInvenName, m_pName);
	}

private:
	const TCHAR* m_pName;
};

class CFind_Item_Count
{
public:
	CFind_Item_Count(const TCHAR* _pName) : m_pName(_pName) {}
public:
	//template<ITEMINFO>
	bool operator()(ITEMINFO _Dst)
	{
		return !lstrcmp(_Dst.pInvenName, m_pName);
	}

private:
	const TCHAR* m_pName;
};

class CIdCmp
{
public:
	CIdCmp(int _id) : ID(_id) {}
public:
	template<CTile*>
	bool operator() (CTile* _dst)
	{
		return !lstrcmp(_dst->Get_DrawID(), ID);
	}
private:
	int ID;
};
#endif // !__FUNCTOR_H__
