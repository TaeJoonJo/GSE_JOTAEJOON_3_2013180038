#pragma once

#include "GameObject.h"
#include "Rect.h"

class CSceneMgr
{
protected:
	Renderer *g_Renderer;

	std::vector<CGameObject*> m_vGameObjects;

	float m_ftime;
public:
	CSceneMgr();
	~CSceneMgr();
public:
	bool Ready_Renderer();
	bool Ready_Objects();
	void Update_Objects(float time);
	void Draw_Objects();
public:
	inline CGameObject* Get_Object(int index) {
		return (m_vGameObjects[index]);
	}
	void Add_Object(float x, float y, float lifetime);
};