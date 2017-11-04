#include "stdafx.h"
#include "Renderer.h"
#include "SceneMgr.h"
#include "Function.h"

CSceneMgr::CSceneMgr()
	: g_Renderer(NULL),
	m_ftime(0.f)
{
	//m_ftime = timeGetTime();
}

CSceneMgr::~CSceneMgr()
{
	delete g_Renderer;

	for (auto d : m_vGameObjects)
		delete d;
	m_vGameObjects.clear();
}

bool CSceneMgr::Ready_Renderer()
{
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
		return false;

	if (!Ready_Objects())
	{
		std::cout << "오브젝트 오류" << std::endl;
		return false;
	}
	return true;
}

bool CSceneMgr::Ready_Objects()
{
	CGameObject* pBuilding = new CRect(0.f, 0.f, OBJECT_BUILDING);
	m_vGameObjects.push_back(pBuilding);

	return true;
}

void CSceneMgr::Update_Objects(float time)
{
	float elsapedtime = time * 0.001f;
	if (elsapedtime > 10.f)
		elsapedtime = 10.f;

	if ((m_fBulletTimer += elsapedtime) > 0.5f)
	{
		for (int i = 0; i < m_vGameObjects.size(); ++i)
		{
			if (m_vGameObjects[i]->GetType() == OBJECT_BUILDING)
			{
				Add_Object(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), OBJECT_BULLET);
			}
		}
		m_fBulletTimer = 0.f;
	}

	// Delete
	for (auto iter = m_vGameObjects.begin(); iter != m_vGameObjects.end();)
	{
		if ((*iter)->GetLifetime() <= 0)
		{
			iter = m_vGameObjects.erase(iter);
		}
		else if ((*iter)->GetLife() <= 0)
		{
			iter = m_vGameObjects.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// Collsion Check
	for (int i = 0; i < m_vGameObjects.size(); ++i)
	{
		for (int j = 0; j < m_vGameObjects.size(); ++j)
		{
			if (CollisionRect(m_vGameObjects[i], m_vGameObjects[j]) && i != j)
			{
				int itype = m_vGameObjects[i]->GetType();
				int jtype = m_vGameObjects[j]->GetType();

				// 캐릭터간의 충돌
				if (itype == OBJECT_CHARACTER && jtype == OBJECT_CHARACTER)
				{
					//((CRect *)m_vGameObjects[i])->SetColor(1.f, 0.f, 0.f, 1.f);
					//((CRect *)m_vGameObjects[j])->SetColor(1.f, 0.f, 0.f, 1.f);
					m_vGameObjects[i]->m_isColied = true;
					m_vGameObjects[j]->m_isColied = true;
				}
				// 빌딩과 캐릭터간의 충돌
				if (itype == OBJECT_BUILDING && jtype == OBJECT_CHARACTER)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
				// 캐릭터와 빌딩
				if (itype == OBJECT_CHARACTER && jtype == OBJECT_BULLET)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
			}
			else if (m_vGameObjects[j]->GetType() == OBJECT_CHARACTER)
				m_vGameObjects[j]->m_isColied = false;
		}
	}

	for (auto d : m_vGameObjects)
		((CRect *)d)->Update(elsapedtime);
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

void CSceneMgr::Add_Object(float x, float y, int type)
{
	if (m_vGameObjects.size() < MAX_ObJECTS_COUNT)
	{
		CGameObject* nRect = new CRect(x, y, (int)type);
		((CRect *)nRect)->SetDirection(GetRandomExceptZero(-1.f, 1.f), GetRandomExceptZero(-1.f, 1.f), 0.f);

		m_vGameObjects.push_back(nRect);
	}
	else
	{
		printf("MAX OBJECT COUNT OVER\n");
	}
}