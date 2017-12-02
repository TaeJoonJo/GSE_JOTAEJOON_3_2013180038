#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_fdx(1.f), m_fdy(1.f), m_fdz(0.f),
	m_flevel(0.f),
	m_ntotalSeqx(0), m_ntotalSeqy(0),
	m_ncurrSeqx(0), m_ncurrSeqy(0),
	m_fcolidetimer(0.f), m_fseqtimer(0.f)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Render()
{

}

void CGameObject::Update(float time)
{

}

CCooltime::CCooltime()
	:m_fCooltime(0.f),
	m_isEnable(true)
{

}

CCooltime::~CCooltime()
{

}