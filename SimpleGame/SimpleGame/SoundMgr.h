#pragma once

#include "Sound.h"

class CSoundMgr
{
public:
	CSoundMgr();
	~CSoundMgr();
private:
	static Sound *m_Sound;
private:
	static int m_BgSound;
	static int m_ShootSound;
	static int m_BowSound;
public:
	static inline void BgSound() {
		m_Sound->PlaySound(m_BgSound, true, 0.5f);
	}
	static inline void Shoot() {
		m_Sound->PlaySound(m_ShootSound, false, 1.f);
	}
	static inline void Bow() {
		m_Sound->PlaySound(m_BowSound, false, 1.f);
	}
	void Init();
};

