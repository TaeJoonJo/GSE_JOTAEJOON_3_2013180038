#pragma once

#include "GameObject.h"
#include "Rect.h"

class CSceneMgr
{
protected:
	//CGameObject* m_GameObjects;
	std::vector<CGameObject*> m_vGameObjects;
public:
	CSceneMgr();
	~CSceneMgr();
public:
	void Ready_Objects();
	void Update_Objects();
	/*inline CGameObject* Get_Object(int index) {
		return &(m_GameObjects[index]);
	}*/
	inline CGameObject* Get_Object(int index) {
		return (m_vGameObjects[index]);
	}
};