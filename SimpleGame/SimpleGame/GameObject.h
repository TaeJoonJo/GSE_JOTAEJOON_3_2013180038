#pragma once

class CGameObject
{
protected:
	float m_flifetime;

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

	inline void SetColor(float r, float g, float b, float a) {
		m_fred = r;
		m_fblue = b;
		m_fgreen = g;
		m_falpha = a;
	}
public:
	virtual void Release() = 0;
};

