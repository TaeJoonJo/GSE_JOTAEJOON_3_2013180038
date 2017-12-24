/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/
/*
	기본 설명
	생성은 기본 마우스 왼쪽클릭을 이용해 가능합니다.
	키보드 a,s,d를 통해 유닛의 종류를 선택가능합니다.
*/
#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#include "GameObject.h"
#include "Rect.h"

CSceneMgr* g_Scene = NULL;
CSoundMgr* g_SoundMgr = NULL;

bool bStart = false;

DWORD g_prevTime = 0;

int g_Select = OBJECT_CHARACTER;

bool g_isLeft = false;

CCooltime CharCooltime;
CCooltime SupCooltime;
CCooltime BuiCooltime;

void CoolTime(float time);

float fLetterColor = 1.f;
float fLetterDir = 1.f;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	float elapsedTime_per_time = elapsedTime * 0.001f;

	if (bStart)
	{
		CoolTime((float)elapsedTime);

		int whoswin = g_Scene->Win_Check();

		if (whoswin == WIN_NOT)
		{
			g_Scene->Update_Objects((float)elapsedTime);
			g_Scene->Draw_Objects();
		}
		else if (whoswin == WIN_RED)
		{
			if (fLetterColor <= 0.f || fLetterColor >= 1.f)
				fLetterDir *= -1.f;

			fLetterColor += 0.1f * fLetterDir;

			CSceneMgr::GetRenderer()->DrawText(-10.f, 0.f, GLUT_BITMAP_HELVETICA_12, fLetterColor, 0.f, 0.f, "You Lose");
		}
		else if (whoswin == WIN_BLUE)
		{
			if (fLetterColor <= 0.f || fLetterColor >= 1.f)
				fLetterDir *= -1.f;

			fLetterColor += 0.1f * fLetterDir;

			CSceneMgr::GetRenderer()->DrawText(-10.f, 0.f, GLUT_BITMAP_HELVETICA_12, 0.f, 0.f, fLetterColor, "You Win");
		}
	}
	else if (!bStart)
	{
		if (fLetterColor <= 0.f || fLetterColor >= 1.f)
			fLetterDir *= -1.f;

		fLetterColor += 0.1f * fLetterDir;

		CSceneMgr::GetRenderer()->DrawText(-55.f, 0.f, GLUT_BITMAP_HELVETICA_12, fLetterColor, fLetterColor, fLetterColor, "Press SpaceBar To Start");
	}

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	int RenderScenex = x - WINHALFSIZEX;
	int RenderSceney = -(y - WINHALFSIZEY);
	
	//printf("x : %d, y : %d\n", RenderScenex, RenderSceney);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		CSoundMgr::Click();
		if (bStart)
		{
			g_isLeft = true;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (bStart && g_isLeft)
		{
			if (g_Select == OBJECT_CHARACTER)
			{
				if (CharCooltime.m_isEnable)
				{
					if (RenderSceney <= 0.f)
					{
						if (g_Scene->Pay(COST_CHARACTER))
						{
							g_Scene->Add_Object(RenderScenex, RenderSceney, OBJECT_CHARACTER, TEAMBLUE);
							CharCooltime.m_isEnable = false;
							CSoundMgr::Gen();
						}
					}
					else
					{
						printf("Character Only North\n");
					}
				}
				else
				{
					printf("Char CoolTime : %f\n", CharCooltime.m_fCooltime);
					printf("Character is Cooltime!\n");
				}
			}
			else if (g_Select == OBJECT_SUPPLY)
			{
				if (SupCooltime.m_isEnable)
				{
					if (RenderSceney <= 0.f)
					{
						if (g_Scene->Pay(COST_SUPPLY))
						{
							g_Scene->Add_Object(RenderScenex, RenderSceney, OBJECT_SUPPLY, TEAMBLUE);
							SupCooltime.m_isEnable = false;
							CSoundMgr::Gen();
						}
					}
					else
					{
						printf("Supply Only North\n");
					}
				}
				else
				{
					printf("Supply CoolTime : %f\n", SupCooltime.m_fCooltime);
					printf("Supply is Cooltime!\n");
				}
			}
			else if (g_Select == OBJECT_BUILDING)
			{
				if (BuiCooltime.m_isEnable)
				{
					if (RenderSceney <= 0.f)
					{
						if (g_Scene->Pay(COST_BUILDING))
						{
							g_Scene->Add_Object(RenderScenex, RenderSceney, OBJECT_BUILDING, TEAMBLUE);
							BuiCooltime.m_isEnable = false;
							CSoundMgr::Gen();
						}
					}
					else
					{
						printf("Builing Only North\n");
					}
				}
				else
				{
					printf("Builing CoolTime : %f\n", BuiCooltime.m_fCooltime);
					printf("Builing is Cooltime!\n");
				}
			}
			g_isLeft = false;
		}

	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	if (!bStart)
	{
		if (key == SPACEBAR)
		{
			bStart = true;

			CSoundMgr::Select();
		}
	}
	else if (bStart)
	{
		if (key == 'a' || key == 'A')
		{
			CSoundMgr::Select();
			g_Select = OBJECT_CHARACTER;
		}
		else if (key == 's' || key == 'S')
		{
			CSoundMgr::Select();
			g_Select = OBJECT_SUPPLY;
		}
		else if (key == 'd' || key == 'D')
		{
			CSoundMgr::Select();
			g_Select = OBJECT_BUILDING;
		}
	}

	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));

	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINSIZEX, WINSIZEY);
	glutCreateWindow("KPU GSE JoTaeJoon");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	g_SoundMgr = new CSoundMgr();
	g_SoundMgr->Init();

	g_Scene = new CSceneMgr(g_SoundMgr);
	if (!g_Scene->Ready_Renderer())
		std::cout << "렌더러 오류" << std::endl;
	
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Scene;
	delete g_SoundMgr;

    return 0;
}

void CoolTime(float time)
{
	float elapedtime = time * 0.001f;

	if (!CharCooltime.m_isEnable)
	{
		if ((CharCooltime.m_fCooltime += elapedtime) >= COOLTIME_CHAR)
		{
			CharCooltime.m_fCooltime = 0.f;
			CharCooltime.m_isEnable = true;
		}
	}

	if (!SupCooltime.m_isEnable)
	{
		if ((SupCooltime.m_fCooltime += elapedtime) >= COOLTIME_SUP)
		{
			SupCooltime.m_fCooltime = 0.f;
			SupCooltime.m_isEnable = true;
		}
	}

	if (!BuiCooltime.m_isEnable)
	{
		if ((BuiCooltime.m_fCooltime += elapedtime) >= COOLTIME_BUI)
		{
			BuiCooltime.m_fCooltime = 0.f;
			BuiCooltime.m_isEnable = true;
		}
	}
}