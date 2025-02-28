#pragma once

#include "Event.h"

namespace df
{
	const std::string STEP_EVENT = "df::step";

	class EventStep : public Event
	{
		private:
			int m_step_count;	// Iteration number of game loop.

		public:
			// Constructor with initial step count.
			// Defaults to 0.
			EventStep(int init_step_count = 0);

			// Set step count.
			void setStepCount(int new_step_count);

			// Get step count.
			int getStepCount() const;
	};
}