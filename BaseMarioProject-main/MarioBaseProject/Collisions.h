#pragma once
#include "Mario.h"
#include "Luigi.h"
#include "Commons.h"


class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Mario* character1, Luigi* character2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();
	static Collisions* m_instance;
};

