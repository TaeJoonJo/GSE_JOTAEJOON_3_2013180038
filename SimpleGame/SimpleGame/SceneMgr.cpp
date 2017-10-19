#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr()
{
	
}

CSceneMgr::~CSceneMgr()
{
	delete[] m_GameObjects;
}

void CSceneMgr::Ready_Objects()
{
	srand((unsigned)time(NULL));

	m_GameObjects = new CRect[MAX_ObJECTS_COUNT];

	for (int i = 0; i < MAX_ObJECTS_COUNT; ++i)
	{
		((CRect*)m_GameObjects)[i].SetDirection(1.f, 1.f, 0.f);
		((CRect*)m_GameObjects)[i].SetRandPot();
	}
}

void CSceneMgr::Update_Objects(void)
{
	for (int i = 0; i < MAX_ObJECTS_COUNT; ++i)
		((CRect*)m_GameObjects)[i].Update();
}
