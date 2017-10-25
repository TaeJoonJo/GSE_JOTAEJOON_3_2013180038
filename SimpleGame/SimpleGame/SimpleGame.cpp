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

Renderer *g_Renderer = NULL;
CSceneMgr* g_Scene = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	/*for(int i = 0; i < MAX_ObJECTS_COUNT; ++i)
	{
		g_Renderer->DrawSolidRect(g_Scene->Get_Object(i));
	}*/

	for (int i = 0; i < MAX_ObJECTS_COUNT; ++i)
	{
		g_Renderer->DrawSolidRect(g_Scene->Get_Object(i));
	}

	glutSwapBuffers();
}

void Idle(void)
{
	g_Scene->Update_Objects();

	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	int RenderScenex = x - 250;
	int RenderSceney = (y - 250) * -1;
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		/*CGameObject* newRect = new CRect(RenderScenex, RenderSceney);
		((CRect*)newRect)->SetDirection(1.f, 1.f, 0.f);
		((CRect*)newRect)->SetSpeed(0.1f);*/
		
	}

	printf("x: %d, y: %d\n", RenderScenex, RenderSceney);
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
	glutInitWindowSize(500, 500);
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
	g_Scene->Ready_Objects();

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Scene;
	delete g_Renderer;

    return 0;
}
