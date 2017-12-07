#include "stdafx.h"
#include "SoundMgr.h"

CSoundMgr::CSoundMgr()
	:
	m_BgSound(0)
{
	m_Sound = new Sound();
}

CSoundMgr::~CSoundMgr()
{
	m_Sound->DeleteSound(m_BgSound);
	m_Sound->DeleteSound(m_ShootSound);

	delete m_Sound;
}

void CSoundMgr::Init()
{
	m_BgSound = m_Sound->CreateSound("../Resource/Sound/Work.mp3");
	m_ShootSound = m_Sound->CreateSound("../Resource/Sound/Shoot.wav");
}