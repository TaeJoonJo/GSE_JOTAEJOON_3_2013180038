#include "stdafx.h"
#include "Rect.h"
#include "Function.h"
//#include "SceneMgr.h"

CRect::CRect()
	:
	m_fsmoved(1.f)
{
	m_fx = GetRandom(-250.f, 250.f);
	m_fy = GetRandom(-250.f, 250.f);
	
	m_fsize = 10.f;
	m_foriginsize = m_fsize;

	m_fred = 1.f;
	m_fblue = 1.f;
	m_fgreen = 1.f;

	m_falpha = GetRandom(0.1f, 1.f);
}

CRect::CRect(float x, float y, int type, int team)
	:
	m_fsmoved(1.f)
{
	m_fx = x;
	m_fy = y;
	m_fz = 0.f;

	m_ntype = type;

	m_nteam = team;

	m_nId = 0;
	m_ntexID = 0;

	m_fcolidetimer = 0.f;
	m_isColied = false;

	m_fshoottimer = 0.f;

	m_ncurrSeqx = 0;
	m_ncurrSeqy = 0;

	if (m_ntype == OBJECT_CHARACTER)
	{
		m_flife = 100.f;
		m_fmaxlife = m_flife;
		m_fspeed = 300.f;
		m_fsize = 30.f;
		m_flevel = 0.2f;
		if (m_nteam == TEAMRED)
			SetColor(1.f, 1.f, 1.f, 1.f);
		else if (m_nteam == TEAMBLUE)
			SetColor(1.f, 1.f, 1.f, 1.f);
		m_flifetime = 100.f;
		m_ntotalSeqx = 5;
		m_ntotalSeqy = 4;
		//m_ntexID = CSceneMgr::GetRenderer()->CreatePngTexture("../Resource/Planet.png");
	}
	else if (m_ntype == OBJECT_BUILDING)
	{
		m_flife = 500.f;
		m_fmaxlife = m_flife;
		m_fspeed = 0.f;
		m_fsize = 100.f;
		m_flevel = 0.1f;
		SetColor(1.f, 1.f, 1.f, 1.f);
		m_ntotalSeqx = 5;
		m_ntotalSeqy = 4;
		m_flifetime = 100.f;
		//m_ntexID = CSceneMgr::GetRenderer()->CreatePngTexture("../Resource/Moon.png");
	}
	else if (m_ntype == OBJECT_BULLET)
	{
		m_flife = 15.f;
		m_fmaxlife = m_flife;
		m_fspeed = 100.f;
		m_fsize = 5.f;
		m_flevel = 0.3f;
		if (m_nteam == TEAMRED)
			SetColor(1.f, 0.f, 0.f, 1.f);
		else if (m_nteam == TEAMBLUE)
			SetColor(0.f, 0.f, 1.f, 1.f);
		m_flifetime = 100.f;
	}
	else if (m_ntype == OBJECT_ARROW)
	{
		m_flife = 10.f;
		m_fmaxlife = m_flife;
		m_fspeed = 100.f;	
		m_fsize = 4.f;
		m_flevel = 0.3f;
		if (m_nteam == TEAMRED)
			SetColor(0.5f, 0.2f, 0.7f, 1.f);
		else if (m_nteam == TEAMBLUE)
			SetColor(1.f, 1.f, 0.f, 1.f);
		m_flifetime = 100.f;
	}
	else if (m_ntype == OBJECT_BACKGROUND)
	{
		m_flife = 100000.f;
		m_fmaxlife = m_flife;
		m_fspeed = 0.f;
		m_fsize = 700.f;
		m_flevel = 0.99f;
		SetColor(1.f, 1.f, 1.f, 1.f);
		m_flifetime = 100000.f;
	}
	else if (m_ntype == OBJECT_PARTICLE)
	{
		m_flife = 15.f;
		m_fmaxlife = m_flife;
		m_fspeed = 50.f;
		m_fsize = 4.f;
		m_flevel = 0.3f;
		if (m_nteam == TEAMRED)
			SetColor(1.f, 0.f, 0.f, 1.f);
		else if (m_nteam == TEAMBLUE)
			SetColor(0.f, 0.f, 1.f, 1.f);
		m_flifetime = 1.f;
	}

	m_foriginsize = m_fsize;
}

