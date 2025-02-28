#pragma once

#include "Manager.h"

#define IM df::InputManager::getInstance()

namespace df
{
	class InputManager : public Manager
	{
		private:
			InputManager();	// Provate (a singleton).
			InputManager(InputManager const&);	// Don't allow copy.
			void operator=(InputManager const&);	// Don't allow assignment.

		public:
			// Get the one and only instancce of the InputManager.
			static InputManager &getInstance();

			// Get window ready to capture input.
			// Return 0 if ok, else -1;
			int startUp();

			// Revert back to normal window mode.
			void shutDown();

			// Get input from the keyboard and mouse.
			// Pass event along to all Objects.
			void getInput(bool output = false) const;
	};
}