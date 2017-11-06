#pragma once

class CGameObject
{
protected:
	float m_flifetime;
	float m_flife;

	float m_fx;
	float m_fy;
	float m_fz;
	float m_fsize;

	float m_fspeed;

	// R G B A
	float m_fred;
	float m_fgreen;
	float m_fblue;
	float m_falpha;

	int m_ntype;

	float m_fcolidetimer;
public:
	bool m_isColied;
public:
	CGameObject();
	~CGameObject();
public:
	virtual void Render();
	virtual void Update();

	inline float GetX() {
		return m_fx;
	}
	inline float GetY() {
		return m_fy;
	}
	inline float GetZ() {
		return m_fz;
	}
	inline float GetSize() {
		return m_fsize;
	}
	inline float GetRed() {
		return m_fred;
	}
	inline float GetGreen() {
		return m_fgreen;
	}
	inline float GetBlue() {
		return m_fblue;
	}
	inline float GetAlpha() {
		return m_falpha;
	}
	inline float GetLife() {
		return m_flife;
	}
	inline float GetLifetime() {
		return m_flifetime;
	}
	inline int GetType() {
		return m_ntype;
	}

	inline void SetPosition(float x, float y, float z) {
		m_fx = x; m_fy = y; m_fz = z;
	}
	inline void SetColor(float r, float g, float b, float a) {
		m_fred = r; m_fgreen = g; m_fblue = b; m_falpha = a;
	}
	inline void SetLife(float life) {
		m_flife = life;
	}
	inline void SetLifetime(float lifetime) {
		m_flifetime = lifetime;
	}
	inline void Attacked(float damage = 0.f) {
		if(m_flife > 0.f) m_flife -= damage;
		m_isColied = true;
	}
	inline float Attack() {
		float temp = m_flife;
		m_flife = 0.f;
		m_isColied = true;
		return temp;
	}
	
public:
	virtual void Release() = 0;
};

