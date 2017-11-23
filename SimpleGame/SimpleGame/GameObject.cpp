#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	:
	m_flevel(0.f)
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