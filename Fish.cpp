// Engine includes
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "Vector.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes
#include "Fish.h"

using namespace df;

Fish::Fish()
{
	setSprite("guppy");

	setType("Fish");

	moveToStart();
}

Fish::~Fish()
{
	// Send view event?
}

// Handle event.
// Return 0 if ignored, else 1.
int Fish::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
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
void Fish::hit(const df::EventCollision* p_collision_event)
{
	// If Fish on Fish, ignore.
	if ((p_collision_event->getObject1()->getType() == "Fish") &&
		(p_collision_event->getObject2()->getType() == "Fish"))
		return;

	// If lure, create catch opportunity
	if ((p_collision_event->getObject1()->getType() == "Lure") &&
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
	temp_pos.setX(-3.0f);

	// y is in vertical range.
	temp_pos.setY(18.0f);
	//temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

	// If collision, move left slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
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

	return;
}