// __FISH_H__

# pragma once

// Engine includes
#include "Object.h"

class Fish : public df::Object
{
private:
	std::string m_name;
	//size range
	//sprite - i think we need derived objects of this derived object
	// there's prob several decent ways we could implement different Fish types
	//name
	//speed and/or movement pattern
	//rarity

public:
	Fish();
	~Fish();
	int eventHandler(const df::Event* p_e) override;
	
	void out();
	void hit(const df::EventCollision* p_collision_event);
	void moveToStart();
	void moveShadow();
};