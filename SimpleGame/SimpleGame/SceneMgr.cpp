#include "stdafx.h"
#include "Renderer.h"
#include "SceneMgr.h"
#include "Function.h"

Renderer *CSceneMgr::g_Renderer = NULL;

vector<CGameObject*> CSceneMgr::m_vGameObjects = vector<CGameObject*>();
int CSceneMgr::m_nobjectId = 0;

CSceneMgr::CSceneMgr()
	:m_nbuildingtexId(0), m_nchartexId(0)
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
	m_nchartexId = g_Renderer->CreatePngTexture("../Resource/Planet.png");
	m_nbuildingtexId = g_Renderer->CreatePngTexture("../Resource/Moon.png");

	Add_Object(0.f, 0.f, OBJECT_BUILDING);

	return true;
}

void CSceneMgr::Update_Objects(float time)
{
	float elsapedtime = time * 0.001f;
	if (elsapedtime > 10.f)
		elsapedtime = 10.f;

	// Delete
	for (VECTORITERATOR iter = m_vGameObjects.begin(); iter != m_vGameObjects.end();)
	{
		if (((*iter)->GetLifetime() <= 0) || ((*iter)->GetLife() <= 0))
		{
			if ((*iter)->GetType() == OBJECT_CHARACTER || (*iter)->GetType() == OBJECT_BUILDING)
			{
				int charid = (*iter)->GetID();
				for (VECTORITERATOR biter = iter; biter != m_vGameObjects.end();)
				{
					int bulletid = (*biter)->GetID();
					if (bulletid == charid)
					{
						if (biter == iter)
						{
							biter = m_vGameObjects.erase(biter);
							iter = biter;
						}
						else
							biter = m_vGameObjects.erase(biter);
					}
					else
					{
						++biter;
					}
				}
			}
			else
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
					m_vGameObjects[i]->Attacked();
					m_vGameObjects[j]->Attacked();
				}
				// 빌딩과 캐릭터간의 충돌
				if (itype == OBJECT_BUILDING && jtype == OBJECT_CHARACTER)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
				// 빌딩과 화살간의 충돌
				if (itype == OBJECT_BUILDING && jtype == OBJECT_ARROW)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
				// 캐릭터와 빌딩간의 충돌
				if (itype == OBJECT_CHARACTER && jtype == OBJECT_BULLET)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
				// 캐릭터와 화살간의 충돌
				if (itype == OBJECT_CHARACTER && jtype == OBJECT_ARROW)
				{
					if(m_vGameObjects[i]->GetID() != m_vGameObjects[j]->GetID())
						m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
			}
		}
	}

	for (int i = 0; i < m_vGameObjects.size(); ++i)
		if (m_vGameObjects[i] != NULL)
			m_vGameObjects[i]->Update(elsapedtime);
}

void CSceneMgr::Draw_Objects()
{
	if (m_vGameObjects.size() > 0)
	{
		for (int i = 0; i < m_vGameObjects.size(); ++i)
		{
			if (m_vGameObjects[i] != NULL)
			{
				int type = m_vGameObjects[i]->GetType();
				if (type == OBJECT_BUILDING || type == OBJECT_CHARACTER)
					g_Renderer->DrawTexturedRect(m_vGameObjects[i], m_vGameObjects[i]->GettexID());
				else
					g_Renderer->DrawSolidRect(m_vGameObjects[i]);

			}
		}
	}
}

void CSceneMgr::Add_Object(float x, float y, int type)
{
	if (m_vGameObjects.size() < MAX_ObJECTS_COUNT)
	{
		CGameObject* nRect = new CRect(x, y, type);
		((CRect *)nRect)->SetDirection(GetRandomExceptZero(-1.f, 1.f), GetRandomExceptZero(-1.f, 1.f), 0.f);

		nRect->SetId(m_nobjectId++);

		if (type == OBJECT_CHARACTER)
			nRect->SettexID(m_nchartexId);
		else if (type == OBJECT_BUILDING)
			nRect->SettexID(m_nbuildingtexId);

		m_vGameObjects.push_back(nRect);
	}
	else
	{
		printf("MAX OBJECT COUNT OVER\n");
	}
}

void CSceneMgr::Add_Object(float x, float y, int type, int id)
{
	if (m_vGameObjects.size() < MAX_ObJECTS_COUNT)
	{
		CGameObject* nRect = new CRect(x, y, type);
		((CRect *)nRect)->SetDirection(GetRandomExceptZero(-1.f, 1.f), GetRandomExceptZero(-1.f, 1.f), 0.f);
		nRect->SetId(id);

		m_vGameObjects.push_back(nRect);
	}
	else
	{
		printf("MAX OBJECT COUNT OVER\n");
	}
}