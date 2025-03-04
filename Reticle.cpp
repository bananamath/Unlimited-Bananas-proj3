#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventMouse.h"
#include "LogManager.h"

#include "Reticle.h"

using namespace df;
using namespace Mouse;

Reticle::Reticle()
{
	setType("Reticle");

	setSolidness(Solidness::SPECTRAL);

	setAltitude(MAX_ALTITUDE); // Make Reticle in foreground.

	setPosition(Vector(40,20));

	sprite = "reticle";
	setSprite("castbar");
	
	lure = NULL;
}

int Reticle::eventHandler(const Event *p_e)
{
	if (p_e -> getType() == MSE_EVENT)
	{
		const EventMouse *p_mouse_event = dynamic_cast <const EventMouse *> (p_e);
		// Change location to new mouse position.
		Vector m_position = p_mouse_event -> getMousePosition();

		if (sprite == "reticle")
		{
			// If we want fixed vertical position
			setPosition(Vector(m_position.getX(), 22));


			/*setPosition(Vector(m_position.getX(), getPosition().getY()));

			if (m_position.getY() > 18)
			{
				setPosition(Vector(getPosition().getX(), m_position.getY()));
			}*/
		}
		
		if (p_mouse_event -> getMouseAction() == CLICKED)
		{
			// If there is no lure, cast one. Otherwise, delete the lure.
			if (lure == NULL)
			{
				// If the player tries to cast, make the Reticle display the castbar.
				if (sprite == "reticle")
				{
					sprite = "castbar";
					getAnimation().setIndex(0);
				}
				// If the player casts, remove the castbar and create a Lure with varying strength.
				else if (sprite == "castbar")
				{
					sprite = "reticle";
					// Strength of cast depends when in the sprite animation the player clicked.
					int strength = getAnimation().getIndex();
					// Adjust strength if the cast bar is on a decreasing frame.
					if (strength > 4)
					{
						strength = 8-strength;
					}
					LM.writeLog("Cast strength: %d", strength);

					lure = new Lure(getPosition(), strength);
				}
			}
			else
			{
				WM.markForDelete(lure);
				lure = NULL;
			}
		}

		return 1;
	}

	return 0;
}

// Draw reticle on window.
int Reticle::draw()
{
	// Draws either the normal Reticle or the castbar sprite depending on the current player action.
	if (sprite == "reticle")
	{
		DM.drawCh(getPosition(), RETICLE_CHAR, RED);
	}
	else if (sprite == "castbar")
	{
		getAnimation().draw(Vector(getPosition().getX(), getPosition().getY()-2));
	}

	return 0;
}