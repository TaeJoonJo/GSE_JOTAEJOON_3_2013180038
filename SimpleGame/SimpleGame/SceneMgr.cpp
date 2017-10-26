#include "stdafx.h"
#include "Renderer.h"
#include "SceneMgr.h"
#include "Function.h"

CSceneMgr::CSceneMgr()
	: g_Renderer(NULL),
	m_ftime(0.f)
{
	m_ftime = timeGetTime();
}

CSceneMgr::~CSceneMgr()
{
	delete g_Renderer;

	//delete[] m_GameObjects;
	for (auto d : m_vGameObjects)
		delete d;
	m_vGameObjects.clear();
}

bool CSceneMgr::Ready_Renderer()
{
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
		return false;


	return true;
}

bool CSceneMgr::Ready_Objects()
{
	/*for(int i = 0; i < MAX_ObJECTS_COUNT; ++i)
	{ 
		CGameObject* nRect = new CRect;
		((CRect*)nRect)->SetDirection(RandDir(), RandDir(), 0.f);

		m_vGameObjects.push_back(nRect);
	}

	if (m_vGameObjects.size() != MAX_ObJECTS_COUNT)
		return false;*/

	return true;
}

void CSceneMgr::Update_Objects(float time)
{
	/*time -= m_ftime;
	float framepertime = time * 0.001f;
	m_ftime = time;*/

	/*for (auto iter = m_vGameObjects.begin(); iter != m_vGameObjects.end();)
	{
		if (((CRect*)(*iter))->GetLifetime() <= 0)
		{
			auto temp = iter;
			++iter;
			delete *temp;
		}
		else
		{
			++iter;
		}
	}*/

	for (int i = 0; i < m_vGameObjects.size(); ++i)
	{
		for (int j = 0; j < m_vGameObjects.size(); ++j)
		{
			if (CollisionRect(m_vGameObjects[i], m_vGameObjects[j]) && m_vGameObjects[i] != m_vGameObjects[j])
			{
				((CRect *)m_vGameObjects[i])->Colide(true);
				((CRect *)m_vGameObjects[j])->Colide(true);
				break;
			}
			else
			{
				((CRect *)m_vGameObjects[i])->Colide(false);
				((CRect *)m_vGameObjects[j])->Colide(false);
			}
		}
	}

	for (auto d : m_vGameObjects)
		((CRect *)d)->Update(time);
}

void CSceneMgr::Draw_Objects()
{
	if (m_vGameObjects.size() > 0)
	{
		for (int i = 0; i < m_vGameObjects.size(); ++i)
		{
			g_Renderer->DrawSolidRect(m_vGameObjects[i]);
		}
	}
}

void CSceneMgr::Add_Object(float x, float y, float lifetime)
{
	if (m_vGameObjects.size() < MAX_ObJECTS_COUNT)
	{
		CGameObject* nRect = new CRect(x, y, lifetime);
		((CRect *)nRect)->SetDirection(1.f, 1.f, 0.f);

		m_vGameObjects.push_back(nRect);
	}
	else
	{
		printf("MAX COUNT OBJECT OVER\n");
	}
}