#include "GameObject.h"
#include "Rect.h"

#pragma once
class CSceneMgr
{
protected:
	CGameObject* m_GameObjects;
public:
	CSceneMgr();
	~CSceneMgr();
public:
	void Ready_Objects();
	void Update_Objects();
	inline CGameObject* Get_Object(int index) {
		return &(m_GameObjects[index]);
	}
};

