#include "GameObject.h"

#pragma once
class CRect :public CGameObject
{
protected:
public:
	CRect();
	CRect(float x, float y, float z, float size, float r, float g, float b, float a);
	~CRect();
public:
	void Render_GameObject();
	void Update_GameObject();
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
public:
	void Release();
};

