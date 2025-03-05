#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventKeyboard.h"

#include "GameStart.h"
#include "Reticle.h"
#include "Fish.h"

using namespace df;

GameStart::GameStart()
{
	setSprite("gamestart");

	setType("GameStart");

	// Put in center of window.
	setLocation(CENTER_CENTER);

	// Play start music.
	p_music = RM.getMusic("music");
}

int GameStart::eventHandler(const Event *p_e)
{
	if (p_e -> getType() == KEYBOARD_EVENT)
	{
		EventKeyboard *p_keyboard_event = (EventKeyboard *) p_e;
		switch (p_keyboard_event -> getKey())
		{
			case Keyboard::P:	// play
				start();
				break;

			case Keyboard::Q:	// quit
				GM.setGameOver();
				break;
		}
		return 1;
	}

	return 0;
}

void GameStart::start()
{
	Object* background = new Object();
	background -> setSolidness(SPECTRAL);
	background -> setAltitude(0);
	background -> setSprite("background");
	background -> setPosition(Vector(40,12));

	new Reticle();
	new Fish(true);
	new Fish(true);
	new Fish(true);

	// Play background music.
	p_music -> play();

	WM.markForDelete(this);
}

// Override default draw so as not to display "value".
int GameStart::draw()
{
	return Object::draw();
}