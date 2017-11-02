#pragma once

#include "GameObject.h"

class CRect :public CGameObject
{
protected:
	float m_fxmoved;
	float m_fymoved;
	float m_fzmoved;

	float m_fsmoved;
	float m_foriginsize;
public:
	CRect();
	//CRect(float x, float y, float z, float size, float speed, float r, float g, float b, float a);
	//CRect(float x, float y, float lifetime);
	CRect(float x, float y, int type);
	~CRect();
public:
	void Render();
	void Update(float time);
public:
	inline float GetLifetime() {
		return m_flifetime;
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
	inline void Colide(bool iscolied) {
		/*m_fxmoved *= -1.f;
		m_fymoved *= -1.f;*/
		if (iscolied)
		{
			m_fred = 1.f;
			m_fblue = 0.f;
			m_fgreen = 0.f;
		}
		if (!iscolied)
		{
			m_fred = 1.f;
			m_fblue = 1.f;
			m_fgreen = 1.f;
		}
	}

	void MovexybySpeed(float time);
	void MovebyMouse(int x, int y);
public:
	void Release();
};

