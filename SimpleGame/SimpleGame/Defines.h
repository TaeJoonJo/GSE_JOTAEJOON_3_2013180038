#pragma once

#define WINSIZEX 500.f
#define WINSIZEY 700.f

#define WINHALFSIZEX WINSIZEX * 0.5f
#define WINHALFSIZEY WINSIZEY * 0.5f

#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 1
#define OBJECT_BULLET 10
#define OBJECT_ARROW 11

#define MAX_ObJECTS_COUNT 1000

#define TEAMBLUE 2	// 아군
#define TEAMRED 1	// 적군

#define VECTORITERATOR std::vector<CGameObject*>::iterator