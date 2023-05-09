#pragma once
#include "Mario.h"
#include "Luigi.h"
#include "Enemy.h"
#include "Commons.h"


class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character*, Character*);
	bool Box(Rect2D rect1, Rect2D rect2);

protected:
	Collisions();
	static Collisions* m_instance;
};

