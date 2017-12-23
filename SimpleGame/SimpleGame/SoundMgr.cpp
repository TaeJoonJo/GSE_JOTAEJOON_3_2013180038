#include "stdafx.h"
#include "SoundMgr.h"

Sound *CSoundMgr::m_Sound;
int CSoundMgr::m_BgSound;
int CSoundMgr::m_ShootSound;
int CSoundMgr::m_BowSound;
int CSoundMgr::m_Char_ExplosionSound;
int CSoundMgr::m_Bui_ExplosionSound;
int CSoundMgr::m_ClickSound;
int CSoundMgr::m_GenSound;
int CSoundMgr::m_SelectSound;

CSoundMgr::CSoundMgr()
{
	m_Sound = new Sound();
}

CSoundMgr::~CSoundMgr()
{
	m_Sound->DeleteSound(m_BgSound);
	m_Sound->DeleteSound(m_ShootSound);
	m_Sound->DeleteSound(m_BowSound);
	m_Sound->DeleteSound(m_Char_ExplosionSound);
	m_Sound->DeleteSound(m_Bui_ExplosionSound);
	m_Sound->DeleteSound(m_ClickSound);
	m_Sound->DeleteSound(m_GenSound);
	m_Sound->DeleteSound(m_SelectSound);

	delete m_Sound;
}

void CSoundMgr::Init()
{
	//m_BgSound = m_Sound->CreateSound("../Resource/Sound/Work.mp3");
	//m_BgSound = m_Sound->CreateSound("../Resource/Sound/CrossSpace.mp3");
	//m_BgSound = m_Sound->CreateSound("../Resource/Sound/Worth_it.mp3");
	m_BgSound = m_Sound->CreateSound("../Resource/Sound/Blue_Space.wav");
	m_ShootSound = m_Sound->CreateSound("../Resource/Sound/Shoot.wav");
	m_BowSound = m_Sound->CreateSound("../Resource/Sound/Bow.ogg");
	m_Char_ExplosionSound = m_Sound->CreateSound("../Resource/Sound/explosion.wav");
	m_Bui_ExplosionSound = m_Sound->CreateSound("../Resource/Sound/explosion2.wav");
	m_ClickSound = m_Sound->CreateSound("../Resource/Sound/click_sound.mp3");
	m_GenSound = m_Sound->CreateSound("../Resource/Sound/hit.wav");
	m_SelectSound = m_Sound->CreateSound("../Resource/Sound/Select.wav");
}