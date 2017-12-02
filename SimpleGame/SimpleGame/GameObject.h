#pragma once

class CGameObject
{
protected:
	float m_flifetime;
	float m_flife;
	float m_fmaxlife;

	float m_fx;
	float m_fy;
	float m_fz;
	float m_fsize;

	float m_fdx;
	float m_fdy;
	float m_fdz;

	float m_fspeed;

	// R G B A
	float m_fred;
	float m_fgreen;
	float m_fblue;
	float m_falpha;

	float m_flevel;

	int m_ntype;

	int m_nteam;

	// ½Äº°ÀÚ
	int m_nId;

	unsigned int m_ntexID;

	float m_fseqtimer;
	float m_fcolidetimer;
public:
	int m_ntotalSeqx;
	int m_ntotalSeqy;

	int m_ncurrSeqx;
	int m_ncurrSeqy;

	bool m_isColied;
public:
	CGameObject();
	~CGameObject();
public:
	virtual void Render();
	virtual void Update(float time);

	inline float GetX() {
		return m_fx;
	}
	inline float GetY() {
		return m_fy;
	}
	inline float GetZ() {
		return m_fz;
	}
	inline float GetDx() {
		return m_fdx;
	}
	inline float GetDy() {
		return m_fdy;
	}
	inline float GetDz() {
		return m_fdz;
	}
	inline float GetSize() {
		return m_fsize;
	}
	inline float GetRed() {
		return m_fred;
	}
	inline float GetGreen() {
		return m_fgreen;
	}
	inline float GetBlue() {
		return m_fblue;
	}
	inline float GetAlpha() {
		return m_falpha;
	}
	inline float GetLife() {
		return m_flife;
	}
	inline float GetMaxLife() {
		return m_fmaxlife;
	}
	inline float GetLifetime() {
		return m_flifetime;
	}
	inline int GetType() {
		return m_ntype;
	}
	inline int GetTeam() {
		return m_nteam;
	}
	inline int GetID() {
		return m_nId;
	}
	inline unsigned int GettexID() {
		return m_ntexID;
	}
	inline float GetLevel() {
		return m_flevel;
	}
	inline float GetColideTime() {
		return m_fcolidetimer;
	}

	inline void SetPosition(float x, float y, float z) {
		m_fx = x; m_fy = y; m_fz = z;
	}
	inline void SetColor(float r, float g, float b, float a) {
		m_fred = r; m_fgreen = g; m_fblue = b; m_falpha = a;
	}
	inline void SetLife(float life) {
		m_flife = life;
	}
	inline void SetMaxLife(float maxlife) {
		m_fmaxlife = maxlife;
	}
	inline void SetLifetime(float lifetime) {
		m_flifetime = lifetime;
	}
	inline void SetTeam(int team) {
		m_nteam = team;
	}
	inline void SetId(int id) {
		m_nId = id;
	}
	inline void SettexID(unsigned int texid) {
		m_ntexID = texid;
	}
	inline void SetLevel(float level) {
		m_flevel = level;
	}
	inline void SetSpeed(float speed) {
		m_fspeed = speed;
	}
	inline void SetDirection(float dx, float dy, float dz)
	{
		m_fdx = dx;
		m_fdy = dy;
		m_fdz = dz;
	}
	inline void Attacked(float damage = 0.f) {
		if(m_flife > 0.f) m_flife -= damage;
		m_isColied = true;
	}
	inline float Attack() {
		float temp = m_flife;
		m_flife = 0.f;
		m_isColied = true;
		return temp;
	}
	
public:
	virtual void Release() = 0;
};

class CCooltime
{
public:
	CCooltime();
	~CCooltime();
public:
	bool m_isEnable;
	float m_fCooltime;
};