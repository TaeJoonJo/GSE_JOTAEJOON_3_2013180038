#pragma once

#include "stdafx.h"

class CRect;

inline float RandDir() {
	int x = rand();

	if (x % 2 == 0)
		return 1.0f;
	return -1.f;
}

template <class Rect>
bool CollisionRect(Rect* a, Rect* b)
{
	float ax = ((CRect *)a)->GetX();
	float ay = ((CRect *)a)->GetY();
	float as = ((CRect *)a)->GetSize();
	float ahs = as / 2.f;

	float bx = ((CRect *)b)->GetX();
	float by = ((CRect *)b)->GetY();
	float bs = ((CRect *)b)->GetSize();
	float bhs = bs / 2.f;

	if (ax - ahs <= bx + bhs &&
		ay + ahs >= by - bhs &&
		ax + ahs >= bx - bhs &&
		ay - ahs <= by + bhs)
		return true;

	return false;
}

inline float GetRandom(float min, float max)
{
	std::random_device rd;
	std::mt19937 rEngine(rd());
	std::uniform_real_distribution<> dist(min, max);

	return static_cast<float>(dist(rEngine));
}

inline float GetRandomExceptZero(float min, float max)
{
	std::random_device rd;
	std::mt19937 rEngine(rd());
	std::uniform_real_distribution<> dist(min, max);

	float temp = 0.f;
	while (temp == 0.f)
		temp = dist(rEngine);

	return static_cast<float>(temp);
}