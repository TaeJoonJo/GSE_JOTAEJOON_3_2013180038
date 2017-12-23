#pragma once

#include "GameObject.h"
#include "Rect.h"
#include "Sound.h"
#include "SoundMgr.h"

class Renderer;

class CSceneMgr
{
protected:
	static Renderer *g_Renderer;
	CSoundMgr *m_pSoundMgr;

	static vector<CGameObject*> m_vGameObjects;

	float m_fRedCharacterTimer;

	float m_fQuakeTimer;

	bool m_bQuake;

	static int m_nobjectId;

	unsigned int m_nbackgroundtexId;

	unsigned int m_nredchartexId;
	unsigned int m_nbluechartexId;

	unsigned int m_nredcharspritetexId;
	unsigned int m_nbluecharspritetexId;

	unsigned int m_nredbuildingtexId;
	unsigned int m_nbluebuildingtexId;

	unsigned int m_nredbuildingspritetexId;
	unsigned int m_nbluebuildingspritetexId;

	unsigned int m_npaticletexId;
	unsigned int m_ncharexplosiontexId;
	unsigned int m_nbuiexplosiontexId;

	unsigned int m_nstartexId;

	float m_fMoneyTimer;

	int m_nMoney;
public:
	CSceneMgr(CSoundMgr* soundmgr);
	~CSceneMgr();
public:
	bool Ready_Renderer();
	bool Ready_Objects();
	void Update_Objects(float time);
	void Draw_Objects();
	int  Win_Check();

	static Renderer* GetRenderer() {
		return g_Renderer;
	}
public:
	inline CGameObject* Get_Object(int index) {
		return (m_vGameObjects[index]);
	}
	
	void Add_Object(float x, float y, int type, int team);
	static void Add_Object(float x, float y, int type, int id, int team);
	void Add_Object(float x, float y, float dx, float dy, int type, int team);
public:
	inline int Get_Money() {
		return m_nMoney;
	};
	inline void Set_Money(int money) {
		m_nMoney = money;
	}
	inline void Earn(int earning) {
		m_nMoney += earning;
	}
	inline bool Pay(int paid) {
		m_nMoney -= paid;

		if (m_nMoney >= 0)
			return true;

		m_nMoney += paid;
		return false;
	}
};
