#include "LogManager.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "EventOut.h"

#include "Saucer.h"

Saucer::Saucer()
{
	setType("Saucer");

	setSprite("saucer");
}

int Saucer::eventHandler(const df::Event *p_e)
{
	// Handles step event.
	if (p_e -> getType() == df::STEP_EVENT)
	{
		const df::EventStep *p_step_event = dynamic_cast <const df::EventStep *> (p_e);

		if (p_step_event -> getStepCount() == 100)
		{
			//WM.markForDelete(this);
			getAnimation().setSlowdownCount(-1);
		}
		else if (p_step_event -> getStepCount() == 200)
		{
			//WM.markForDelete(this);
			getAnimation().setSlowdownCount(0);
			getAnimation().getSprite() -> setSlowdown(10);
		}

		step();
		return 0;
	}

	// Handles collision event.
	if (p_e -> getType() == df::COLLISION_EVENT)
	{
		LM.writeLog("Saucer: Collided with object");
		return 0;
	}

	// Handles out event.
	if (p_e -> getType() == df::OUT_EVENT)
	{
		LM.writeLog("Saucer: Out of window");
		return 0;
	}

	return -1;
}

void Saucer::step()
{
	//LM.writeLog("Saucer: Handled step event.");
}

//int Saucer::draw()
//{
//	return DM.drawString(getPosition(), "Saucer", df::LEFT_JUSTIFIED, df::RED);
//}