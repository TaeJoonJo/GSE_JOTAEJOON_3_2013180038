#include "GameObject.h"

#pragma once
class CRect :public CGameObject
{
protected:
	float m_fxmoved;
	float m_fymoved;
	float m_fzmoved;
public:
	CRect();
	CRect(float x, float y, float z, float size, float speed, float r, float g, float b, float a);
	CRect(float x, float y);
	~CRect();
public:
	void Render();
	void Update();
public:
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
	inline void SetSpeed(float speed) {
		m_fspeed = speed;
	}
	inline void SetDirection(float x, float y, float z)
	{
		m_fxmoved = x;
		m_fymoved = y;
		m_fzmoved = z;
	}
	inline void SetRandPot() {
		m_fx = (rand() % 500) - 250.f;
		m_fy = (rand() % 500) - 250.f;
	}

	void MovexybySpeed();
	void MovebyMouse(int x, int y);
public:
	void Release();
};

