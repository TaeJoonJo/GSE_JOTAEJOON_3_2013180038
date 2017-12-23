#include "stdafx.h"
#include "Renderer.h"
#include "SceneMgr.h"
#include "Function.h"

Renderer *CSceneMgr::g_Renderer = NULL;

vector<CGameObject*> CSceneMgr::m_vGameObjects = vector<CGameObject*>();
int CSceneMgr::m_nobjectId = 0;

CSceneMgr::CSceneMgr(CSoundMgr *soundmgr)
	:m_nredbuildingtexId(0), m_nbluebuildingtexId(0), m_nredchartexId(0), m_nbluechartexId(0), m_nbackgroundtexId(0),
	m_nredbuildingspritetexId(0), m_nbluebuildingspritetexId(0), m_nredcharspritetexId(0), m_nbluecharspritetexId(0), 
	m_npaticletexId(0), m_ncharexplosiontexId(0), m_nbuiexplosiontexId(0), m_nstartexId(0),
	m_fRedCharacterTimer(0.f),
	m_fQuakeTimer(0.f), m_bQuake(false),
	m_nMoney(0), m_fMoneyTimer(0.f)
{
	m_pSoundMgr = soundmgr;
	//m_ftime = timeGetTime();
}

CSceneMgr::~CSceneMgr()
{
	delete g_Renderer;
	delete m_pSoundMgr;

	for (auto d : m_vGameObjects)
		delete d;
	m_vGameObjects.clear();
}

bool CSceneMgr::Ready_Renderer()
{
	g_Renderer = new Renderer(WINSIZEX, WINSIZEY);
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
	m_nbackgroundtexId = g_Renderer->CreatePngTexture("../Resource/Space.png");
	/*m_nbluechartexId = g_Renderer->CreatePngTexture("../Resource/BlueUnit.png");
	m_nredchartexId = g_Renderer->CreatePngTexture("../Resource/RedUnit.png");*/

	//m_nbluebuildingtexId = g_Renderer->CreatePngTexture("../Resource/Moon.png");
	//m_nredbuildingtexId = g_Renderer->CreatePngTexture("../Resource/Planet.png");

	m_nstartexId = g_Renderer->CreatePngTexture("../Resource/Star2.png");

	m_npaticletexId = g_Renderer->CreatePngTexture("../Resource/Paticle2.png");
	m_ncharexplosiontexId = g_Renderer->CreatePngTexture("../Resource/explosion.png");
	m_nbuiexplosiontexId = g_Renderer->CreatePngTexture("../Resource/explosion2.png");

	// 5x4
	m_nbluecharspritetexId = g_Renderer->CreatePngTexture("../Resource/rocksprite2.png");
	// 5x4
	m_nredcharspritetexId = g_Renderer->CreatePngTexture("../Resource/rocksprite1.png");

	// 5x4
	m_nbluebuildingspritetexId = g_Renderer->CreatePngTexture("../Resource/Earthsprite.png");
	// 5x4
	m_nredbuildingspritetexId = g_Renderer->CreatePngTexture("../Resource/Marssprite.png");

	// 배경
	Add_Object(0.f, 0.f, OBJECT_BACKGROUND, -1);

	Add_Object(-200.f, WINHALFSIZEY - 100.f, OBJECT_BUILDING, TEAMRED);
	Add_Object(0.f, WINHALFSIZEY - 100.f, OBJECT_BUILDING, TEAMRED);
	Add_Object(200.f, WINHALFSIZEY - 100.f, OBJECT_BUILDING, TEAMRED);

	Add_Object(-200.f, -WINHALFSIZEY + 100.f, OBJECT_BUILDING, TEAMBLUE);
	Add_Object(0.f, -WINHALFSIZEY + 100.f, OBJECT_BUILDING, TEAMBLUE);
	Add_Object(200.f, -WINHALFSIZEY + 100.f, OBJECT_BUILDING, TEAMBLUE);

	m_pSoundMgr->BgSound();

	return true;
}

