// Engine includes
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "Vector.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"

// Game includes
#include "Fish.h"

using namespace df;

Fish::Fish()
{
	setSprite("shadow");

	setType("Fish");

	setSolidness(SOFT);

	move_cooldown = 0;
	moveToStart();
}

Fish::~Fish()
{
	// Send view event?
}

// Handle event.
// Return 0 if ignored, else 1.
int Fish::eventHandler(const Event* p_e)
{
	if (p_e->getType() == OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == COLLISION_EVENT) {
		const EventCollision* p_collision_event = dynamic_cast <EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	if (p_e -> getType() == STEP_EVENT)
	{
		moveShadow();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// If moved off right edge, move back to far left
void Fish::out()
{
	// If haven't moved off left edge, then nothing to do
	if (getPosition().getX() < WM.getBoundary().getHorizontal())
		return;

	// Otherwise, move back to far left
	moveToStart();
}

// Called when Fish shadow collides
void Fish::hit(const EventCollision* p_collision_event)
{
	// If Fish on Fish, ignore.
	if ((p_collision_event->getObject1()->getType() == "Fish") &&
		(p_collision_event->getObject2()->getType() == "Fish"))
		return;

	// If lure, create catch opportunity
	if ((p_collision_event->getObject1()->getType() == "Lure") ||
		(p_collision_event->getObject2()->getType() == "Lure")) {

		// TODO: catch opportunity
		LM.writeLog("Fish::hit() - There's a bite!");
	}
	
	return;
}

// On spawn or Fish left window without being caught,
// move to starting location to the left of the window
void Fish::moveToStart()
{
	Vector temp_pos;

	// Get world boundaries.
	int world_horiz = (int)WM.getBoundary().getHorizontal();
	int world_vert = (int)WM.getBoundary().getVertical();

	// x is off left side of window.
	temp_pos.setX(-4.0f);

	// y is in vertical range.
	//temp_pos.setY(14.0f);
	temp_pos.setY((rand() % 4) + 14.0f);

	// If collision, move left slightly until empty space.
	ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (collision_list.getCount() != 0) {
		temp_pos.setX(temp_pos.getX() - 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);

	return;
}

// Move Fish shadow in the water
void Fish::moveShadow()
{
	if (move_cooldown == 0)
	{
		move_cooldown = 10;

		int random_dir = rand() % 4;
		switch (random_dir)
		{
			case 0:
				setVelocity(Vector(4,0));
				break;

			case 1:
				setVelocity(Vector(0,0));
				break;

			case 2:
				setVelocity(Vector(2,1));
				break;

			case 3:
				setVelocity(Vector(2,-1));
				break;
		}
	}
	else
	{
		move_cooldown--;
		setVelocity(Vector(0,0));
	}
}