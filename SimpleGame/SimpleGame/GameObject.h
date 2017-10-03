#pragma once
class CGameObject
{
protected:
	float m_fx;
	float m_fy;
	float m_fz;
	float m_fsize;

	// R G B A
	float m_fred;
	float m_fgreen;
	float m_fblue;
	float m_falpha;
public:
	CGameObject();
	~CGameObject();
public:
	virtual void Render_GameObject();
	virtual void Update_GameObject();
public:
	virtual void Release() = 0;
};

