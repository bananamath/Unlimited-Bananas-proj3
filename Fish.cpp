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
	m_name = "";
	m_sprite = "";
	m_rarity = "";
	m_size = 0;
	move_cooldown = 0;
	setType("Fish");

	setSprite("shadow");

	setSolidness(SOFT);

	// Switch statement for random fish creation
	int rval = rand() % 100;

	if (rval < 33) {
		//guppy
		setFishName("Guppy");
		setFishSprite("guppy");
		setFishRarity("Common");
		setFishSpeed(20);	// SLOW

		int minLength = 3;
		int maxLength = 10;
		int r = 1 / (rand() % 100);
		int sz = (r * maxLength) + minLength;
		setFishSize(sz);
	}
	else if (rval < 66) {
		//salmon
		setFishName("Ampersalmon");
		setFishSprite("ampersalmon");
		setFishRarity("Common");
		setFishSpeed(10);	// MEDIUM

		int minLength = 6;
		int maxLength = 24;
		int r = 1 / (rand() % 100);
		int sz = (r * maxLength) + minLength;
		setFishSize(sz);
	}
	else if (rval < 83) {
		//eel
		setFishName("Eel");
		setFishSprite("eel");
		setFishRarity("Uncommon");
		setFishSpeed(5);	// FAST

		int minLength = 8;
		int maxLength = 20;
		int r = 1 / (rand() % 100);
		int sz = (r * maxLength) + minLength;
		setFishSize(sz);
	}
	else {
		//boot
		setFishName("Boot");
		setFishSprite("boot");
		setFishRarity("Uncommon");
		setFishSpeed(20);	// SLOW

		int minLength = 8;
		int maxLength = 7;	//dont worry about it (maxLength is a misnomer)
		int r = 1 / (rand() % 100);
		int sz = (r * maxLength) + minLength;
		setFishSize(sz);
	}

	LM.writeLog("Made a fish! It's a %s with length: %d", getFishName().c_str(), getFishSize());

	moveToStart();
}

//Fish::Fish(std::string sprite, std::string name, int size, std::string rarity)
//{
//	setType("Fish");
//
//	setSprite("shadow");
//	setFishSprite(sprite);
//	setFishName(name);
//	setFishSize(size);
//	setFishRarity(rarity);
//
//	setSolidness(SOFT);
//
//	move_cooldown = 0;
//	moveToStart();
//}

Fish::~Fish()
{
	// Send view event?
	// spawn a new Fish
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
		
		// delete current fish
		WM.markForDelete(this);

		// create new fish
		Fish();
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
	temp_pos.setX(-6.0f);

	// y is in vertical range.
	temp_pos.setY((rand() % 4) + 12.0f);

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

// Getters and Setters
std::string Fish::getFishName() const {
	return m_name;
}
void Fish::setFishName(std::string name) {
	m_name = name;
	return;
}

std::string Fish::getFishSprite() const {
	return m_sprite;
}
void Fish::setFishSprite(std::string sprite) {
	m_sprite = sprite;
	return;
}

int Fish::getFishSize() const {
	return m_size;
}
void Fish::setFishSize(int size) {
	m_size = size;
	return;
}

std::string Fish::getFishRarity() const {
	return m_rarity;
}
void Fish::setFishRarity(std::string rarity) {
	m_rarity = rarity;
	return;
}

int Fish::getFishSpeed() const {
	return m_speed;
}
void Fish::setFishSpeed(int speed) {
	m_speed = speed;
	return;
}