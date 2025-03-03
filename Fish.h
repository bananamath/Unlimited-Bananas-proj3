// __FISH_H__

#ifndef __FISH_H__
#define __FISH_H__

// Engine includes
#include "Object.h"
#include "Sprite.h"
#include "EventCollision.h"

namespace df
{
	class Fish : public Object
	{
	private:
		std::string m_name;
		std::string m_sprite;
		int m_size;				// length in inches
		std::string m_rarity;
		int m_speed;

		int move_cooldown;


	public:
		// Default Fish constructor
		Fish();

		// Fish constructor with parameters given
		/*Fish(std::string sprite, std::string name, int size, std::string rarity);*/

		~Fish();
		int eventHandler(const Event* p_e) override;
		
		void out();
		void hit(const EventCollision* p_collision_event);
		void moveToStart();
		void moveShadow();

		// Getters and Setters
		std::string getFishName() const;
		void setFishName(std::string name);

		std::string getFishSprite() const;
		void setFishSprite(std::string sprite);

		int getFishSize() const;
		void setFishSize(int size);

		std::string getFishRarity() const;
		void setFishRarity(std::string rarity);

		int getFishSpeed() const;
		void setFishSpeed(int speed);
	};
}
#endif // __FISH_H__