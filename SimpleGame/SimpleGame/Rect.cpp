#include "stdafx.h"
#include "Rect.h"


CRect::CRect()
	: m_fxmoved(0.f), m_fymoved(0.f), m_fzmoved(0.f)
{
	m_fx = (rand() % 500) - 250.f;
	m_fy = (rand() % 500) - 250.f;
	//m_fspeed = (((rand() % 5) / 10.f) + 0.1f);
	m_fspeed = 0.1f;

	//m_fsize = (rand() % 50 + 100.f);
	
	m_fsize = 10.f;

	m_fred = 1.f;
	m_fblue = 1.f;
	m_fgreen = 1.f;

	/*m_fred = (rand() % 10) * 0.1f;
	m_fgreen = (rand() % 10) * 0.1f;
	m_fblue = (rand() % 10) * 0.1f;*/

	m_falpha = (rand() % 10) * 0.1f;
}

CRect::CRect(float x, float y, float z, float size, float speed, float r, float g, float b, float a)
	: m_fxmoved(0.f), m_fymoved(0.f), m_fzmoved(0.f)
{
	m_fx = x;
	m_fy = y;
	m_fz = z;
	m_fsize = size;

	m_fspeed = speed;

	m_fred = r;
	m_fgreen = g;
	m_fblue = b;
	m_falpha = a;
}
CRect::CRect(float x, float y) 
{
	m_fx = x;
	m_fy = y;
	m_fspeed = 0.1f;

	m_fsize = (rand() % 50 + 100.f);

	m_fred = (rand() % 10) * 0.1f;
	m_fgreen = (rand() % 10) * 0.1f;
	m_fblue = (rand() % 10) * 0.1f;
	m_falpha = (rand() % 10) * 0.1f;
}

CRect::~CRect()
{
}

void CRect::Render()
{
	
}

void CRect::Update()
{
	if (((m_fx + (m_fsize * 0.5f)) < -250.f) || ((m_fx - (m_fsize * 0.5f)) > 250.f))
		m_fxmoved *= -1.f;
	if ((m_fy + (m_fsize * 0.5f)) < -250.f || ((m_fy - (m_fsize * 0.5f)) > 250.f))
		m_fymoved *= -1.f;

	MovexybySpeed();
}

void CRect::MovexybySpeed()
{
	m_fx += m_fspeed * m_fxmoved;
	m_fy += m_fspeed * m_fymoved;
}

void CRect::MovebyMouse(int x, int y)
{
	m_fx = x;
	m_fy = y;
}

void CRect::Release()
{
	delete this;
}