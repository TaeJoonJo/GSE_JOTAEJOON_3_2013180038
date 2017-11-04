#include "stdafx.h"
#include "Rect.h"
#include "Function.h"

CRect::CRect()
	: m_fxmoved(1.f), m_fymoved(1.f), m_fzmoved(1.f),
	m_fsmoved(1.f)
{
	m_fx = GetRandom(-250.f, 250.f);
	m_fy = GetRandom(-250.f, 250.f);
	
	m_fspeed = RECT_SPEED;

	m_fsize = 10.f;
	m_foriginsize = m_fsize;

	m_fred = 1.f;
	m_fblue = 1.f;
	m_fgreen = 1.f;

	m_falpha = GetRandom(0.1f, 1.f);
}

CRect::CRect(float x, float y, int type)
	: m_fxmoved(1.f), m_fymoved(1.f), m_fzmoved(0.f),
	m_fsmoved(1.f)
{
	m_fx = x;
	m_fy = y;
	m_fz = 0.f;

	m_ntype = type;

	if (m_ntype == OBJECT_CHARACTER)
	{
		m_flife = 10.f;
		m_fspeed = 300.f;
		m_fsize = 10.f;
		m_fred = 1.f;
		m_fblue = 1.f;
		m_fgreen = 1.f;
		m_falpha = 1.f;
	}
	else if (m_ntype == OBJECT_BUILDING)
	{
		m_flife = 500.f;
		m_fspeed = 0.f;
		m_fsize = 50.f;
		m_fred = 1.f;
		m_fblue = 0.f;
		m_fgreen = 1.f;
		m_falpha = 1.f;
	}
	else if (m_ntype == OBJECT_BULLET)
	{
		m_flife = 20.f;
		m_fspeed = 300.f;
		m_fsize = 5.f;
		m_fred = 1.f;
		m_fblue = 0.f;
		m_fgreen = 0.f;
		m_falpha = 1.f;
	}
	else if (m_ntype == OBJECT_ARROW)
	{
		m_flife = 10.f;
		m_fspeed = 100.f;	
		m_fsize = 5.f;
		m_fred = 0.f;
		m_fblue = 0.f;
		m_fgreen = 0.5f;
		m_falpha = 1.f;
	}

	m_flifetime = 1000.f;

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
	if (m_ntype == OBJECT_CHARACTER && m_isColied)
		SetColor(1.f, 0.f, 0.f, 1.f);
	else if (m_ntype == OBJECT_CHARACTER)
		SetColor(1.f, 1.f, 1.f, 1.f);

	if (((m_fx + (m_fsize * 0.5f)) <= -250.f) || ((m_fx - (m_fsize * 0.5f)) >= 250.f))
		m_fxmoved *= -1.f;
	if ((m_fy + (m_fsize * 0.5f)) <= -250.f || ((m_fy - (m_fsize * 0.5f)) >= 250.f))
		m_fymoved *= -1.f;

	float fhoriginsize = m_foriginsize * 0.5f;
	if (m_foriginsize + fhoriginsize < m_fsize)
		m_fsmoved *= -1.f;
	if(m_foriginsize - fhoriginsize > m_fsize)
		m_fsmoved *= -1.f;

	if(m_ntype == OBJECT_CHARACTER)
		m_fsize += fhoriginsize * 0.1f * m_fsmoved;

	if(m_flifetime > 0.f)
		m_flifetime -= 0.5f;

	//printf("life: %f\n", temptime);
	if (m_ntype == OBJECT_BUILDING)
		printf("life : %f\n", m_flife);

	MovexybySpeed(time);
}

void CRect::MovexybySpeed(float time)
{
	m_fx += m_fspeed * m_fxmoved * time;
	m_fy += m_fspeed * m_fymoved * time;
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