#include "stdafx.h"
#include "SceneMgr.h"
#include "Function.h"

CSceneMgr::CSceneMgr()
{
	
}

CSceneMgr::~CSceneMgr()
{
	//delete[] m_GameObjects;
	for (auto d : m_vGameObjects)
		delete d;
	m_vGameObjects.clear();
}

void CSceneMgr::Ready_Objects()
{
	/*m_GameObjects = new CRect[MAX_ObJECTS_COUNT];

	for (int i = 0; i < MAX_ObJECTS_COUNT; ++i)
	{
		((CRect*)m_GameObjects)[i].SetDirection(RandDir(), RandDir(), 0.f);
		m_GameObjects[i];
	}*/
	for(int i = 0; i < MAX_ObJECTS_COUNT; ++i)
	{ 
		CGameObject* nRect = new CRect;
		((CRect*)nRect)->SetDirection(RandDir(), RandDir(), 0.f);

		m_vGameObjects.push_back(nRect);
	}
}

void CSceneMgr::Update_Objects(void)
{
	/*for (int i = 0; i < MAX_ObJECTS_COUNT; ++i)
		((CRect*)m_GameObjects)[i].Update();*/

	for(auto a : m_vGameObjects)
		for (auto b : m_vGameObjects)
		{
			if (CollisionRect(a, b) && a != b)
			{
				((CRect *)a)->Colide();
				((CRect *)b)->Colide();
				break;
			}
		}

	for (auto d : m_vGameObjects)
		((CRect *)d)->Update();
}
