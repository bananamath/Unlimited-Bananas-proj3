#pragma once

#include <string>

#include "Object.h"
#include "Fish.h"

namespace df
{
	class ViewCaught : public Object
	{
		private:
			std::string m_name;
			std::string m_sprite;
			int m_size;				// length in inches
			std::string m_rarity;
			int m_lifetime;

		public:
			// Construct ViewCaught
			ViewCaught(std::string name, std::string sprite, int size, std::string rarity);

			~ViewCaught();

			int eventHandler(const df::Event *p_e) override;

			int draw(void) override;
	};
}