CRect::~CRect()
{
}

void CRect::Render()
{
	
}

void CRect::Update(float time)
{
	if (m_ntype == OBJECT_CHARACTER)
	{
		if (((m_fx - (m_fsize * 0.5f)) <= -WINHALFSIZEX) || ((m_fx + (m_fsize * 0.5f)) >= WINHALFSIZEX))
			m_fdx *= -1.f;
		if ((m_fy - (m_fsize * 0.5f)) <= -WINHALFSIZEY || ((m_fy + (m_fsize * 0.5f)) >= WINHALFSIZEY))
			m_fdy *= -1.f;
		/*if (m_isColied)
		{
			if ((m_fcolidetimer += time) > 0.3f)
			{
				SetColor(1.f, 1.f, 1.f, 1.f);
				m_isColied = false;
				m_fcolidetimer = 0.f;
			}
			else
				SetColor(1.0f, 0.f, 1.f, 1.f);
		}*/
		if ((m_fshoottimer += time) > SHOOTTIMER_CHAR)
		{
			CSceneMgr::Add_Object(m_fx, m_fy, OBJECT_ARROW, m_nId, m_nteam);
			m_fshoottimer = 0.f;
			CSoundMgr::Bow();
		}
		if ((m_fseqtimer += time) > 0.1f)
		{

			if (m_ncurrSeqx < m_ntotalSeqx - 2)
			{
				++m_ncurrSeqx;
			}
			else
			{
				if (m_ncurrSeqy < m_ntotalSeqy - 1)
					++m_ncurrSeqy;
				else
					m_ncurrSeqy = 0;
				m_ncurrSeqx = 0;
			}
			m_fseqtimer = 0.f;
		}
	}
	else if (m_ntype == OBJECT_BUILDING)
	{
		if (m_isColied)
		{
			if ((m_fcolidetimer += time) > 1.f)
			{
				SetColor(1.f, 1.f, 1.f, 1.f);
				m_isColied = false;
				m_fcolidetimer = 0.f;
			}
			else
				SetColor(1.f, 0.f, 0.4f, 1.f);
		}
		if ((m_fshoottimer += time) > SHOOTTIMER_BUILDING)
		{
			CSceneMgr::Add_Object(m_fx, m_fy, OBJECT_BULLET, m_nId, m_nteam);
			m_fshoottimer = 0.f;
			CSoundMgr::Shoot();
		}
		if ((m_fseqtimer += time) > 0.1f)
		{

			if (m_ncurrSeqx < m_ntotalSeqx - 2)
			{
				++m_ncurrSeqx;
			}
			else
			{
				if (m_ncurrSeqy < m_ntotalSeqy - 1)
					++m_ncurrSeqy;
				else
					m_ncurrSeqy = 0;
				m_ncurrSeqx = 0;
			}
			m_fseqtimer = 0.f;
		}
	}
	else if (m_ntype == OBJECT_PARTICLE || m_ntype == OBJECT_BULLET || m_ntype == OBJECT_BACKGROUND)
	{
		m_fcolidetimer += time;
	}
	/*if (m_ntype == OBJECT_CHARACTER)
	{
		float fhoriginsize = m_foriginsize * 0.5f;
		if (m_foriginsize + fhoriginsize < m_fsize)
			m_fsmoved *= -1.f;
		if (m_foriginsize - fhoriginsize > m_fsize)
			m_fsmoved *= -1.f;

		m_fsize += fhoriginsize * m_fsmoved * time;
	}*/

	if(m_flifetime > 0.f)
		m_flifetime -= 0.5f * time;

	MovexybySpeed(time);
}

void CRect::MovexybySpeed(float time)
{
	m_fx += m_fspeed * m_fdx * time;
	m_fy += m_fspeed * m_fdy * time;
}

void CRect::MovebyMouse(int x, int y)
{
	m_fx = (float)x;
	m_fy = (float)y;
}

void CRect::Release()
{
	delete this;
}