void CSceneMgr::Update_Objects(float time)
{
	float elsapedtime = time * 0.001f;
	if (elsapedtime > 10.f)
		elsapedtime = 10.f;

	if ((m_fMoneyTimer += elsapedtime) > TIMER_MONEY)
	{
		Earn(EARNING);

		m_fMoneyTimer = 0.f;
	}

	if ((m_fRedCharacterTimer += elsapedtime) > REGENTIMER_RED)
	{
		Add_Object(GetRandom(-WINHALFSIZEX, WINHALFSIZEX), GetRandom(0.f, WINHALFSIZEY), OBJECT_CHARACTER, TEAMRED);

		m_fRedCharacterTimer = 0.f;
	}

	if (m_bQuake)
	{
		float quakedegree = sin(m_fQuakeTimer * 40.f) * 20.f;

		g_Renderer->SetSceneTransform(quakedegree, 0.f, 1.f, 1.f);
		if ((m_fQuakeTimer += elsapedtime) > TIMER_QUAKE)
		{
			g_Renderer->SetSceneTransform(0.f, 0.f, 1.f, 1.f);

			m_fQuakeTimer = 0.f;
			m_bQuake = false;
		}
	}

	// Delete
	for (VECTORITERATOR iter = m_vGameObjects.begin(); iter != m_vGameObjects.end();)
	{
		int type = (*iter)->GetType();
		if (type == OBJECT_ARROW || type == OBJECT_BULLET)
		{
			if ((*iter)->GetX() < -WINHALFSIZEX || (*iter)->GetX() > WINHALFSIZEX ||
				(*iter)->GetY() < -WINHALFSIZEY || (*iter)->GetY() > WINHALFSIZEY)
				(*iter)->Attack();
		}
		if (((*iter)->GetLifetime() <= 0) || ((*iter)->GetLife() <= 0))
		{
			if ((*iter)->GetType() == OBJECT_CHARACTER || (*iter)->GetType() == OBJECT_BUILDING)
			{
				if((*iter)->GetType() == OBJECT_CHARACTER)
				{
					Add_Object((*iter)->GetX(), (*iter)->GetY(), OBJECT_CHAR_EXPLOSION, (*iter)->GetTeam());
					CSoundMgr::Char_Explosion();
				}
				else
				{
					m_bQuake = true;
					Add_Object((*iter)->GetX(), (*iter)->GetY(), OBJECT_BUI_EXPLOSION, (*iter)->GetTeam());
					CSoundMgr::Bui_Explosion();
				}

				int charid = (*iter)->GetID();
				for (VECTORITERATOR biter = iter; biter != m_vGameObjects.end();)
				{
					int bulletid = (*biter)->GetID();
					if (bulletid == charid)
					{
						if ((*biter)->GetType() == OBJECT_BULLET)
						{
							//Add_Object((*biter)->GetX(), (*biter)->GetY(), -(*biter)->GetDx(), -(*biter)->GetDy(), OBJECT_PARTICLE, (*biter)->GetTeam());
						}

						if (biter == iter)
						{
							biter = m_vGameObjects.erase(biter);
							iter = biter;
						}
						else
						{
							biter = m_vGameObjects.erase(biter);
						}
					}
					else
					{
						++biter;
					}
				}
			}
			else
			{
				iter = m_vGameObjects.erase(iter);
			}
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
			int iteam = m_vGameObjects[i]->GetTeam();
			int jteam = m_vGameObjects[j]->GetTeam();
			if ( i != j && iteam != jteam &&
				CollisionRect(m_vGameObjects[i], m_vGameObjects[j]))
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
				else if (itype == OBJECT_BUILDING && jtype == OBJECT_CHARACTER)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
				// 빌딩과 화살간의 충돌
				else if (itype == OBJECT_BUILDING && jtype == OBJECT_ARROW)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
				}
				// 빌딩과 총알간의 충돌
				else if (itype == OBJECT_BUILDING && jtype == OBJECT_BULLET)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
					//Add_Object(m_vGameObjects[j]->GetX(), m_vGameObjects[j]->GetY(), -m_vGameObjects[j]->GetDx(), -m_vGameObjects[j]->GetDy(), OBJECT_PARTICLE, m_vGameObjects[j]->GetTeam());
				}
				// 캐릭터와 총알간의 충돌
				else if (itype == OBJECT_CHARACTER && jtype == OBJECT_BULLET)
				{
					m_vGameObjects[i]->Attacked(m_vGameObjects[j]->Attack());
					//Add_Object(m_vGameObjects[j]->GetX(), m_vGameObjects[j]->GetY(), -m_vGameObjects[j]->GetDx(), -m_vGameObjects[j]->GetDy(), OBJECT_PARTICLE, m_vGameObjects[j]->GetTeam());
				}
				// 캐릭터와 화살간의 충돌
				else if (itype == OBJECT_CHARACTER && jtype == OBJECT_ARROW)
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

	
	for (int i = 0; i < m_vGameObjects.size(); ++i)
	{
		if (m_vGameObjects[i] != NULL)
		{
			int type = m_vGameObjects[i]->GetType();
			if (type == OBJECT_BUILDING)
			{
				g_Renderer->DrawTexturedRectSeq(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GettexID(), m_vGameObjects[i]->m_ncurrSeqx, m_vGameObjects[i]->m_ncurrSeqy,
					m_vGameObjects[i]->m_ntotalSeqx, m_vGameObjects[i]->m_ntotalSeqy, m_vGameObjects[i]->GetLevel());
			}
			else if (type == OBJECT_CHARACTER)
				g_Renderer->DrawTexturedRectSeq(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GettexID(), m_vGameObjects[i]->m_ncurrSeqx, m_vGameObjects[i]->m_ncurrSeqy,
					m_vGameObjects[i]->m_ntotalSeqx, m_vGameObjects[i]->m_ntotalSeqy, m_vGameObjects[i]->GetLevel());
			else if (type == OBJECT_BACKGROUND)
			{
				g_Renderer->DrawTexturedRect(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GettexID(), m_vGameObjects[i]->GetLevel());

				float sAlpha = sin((m_vGameObjects[i]->GetColideTime()) * 2.f);
				g_Renderer->DrawParticleClimate(0.f, 0.f, 0.f, 5.f,
					1.f, 1.f, 1.f, 1.f,
					-0.1f, -0.1f,
					m_nstartexId,
					m_vGameObjects[i]->GetColideTime(), 0.1f);
			}
			else if (type == OBJECT_PARTICLE)
			{
				g_Renderer->DrawParticle(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GetDx(), m_vGameObjects[i]->GetDy(), m_vGameObjects[i]->GettexID(), m_vGameObjects[i]->GetColideTime(),
					m_vGameObjects[i]->GetLevel());
			}
			else if (type == OBJECT_BULLET)
			{
				g_Renderer->DrawSolidRect(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GetLevel());
					
				float pAlpha = sin((m_vGameObjects[i]->GetColideTime()) * 2.f);
				g_Renderer->DrawParticle(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize() * 0.5f, m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), pAlpha,
					-m_vGameObjects[i]->GetDx(), -m_vGameObjects[i]->GetDy(), m_npaticletexId, m_vGameObjects[i]->GetColideTime(),
					m_vGameObjects[i]->GetLevel());
			}
			else if (type == OBJECT_CHAR_EXPLOSION)
			{
				g_Renderer->DrawTexturedRectSeq(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GettexID(), m_vGameObjects[i]->m_ncurrSeqx, m_vGameObjects[i]->m_ncurrSeqy,
					m_vGameObjects[i]->m_ntotalSeqx, m_vGameObjects[i]->m_ntotalSeqy, m_vGameObjects[i]->GetLevel());
			}
			else if (type == OBJECT_BUI_EXPLOSION)
			{
				g_Renderer->DrawTexturedRectSeq(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GettexID(), m_vGameObjects[i]->m_ncurrSeqx, m_vGameObjects[i]->m_ncurrSeqy,
					m_vGameObjects[i]->m_ntotalSeqx, m_vGameObjects[i]->m_ntotalSeqy, m_vGameObjects[i]->GetLevel());
			}
			else
			{
				g_Renderer->DrawSolidRect(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY(), m_vGameObjects[i]->GetZ(),
					m_vGameObjects[i]->GetSize(), m_vGameObjects[i]->GetRed(), m_vGameObjects[i]->GetGreen(), m_vGameObjects[i]->GetBlue(), m_vGameObjects[i]->GetAlpha(),
					m_vGameObjects[i]->GetLevel());
			}
			if (type == OBJECT_BUILDING || type == OBJECT_CHARACTER)
			{
				if (m_vGameObjects[i]->GetTeam() == TEAMBLUE)
					g_Renderer->DrawSolidRectGauge(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY() + (m_vGameObjects[i]->GetSize() * 0.8f), m_vGameObjects[i]->GetZ(),
						m_vGameObjects[i]->GetSize(), 10.f, 0.f, 0.f, 1.f, 1.f, m_vGameObjects[i]->GetLife() / m_vGameObjects[i]->GetMaxLife(),
						m_vGameObjects[i]->GetLevel());
				else
					g_Renderer->DrawSolidRectGauge(m_vGameObjects[i]->GetX(), m_vGameObjects[i]->GetY() + (m_vGameObjects[i]->GetSize() * 0.8f), m_vGameObjects[i]->GetZ(),
						m_vGameObjects[i]->GetSize(), 10.f, 1.f, 0.f, 0.f, 1.f, m_vGameObjects[i]->GetLife() / m_vGameObjects[i]->GetMaxLife(),
						m_vGameObjects[i]->GetLevel());
			}
		}
	}

	string str = "Money : ";
	char money[100];
	ZeroMemory(money, sizeof(money));

	_itoa(m_nMoney, money, 10);
	str += money;
	
	char* text = new char[str.size() + 1];
	ZeroMemory((void*)text, sizeof(text));

	strcpy(text, str.c_str());
	text[str.size()] = '\0';

	g_Renderer->DrawText(145.f, -345.f, GLUT_BITMAP_HELVETICA_18, 1.f, 1.f, 1.f, text);

	delete[] text;
}

