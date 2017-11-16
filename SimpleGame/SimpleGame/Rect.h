#pragma once

#include "GameObject.h"
#include "SceneMgr.h"
#include "Renderer.h"

class CRect :public CGameObject
{
protected:
	float m_fxmoved;
	float m_fymoved;
	float m_fzmoved;

	float m_fsmoved;
	float m_foriginsize;

	float m_fshoottimer;
public:
	CRect();
	//CRect(float x, float y, float z, float size, float speed, float r, float g, float b, float a);
	//CRect(float x, float y, float lifetime);
	CRect(float x, float y, int type, int team = TEAMRED);
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

	void MovexybySpeed(float time);
	void MovebyMouse(int x, int y);
public:
	void Release();
};