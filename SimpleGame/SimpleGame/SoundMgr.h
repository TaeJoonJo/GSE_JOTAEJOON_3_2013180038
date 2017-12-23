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
	static int m_Char_ExplosionSound;
	static int m_Bui_ExplosionSound;
	static int m_ClickSound;
	static int m_GenSound;
	static int m_SelectSound;
public:
	static inline void BgSound() {
		m_Sound->PlaySound(m_BgSound, true, 1.f);
	}
	static inline void Shoot() {
		m_Sound->PlaySound(m_ShootSound, false, 1.f);
	}
	static inline void Bow() {
		m_Sound->PlaySound(m_BowSound, false, 1.f);
	}
	static inline void Char_Explosion() {
		m_Sound->PlaySound(m_Char_ExplosionSound, false, 0.5f);
	}
	static inline void Bui_Explosion() {
		m_Sound->PlaySound(m_Bui_ExplosionSound, false, 0.5f);
	}
	static inline void Click() {
		m_Sound->PlaySound(m_ClickSound, false, 1.f);
	}
	static inline void Gen() {
		m_Sound->PlaySound(m_GenSound, false, 0.5f);
	}
	static inline void Select() {
		m_Sound->PlaySound(m_SelectSound, false, 1.f);
	}
	void Init();
};

