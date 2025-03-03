// __FISH_H__

# pragma once

// Engine includes
#include "Object.h"
#include "EventCollision.h"

namespace df
{
	class Fish : public Object
	{
	private:
		std::string m_name;
		//size range
		//sprite - i think we need derived objects of this derived object
		// there's prob several decent ways we could implement different Fish types
		//name
		//speed and/or movement pattern
		//rarity
		int move_cooldown;

	public:
		Fish();
		~Fish();
		int eventHandler(const Event* p_e) override;
		
		void out();
		void hit(const EventCollision* p_collision_event);
		void moveToStart();
		void moveShadow();
	};
}