#include "stdafx.h"
#include "SoundMgr.h"

Sound *CSoundMgr::m_Sound;
int CSoundMgr::m_BgSound;
int CSoundMgr::m_ShootSound;
int CSoundMgr::m_BowSound;

CSoundMgr::CSoundMgr()
{
	m_Sound = new Sound();
}

CSoundMgr::~CSoundMgr()
{
	m_Sound->DeleteSound(m_BgSound);
	m_Sound->DeleteSound(m_ShootSound);
	m_Sound->DeleteSound(m_BowSound);

	delete m_Sound;
}

void CSoundMgr::Init()
{
	//m_BgSound = m_Sound->CreateSound("../Resource/Sound/Work.mp3");
	//m_BgSound = m_Sound->CreateSound("../Resource/Sound/CrossSpace.mp3");
	m_BgSound = m_Sound->CreateSound("../Resource/Sound/Worth_it.mp3");
	m_ShootSound = m_Sound->CreateSound("../Resource/Sound/Shoot.wav");
	m_BowSound = m_Sound->CreateSound("../Resource/Sound/Bow.ogg");
}