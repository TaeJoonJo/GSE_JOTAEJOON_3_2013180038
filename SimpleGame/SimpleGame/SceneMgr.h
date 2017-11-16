#pragma once

#include "GameObject.h"
#include "Rect.h"

class Renderer;

class CSceneMgr
{
protected:
	static Renderer *g_Renderer;

	static vector<CGameObject*> m_vGameObjects;

	float m_fRedCharacterTimer;

	static int m_nobjectId;

	unsigned int m_nchartexId;
	unsigned int m_nredbuildingtexId;
	unsigned int m_nbluebuildingtexId;
public:
	CSceneMgr();
	~CSceneMgr();
public:
	bool Ready_Renderer();
	bool Ready_Objects();
	void Update_Objects(float time);
	void Draw_Objects();

	static Renderer* GetRenderer() {
		return g_Renderer;
	}
public:
	inline CGameObject* Get_Object(int index) {
		return (m_vGameObjects[index]);
	}
	void Add_Object(float x, float y, int type, int team);
	static void Add_Object(float x, float y, int type, int id, int team);
};
