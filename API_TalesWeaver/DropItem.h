#pragma once
#ifndef __DROPITEM_H__
#define __DROPITEM_H__

class CDropItem
{
public:
	CDropItem();
	virtual ~CDropItem();
public:
	virtual void Initialize(INFO _XY) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;
	void Add_Count() { ++m_tItem.iCount; }
	const TCHAR* Add_Frame() const { return m_tItem.pName; }
	const TCHAR* Get_Name() const { return m_tItem.pInvenName; }
	int Get_Count() { return m_tItem.iCount; }
	ITEMINFO Get_ItemINFO() { return m_tItem; }
protected:
	RECT m_tRect;
	bool m_bRender;
	ITEMINFO m_tItem;
};


#endif // !__DROPITEM_H__
