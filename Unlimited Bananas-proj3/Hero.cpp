#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "DisplayManager.h"
#include "EventOut.h"
#include "EventView.h"

#include "Hero.h"

using namespace df;

Hero::Hero()
{
	setType("Hero");

	setPosition(Vector (5,5));

	// Always keep Hero centered in window.
	WM.setViewFollowing(this);

	// Create reticle.
	p_reticle = new Reticle();
	p_reticle -> draw();
}

int Hero::eventHandler(const Event *p_e)
{
	if (p_e -> getType() == KEYBOARD_EVENT)
	{
		const EventKeyboard *p_keyboard_event = dynamic_cast <const EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 0;
	}

	if (p_e -> getType() == OUT_EVENT)
	{
		LM.writeLog("Hero: Out of window");
		return 0;
	}

	return -1;
}

// Take appropriate action according to key pressed.
void Hero::kbd(const EventKeyboard *p_keyboard_event)
{
	switch(p_keyboard_event -> getKey())
	{
		case Keyboard::W: // up
			if (p_keyboard_event -> getKeyboardAction() == KEY_PRESSED)
			{
				WM.moveObject(this, Vector (getPosition().getX(), getPosition().getY()-1));
				EventView ev("Movement", 1, true);
				WM.onEvent(&ev);

				EventView ev1("Wrong target", 0, false);
				WM.onEvent(&ev1);
			}
			break;

		case Keyboard::S: // down
			if (p_keyboard_event -> getKeyboardAction() == KEY_PRESSED)
			{
				WM.moveObject(this, Vector (getPosition().getX(), getPosition().getY()+1));
				EventView ev("Movement", 1, true);
				WM.onEvent(&ev);
			}
			break;

		case Keyboard::A: // left
			if (p_keyboard_event -> getKeyboardAction() == KEY_PRESSED)
			{
				WM.moveObject(this, Vector (getPosition().getX()-2, getPosition().getY()));
				EventView ev("Movement", 1, true);
				WM.onEvent(&ev);
			}
			break;

		case Keyboard::D: // right
			if (p_keyboard_event -> getKeyboardAction() == KEY_PRESSED)
			{
				WM.moveObject(this, Vector (getPosition().getX()+2, getPosition().getY()));
				EventView ev("Movement", 1, true);
				WM.onEvent(&ev);
			}
			break;
	}

	return;
}

// Draw hero on window.
int Hero::draw()
{
	return DM.drawString(getPosition(), "Hero", df::CENTER_JUSTIFIED, BLUE);
}