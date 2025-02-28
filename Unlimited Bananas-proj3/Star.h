#pragma once

#include "Object.h"
#include "Event.h"

#define STAR_CHAR '.'

class Star : public df::Object
{
	public:
		Star();
		int eventHandler(const df::Event *p_e) override;
		int draw(void) override;
};