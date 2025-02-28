#pragma once

#include "Object.h"
 
class Saucer : public df::Object
{
	private:
		void step();

	public:
		Saucer();
		int eventHandler(const df::Event *p_e) override;
		//int draw();
};
