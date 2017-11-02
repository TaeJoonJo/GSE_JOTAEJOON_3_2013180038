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
//
//CRect::CRect(float x, float y, float z, float size, float speed, float r, float g, float b, float a)
//	: m_fxmoved(1.f), m_fymoved(1.f), m_fzmoved(0.f),
//	m_fsmoved(1.f)
//{
//	m_fx = x;
//	m_fy = y;
//	m_fz = z;
//
//	m_fsize = size;
//	m_foriginsize = m_fsize;
//
//	m_fspeed = speed;
//
//	m_fred = r;
//	m_fgreen = g;
//	m_fblue = b;
//	m_falpha = a;
//}
//CRect::CRect(float x, float y, float lifetime) 
//	: m_fxmoved(1.f), m_fymoved(1.f), m_fzmoved(0.f),
//	m_fsmoved(1.f)
//{
//	m_fx = x;
//	m_fy = y;
//
//	m_flifetime = lifetime;
//
//	m_fspeed = RECT_SPEED;
//
//	m_fsize = 10.f;
//	m_foriginsize = m_fsize;
//
//	m_fred = (rand() % 10) * 0.1f;
//	m_fgreen = (rand() % 10) * 0.1f;
//	m_fblue = (rand() % 10) * 0.1f;
//	m_falpha = (rand() % 10) * 0.1f;
//}

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
		m_flifetime = 10.f;
		m_fspeed = 300.f;
		m_fsize = 10.f;
		m_fred = 1.f;
		m_fblue = 1.f;
		m_fgreen = 1.f;
		m_falpha = 1.f;
	}
	else if (m_ntype == OBJECT_BUILDING)
	{
		m_flifetime = 500.f;
		m_fspeed = 0.f;
		m_fsize = 50.f;
		m_fred = 1.f;
		m_fblue = 0.f;
		m_fgreen = 1.f;
		m_falpha = 1.f;
	}
	else if (m_ntype == OBJECT_BULLET)
	{
		m_flifetime = 20.f;
		m_fspeed = 300.f;
		m_fsize = 20.f;
		m_fred = 1.f;
		m_fblue = 0.f;
		m_fgreen = 0.f;
		m_falpha = 1.f;
	}
	else if (m_ntype == OBJECT_ARROW)
	{
		m_flifetime = 10.f;
		m_fspeed = 100.f;	
		m_fsize = 20.f;
		m_fred = 0.f;
		m_fblue = 0.f;
		m_fgreen = 0.5f;
		m_falpha = 1.f;
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
	float temptime = time / 1000.f;

	if (((m_fx + (m_fsize * 0.5f)) <= -250.f) || ((m_fx - (m_fsize * 0.5f)) >= 250.f))
		m_fxmoved *= -1.f;
	if ((m_fy + (m_fsize * 0.5f)) <= -250.f || ((m_fy - (m_fsize * 0.5f)) >= 250.f))
		m_fymoved *= -1.f;

	float fhoriginsize = m_foriginsize * 0.5f;
	if (m_foriginsize + fhoriginsize < m_fsize)
		m_fsmoved *= -1.f;
	if(m_foriginsize - fhoriginsize > m_fsize)
		m_fsmoved *= -1.f;

	//m_fsize += 1.f * m_fsmoved * temptime;
	//m_flifetime -= temptime;

	printf("life: %d\n", m_flifetime);

	MovexybySpeed(temptime);
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