int CSceneMgr::Win_Check()
{
	int nRedBuiCnt = 0;
	int nBlueBuiCnt = 0;

	for (int i = 0; i < m_vGameObjects.size(); ++i)
	{
		if (m_vGameObjects[i]->GetType() == OBJECT_BUILDING)
		{
			if (m_vGameObjects[i]->GetTeam() == TEAMRED)
				++nRedBuiCnt;
			else
				++nBlueBuiCnt;
		}
	}

	if (nRedBuiCnt == 0)
		return WIN_BLUE;
	if (nBlueBuiCnt == 0)
		return WIN_RED;
	return WIN_NOT;
}

void CSceneMgr::Add_Object(float x, float y, int type, int team)
{
	if (m_vGameObjects.size() < MAX_ObJECTS_COUNT)
	{
		CGameObject* nRect = new CRect(x, y, type, team);
		((CRect *)nRect)->SetDirection(GetRandomExceptZero(-1.f, 1.f), GetRandomExceptZero(-1.f, 1.f), 0.f);

		nRect->SetId(m_nobjectId++);

		if (type == OBJECT_CHARACTER)
		{
			if (team == TEAMRED)
				nRect->SettexID(m_nredcharspritetexId);
			else if (team == TEAMBLUE)
				nRect->SettexID(m_nbluecharspritetexId);
		}
		else if (type == OBJECT_BUILDING)
		{
			if (team == TEAMRED)
				nRect->SettexID(m_nredbuildingspritetexId);
			else if (team == TEAMBLUE)
				nRect->SettexID(m_nbluebuildingspritetexId);
		}
		else if (type == OBJECT_BACKGROUND)
		{
			nRect->SettexID(m_nbackgroundtexId);
		}
		else if (type == OBJECT_PARTICLE)
		{
			nRect->SettexID(m_npaticletexId);
		}
		else if (type == OBJECT_CHAR_EXPLOSION)
		{
			nRect->SettexID(m_ncharexplosiontexId);
		}
		else if (type == OBJECT_BUI_EXPLOSION)
		{
			nRect->SettexID(m_nbuiexplosiontexId);
		}
		m_vGameObjects.push_back(nRect);
	}
	else
	{
		printf("MAX OBJECT COUNT OVER\n");
	}
}

