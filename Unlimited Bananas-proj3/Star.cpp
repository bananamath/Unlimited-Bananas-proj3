#include <stdlib.h>

#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "LogManager.h"
#include "EventOut.h"

#include "Star.h"

Star::Star()
{
	setType("Star");
	setSolidness(df::Solidness::SPECTRAL);

	setAltitude(0);
}

int Star::eventHandler(const df::Event* p_e)
{
	// Handles step event.
	if (p_e -> getType() == df::STEP_EVENT)
	{
		const df::EventStep *p_step_event = dynamic_cast <const df::EventStep *> (p_e);

		if (p_step_event -> getStepCount() % 30 == 0)
		{
			setAltitude(getAltitude()+1);
		}

		LM.writeLog("Position: %f, %f", getPosition().getX(), getPosition().getY());

		return 0;
	}

	// Handles out event.
	if (p_e -> getType() == df::OUT_EVENT)
	{
		LM.writeLog("Star: Out of window, so deleting");
		WM.markForDelete(this);
		return 0;
	}

	return -1;
}

int Star::draw()
{
	return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}