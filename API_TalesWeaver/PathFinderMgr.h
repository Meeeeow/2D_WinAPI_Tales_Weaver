#pragma once
#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__


class CPathFinderMgr
{
private:
	CPathFinderMgr();
	~CPathFinderMgr();

public:
	void Do_Find_Path(INFO _playerPos, INFO _endPos);
public:
	static CPathFinderMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CPathFinderMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}
private:
	static CPathFinderMgr*	m_pInstance;
	int						m_igCost;
	int						m_ihCost;
	int						index;
};


#endif // !__PATHFINDER_H__
