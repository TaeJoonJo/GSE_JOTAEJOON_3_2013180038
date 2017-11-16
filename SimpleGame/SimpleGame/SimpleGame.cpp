/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "SceneMgr.h"

#include "GameObject.h"
#include "Rect.h"

CSceneMgr* g_Scene = NULL;

DWORD g_prevTime = 0;

bool isLeft = false;

bool isEnableChar = true;
float g_fCharCooltime = 0.f;

void CoolTime(float time);

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	CoolTime((float)elapsedTime);

	g_Scene->Update_Objects((float)elapsedTime);
	g_Scene->Draw_Objects();

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
		isLeft = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (isLeft)
		{
			if (isEnableChar)
			{
				if (RenderSceney <= 0.f)
				{
					g_Scene->Add_Object(RenderScenex, RenderSceney, OBJECT_CHARACTER, TEAMBLUE);
					isEnableChar = false;
				}
				else
				{
					printf("Character Only North\n");
				}
			}
			else
			{
				printf("Character is Cooltime!\n");
			}
		}

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		g_Scene->Add_Object(RenderScenex, RenderSceney, OBJECT_CHARACTER, TEAMRED);
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
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
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	g_Scene = new CSceneMgr;
	if (!g_Scene->Ready_Renderer())
		std::cout << "������ ����" << std::endl;

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Scene;

    return 0;
}

void CoolTime(float time)
{
	float elapedtime = time * 0.001f;

	if (!isEnableChar)
	{
		//printf("Char CoolTime : %d\n", g_fCharCooltime);
		if ((g_fCharCooltime += elapedtime) >= 7.f)
		{
			g_fCharCooltime = 0.f;
			isEnableChar = true;
		}
	}
}