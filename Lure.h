// __LURE_H__

# pragma once

// Engine includes
#include "Object.h"
#include "EventStep.h"
#include "Sound.h"

namespace df
{
	class Lure : public Object
	{
		private:
			float target_y;
			Sound *p_sound;

		public:
			Lure(Vector position, int strength);
			int eventHandler(const df::Event* p_e) override;
			void step();
			int draw(void) override;
	};
}