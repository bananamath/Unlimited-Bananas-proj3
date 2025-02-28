#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventMouse.h"

#include "Reticle.h"

using namespace df;
using namespace Mouse;

Reticle::Reticle()
{
	setType("Reticle");

	setSolidness(df::Solidness::SPECTRAL);

	setAltitude(MAX_ALTITUDE); // Make Reticle in foreground.

	color = "RED";
}

int Reticle::eventHandler(const Event *p_e)
{
	if (p_e -> getType() == MSE_EVENT)
	{
		const EventMouse *p_mouse_event = dynamic_cast <const EventMouse *> (p_e);
		// Change location to new mouse position.
		setPosition(p_mouse_event -> getMousePosition());
		
		if (p_mouse_event -> getMouseAction() == CLICKED)
		{
			if (p_mouse_event -> getMouseButton() == LEFT)
			{
				color = "MAGENTA";
			}

			if (p_mouse_event -> getMouseButton() == RIGHT)
			{
				color = "RED";
			}
		}

		return 1;
	}

	return 0;
}

// Draw reticle on window.
int Reticle::draw()
{
	if (color == "RED")
	{
		DM.drawCh(getPosition(), RETICLE_CHAR, RED);
	}

	if (color == "MAGENTA")
	{
		DM.drawCh(getPosition(), RETICLE_CHAR, MAGENTA);
	}

	return 0;
}