#include "stdafx.h"
#include "Effect.h"


CEffect::CEffect()
	:m_bRender(false)
{
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
}


CEffect::~CEffect()
{
}

void CEffect::Frame_Update()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iStartX > m_tFrame.iEndX)
		{
			m_tFrame.iStartX = 0;
			m_bRender = false;
		}
	}
}

