#pragma once

#define WINSIZEX 500.f
#define WINSIZEY 700.f

#define WINHALFSIZEX WINSIZEX * 0.5f
#define WINHALFSIZEY WINSIZEY * 0.5f

#define SPACEBAR 32

#define OBJECT_BACKGROUND -1
#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 1
#define OBJECT_BULLET 10
#define OBJECT_ARROW 11
#define OBJECT_PARTICLE 12
#define OBJECT_CHAR_EXPLOSION 13
#define OBJECT_BUI_EXPLOSION 14

#define COST_CHARACTER 20
#define COST_BUILDING  100

#define MAX_ObJECTS_COUNT 1000

#define COOLTIME_CHAR 1.f
#define COOLTIME_BUI  10.f

#define SHOOTTIMER_BUILDING 5.f
#define SHOOTTIMER_CHAR 3.f

#define REGENTIMER_RED 3.f

#define TIMER_PARTICLE 4.f
#define TIMER_QUAKE    0.5f
#define TIMER_MONEY	   1.f

#define EARNING		   5

#define TEAMBLUE 2	// 아군
#define TEAMRED 1	// 적군
#define TEAMNOT 3	// 중립

#define WIN_BLUE 2
#define WIN_RED  1
#define WIN_NOT  0

#define VECTORITERATOR std::vector<CGameObject*>::iterator