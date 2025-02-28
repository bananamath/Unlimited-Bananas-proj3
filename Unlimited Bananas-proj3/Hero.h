#pragma once

#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include "Reticle.h"

class Hero : public df::Object
{
	private:
		void kbd(const df::EventKeyboard *p_keyboard_event);
		
		Reticle *p_reticle;

	public:
		Hero();
		int eventHandler(const df::Event *p_e) override;
		int draw(void) override;
};