void CSceneMgr::Add_Object(float x, float y, int type, int id, int team)
{
	if (m_vGameObjects.size() < MAX_ObJECTS_COUNT)
	{
		CGameObject* nRect = new CRect(x, y, type, team);
		((CRect *)nRect)->SetDirection(GetRandomExceptZero(-1.f, 1.f), GetRandomExceptZero(-1.f, 1.f), 0.f);
		nRect->SetId(id);

		m_vGameObjects.push_back(nRect);
	}
	else
	{
		printf("MAX OBJECT COUNT OVER\n");
	}
}

void CSceneMgr::Add_Object(float x, float y, float dx, float dy, int type, int team)
{
	if (m_vGameObjects.size() < MAX_ObJECTS_COUNT)
	{
		CGameObject* nRect = new CRect(x, y, type, team);
		((CRect *)nRect)->SetDirection(dx, dx, 0.f);

		nRect->SetId(m_nobjectId++);

		if (type == OBJECT_CHARACTER)
		{
			if (team == TEAMRED)
				nRect->SettexID(m_nredcharspritetexId);
			else if (team == TEAMBLUE)
				nRect->SettexID(m_nbluecharspritetexId);
		}
		else if (type == OBJECT_BUILDING)
		{
			if (team == TEAMRED)
				nRect->SettexID(m_nredbuildingspritetexId);
			else if (team == TEAMBLUE)
				nRect->SettexID(m_nbluebuildingspritetexId);
		}
		else if (type == OBJECT_BACKGROUND)
		{
			nRect->SettexID(m_nbackgroundtexId);
		}
		else if (type == OBJECT_PARTICLE)
		{
			nRect->SettexID(m_npaticletexId);
		}
		else if (type == OBJECT_CHAR_EXPLOSION)
		{
			nRect->SettexID(m_ncharexplosiontexId);
		}
		m_vGameObjects.push_back(nRect);
	}
	else
	{
		printf("MAX OBJECT COUNT OVER\n");
	}
}