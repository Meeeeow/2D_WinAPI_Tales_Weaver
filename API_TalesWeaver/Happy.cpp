#include "stdafx.h"
#include "Happy.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "InventoryMgr.h"
#include "SilverSword.h"
#include "Player.h"
#include "EquipMgr.h"
#include "SilverArmor.h"

CHappy::CHappy()
	:m_eCurState(END), m_ePreState(END)
{
}


CHappy::~CHappy()
{
	Release();
}

void CHappy::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/NPC/Happy/NPC_Happy.bmp", L"HappyCat");
	m_tRect.left = 510;
	m_tRect.top = 390;
	m_tRect.right = m_tRect.left + 50;
	m_tRect.bottom = m_tRect.bottom + 50;
	m_tHitBox.left = 510;
	m_tHitBox.right = 570;
	m_tHitBox.top = 390;
	m_tHitBox.bottom = 450;
	m_eCurState = IDLE;
	m_bFirstChat = true;
	m_bChat = false;
	m_bFirstQuest = false;
	m_bSecondChat = false;
	m_bSecondQuest = false;
	m_tInfo.fX = 535;
	m_tInfo.fY = 415;
	chat1 = true;
	chat2 = false;
	chat3 = false;
}

int CHappy::Update()
{
	Frame_Check();
	Frame_Update();
	RECT rc = {};
	if (IntersectRect(&rc, &m_tHitBox, &CObjMgr::Get_Instance()->Get_Hit_Box(OBJID::PLAYER)))
	{

		m_bChat = true;
		if (!m_bFirstQuest && CInventoryMgr::Get_Instance()->Find_Item_Count(L"은괴") < 5)
			m_bFirstChat = true;
		else if (!m_bFirstQuest && CInventoryMgr::Get_Instance()->Find_Item_Count(L"은괴") >= 5)
		{
			m_tTime = GetTickCount();
			m_bFirstQuest = true;
			m_bFirstChat = false;
			CInventoryMgr::Get_Instance()->Find_Item_Decrease(L"은괴", 5);
			CDropItem* pObj = new CSilverSword;
			pObj->Initialize(m_tInfo);
			CEquipMgr::Get_Instance()->Change_EQUIP(EQUIPID::SWORD, pObj->Get_ItemINFO());
			//CInventoryMgr::Get_Instance()->Add_Item(pObj->Get_ItemINFO());
			for (auto iter : CObjMgr::Get_Instance()->Get_Player())
				static_cast<CPlayer*>(iter)->Get_Player_SilverSword();

			SAFE_DELETE(pObj);
		}
		if (!m_bFirstChat &&m_bFirstQuest &&m_bSecondChat &&!m_bSecondQuest && CInventoryMgr::Get_Instance()->Find_Item_Count(L"가고일 가죽") < 5)
		{
			m_bSecondChat = true;
		}
		else if (!m_bFirstChat &&m_bFirstQuest && m_bSecondChat && !m_bSecondQuest && CInventoryMgr::Get_Instance()->Find_Item_Count(L"가고일 가죽") >= 5)
		{
			m_tTime = GetTickCount();
			m_bSecondChat = false;
			m_bSecondQuest = true;
			CInventoryMgr::Get_Instance()->Find_Item_Decrease(L"가고일 가죽", 5);
			CDropItem* pObj = new CSilverArmor;
			pObj->Initialize(m_tInfo);
			CEquipMgr::Get_Instance()->Change_EQUIP(EQUIPID::ARMOR, pObj->Get_ItemINFO());
			for (auto iter : CObjMgr::Get_Instance()->Get_Player())
				static_cast<CPlayer*>(iter)->Get_Player_SilverArmor();
			SAFE_DELETE(pObj);
		}
	}
	else
	{
		m_bChat = false;
	
	}
	if (chat1)
	{
		if (!m_bFirstChat && m_tTime + 5000 < GetTickCount())
		{
			m_bSecondChat = true;
			chat1 = false;
			chat2 = true;
		}
	}
	if (!m_bFirstChat && !m_bSecondChat && m_bSecondQuest &&m_tTime + 5000 < GetTickCount())
	{
		m_bThirdChat = true;
		chat2 = false;
		chat3 = true;
	}
	return OBJ_NOEVENT;
}

void CHappy::Late_Update()
{
}

void CHappy::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hNPCDC = CBmpMgr::Get_Instance()->Find_Bmp(L"HappyCat");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, 50, 50
		, hNPCDC
		, m_tFrame.iStartX * 50,0
		, 50, 50
		, RGB(255, 255, 255));
	if (chat1)
	{
		if (m_bFirstChat && !m_bFirstQuest && m_bChat)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"가고일을 잡고 싶으면 젤리삐를 잡아 은괴 5개를 모아오라냥!");
			TextOut(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
		if (m_bFirstQuest && !m_bFirstChat && m_bChat)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"은검을 주었으니 가고일에게 피해가 들어갈 것이다냥!");
			TextOut(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
	if (chat2)
	{
		if (m_bSecondChat && !m_bSecondQuest && m_bChat)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"가고일의 공격이 너무 아프면 가고일 가죽 5개를 모아오라냥!");
			TextOut(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}

		if (!m_bSecondChat && m_bSecondQuest && !m_bThirdChat && m_bChat)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"반짝반짝 은 갑옷이다냥!");
			TextOut(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
	if (chat3)
	{
		if (m_bThirdChat && m_bChat)
		{
			SetBkMode(_DC, OPAQUE);
			SetBkColor(_DC, RGB(0, 0, 0));

			TCHAR szBuff[64] = L"";
			swprintf_s(szBuff, L"이만큼 해줬으면 됐지 뭘 더 바라냥!");
			TextOut(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY - 30, szBuff, lstrlen(szBuff));
		}
	}
}

void CHappy::Release()
{
	
}

void CHappy::is_Hit_Check(RECT _Rect, int _Dmg)
{
}

void CHappy::is_Magic_Hit_Check(RECT _Rect, int _Dmg)
{
}

void CHappy::Update_HitBox()
{
}

void CHappy::Frame_Check()
{
	if (m_eCurState != m_ePreState)
	{
		switch (m_eCurState)
		{
		case CHappy::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 7;
			m_tFrame.iState = IDLE;
			m_tFrame.dwDelay = 500;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CHappy::Frame_Update()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX = 0;
	}
}
