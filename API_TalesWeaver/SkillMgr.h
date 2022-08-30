#pragma once

#ifndef __SKILLMGR_H__
#define __SKILLMGR_H__



class CSkillMgr
{
private:
	CSkillMgr();
	~CSkillMgr();

public:
	static CSkillMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSkillMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CSkillMgr* m_pInstance;
};


#endif // !__SKILLMGR_H__
