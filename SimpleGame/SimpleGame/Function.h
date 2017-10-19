#pragma once

template <class Object>
bool CollisionRect(Object* a, Object* b)
{
	ax = a->GetX();
	ay = a->GetY();
	as = a->GetSize();
	ahs = as / 2.f;

	bx = b->GetX();
	by = b->GetY();
	bs = b->GetSize();
	bhs = bs / 2.f;
	if (ax - ahs > bx + bhs)
		return false;
	if (ay + ahs > by - bhs)
		return false;
	if (ax + ahs < bx - bhs)
		return false;
	if (ay - ahs < by + bhs)
		return false;

	return true;
}
