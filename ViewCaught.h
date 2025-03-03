#pragma once

#include <string>

#include "ViewObject.h"
#include "Fish.h"

namespace df
{
	class ViewCaught : public ViewObject
	{
	private:
		Fish m_fish;

	public:
		// Construct ViewCaught
		ViewCaught();

		// Draw view string and value.
		virtual int draw();

		// Set Fish data
		void setFishData(Fish fish);

		// Get Fish data
		Fish getFishData() const;
	};
}