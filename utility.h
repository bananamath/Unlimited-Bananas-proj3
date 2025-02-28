#pragma once

#include "Vector.h"
#include "Box.h"
#include "Object.h"

using namespace df;

namespace utility
{
	// Return true if two positions intersect, else false.
	bool positionsIntersect(Vector p1, Vector p2);

	// Return true if boxes intersect, else false.
	bool boxIntersectBox(Box A, Box B);

	// Convert relative bounding Box for Object to absolute world Box.
	Box getWorldBox(const Object *p_o);

	// Convert relative bounding Box for Object to absolute world Box.
	Box getWorldBox(const Object *p_o, Vector where);

	// Convert world position to view position.
	Vector worldToView(Vector world_pos);

	// Convert view position to world position.
	Vector viewToWorld(Vector view_pos);

	// Convert int to a string, returning string.
	std::string toString(int i);
}