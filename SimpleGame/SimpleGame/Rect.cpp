#include "stdafx.h"
#include "Rect.h"


CRect::CRect()
{
	m_fx = 0.f;
	m_fy = 0.f;
}

CRect::CRect(float x, float y, float z, float size, float r, float g, float b, float a)
{
	m_fx = x;
	m_fy = y;
	m_fz = z;
	m_fsize = size;

	m_fred = r;
	m_fgreen = g;
	m_fblue = b;
	m_falpha = a;
}

CRect::~CRect()
{
}

void CRect::Render_GameObject()
{
	
}

void CRect::Update_GameObject()
{

}

void CRect::Release()
{
	delete this;
}