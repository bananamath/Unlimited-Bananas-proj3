#include "Lure.h"
#include "DisplayManager.h"
#include "LogManager.h"

using namespace df;

Lure::Lure(Vector position, int strength)
{
	setType("Lure");

	// Spectral until it lands in the water, then changes to soft to collide with fish.
	setSolidness(SPECTRAL);

	setAltitude(1);

	setSprite("lure");

	setPosition(position);
    target_y = position.getY() - strength*2;
	LM.writeLog("Lure target y: %f", target_y);
}

int Lure::eventHandler(const Event* p_e)
{
	if (p_e -> getType() == STEP_EVENT) {
		step();
		return 1;
	}

    return 0;
}

void Lure::step()
{
	if (getPosition().getY() >= target_y)
	{
		setPosition(Vector(getPosition().getX(), getPosition().getY()-1));
	}
	else if (getSolidness() == SPECTRAL)
	{
		setSolidness(SOFT);
	}
}

int Lure::draw(void)
{
	if (getPosition().getY() >= target_y)
	{
		DM.drawCh(getPosition(), '|', BLUE);
	}
	else
	{
		getAnimation().draw(getPosition());
	}

	return 0;
}
