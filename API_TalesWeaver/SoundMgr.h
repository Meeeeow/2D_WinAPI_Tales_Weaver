#pragma once
class CSoundMgr
{
public:
	static CSoundMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundMgr; 

		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
public:
	enum CHANNELID {BGM, PLAYER, PLAYERATK , PLAYERRUN ,PLAYERFB,PLAYERFBB , PLAYERPOTION
		, JELLYBEE_ATK,JELLYBEE_HIT,JELLYBEE_DEAD
		, GARGOYLE_ATK,GARGOYLE_HIT, GARGOYLE_SILVER_HIT,GARGOYLE_DEAD
		, NORMALBOSS_ATK, NORMALBOSS_HIT, NORMALBOSS_SILVER_HIT, NORMALBOSS_DEAD
		, BLUEWOLF_ATK, BLUEWOLF_HIT, BLUEWOLF_DEAD
		, HARDBOSS_ATK, HARDBOSS_SKILL, HARDBOSS_FIRE, HARDBOSS_DODGE, HARDBOSS_HIT,HARDBOSS_DEAD 
		, EFFECT, UI,BUTTON, CLICKBUTTON,MAXCHANNEL};
private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize(); 

	void Release(); 
public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();

private:
	void LoadSoundFile(); 

private:
	static CSoundMgr* m_pInstance; 
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem; 

};

