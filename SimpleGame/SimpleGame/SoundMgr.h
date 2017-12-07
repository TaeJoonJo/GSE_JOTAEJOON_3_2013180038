#pragma once

#include "Sound.h"

class CSoundMgr
{
public:
	CSoundMgr();
	~CSoundMgr();
private:
	Sound *m_Sound;
private:
	int m_BgSound;
	int m_ShootSound;
public:
	inline void BgSound() {
		m_Sound->PlaySound(m_BgSound, true, 0.5f);
	}
	inline void Shoot() {
		m_Sound->PlaySound(m_ShootSound, false, 0.5f);
	}

	void Init();
};

