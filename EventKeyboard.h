#pragma once

#include "Event.h"

namespace df
{
	const std::string KEYBOARD_EVENT = "df::keyboard";

	// Types of keyboard actions Dragonfly recognizes.
	enum EventKeyboardAction
	{
		UNDEFINED_KEYBOARD_ACTION = -1,	// Undefined.
		KEY_PRESSED,	// Was down.
		KEY_RELEASED,	// Was released.
	};

	// Keys Dragonfly recognizes.
	namespace Keyboard
	{
		enum Key
		{
			UNDEFINED_KEY = -1,
			SPACE, RETURN, ESCAPE, TAB, LEFTARROW, RIGHTARROW, UPARROW, DOWNARROW, PAUSE, MINUS, PLUS, TILDE, PERIOD, COMMA, SLASH, LEFTCONTROL, RIGHTCONTROL, LEFTSHIFT, RIGHTSHIFT, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0,
		};
	}

	class EventKeyboard : public Event
	{
		private:
			Keyboard::Key m_key_val;	// Key value.
			EventKeyboardAction m_keyboard_action;	// Key action.

		public:
			EventKeyboard();

			// Set key in event.
			void setKey(Keyboard::Key new_key);

			// Get key from event.
			Keyboard::Key getKey() const;

			// Set keyboard event action.
			void setKeyboardAction(EventKeyboardAction new_action);

			// Get keyboard event action.
			EventKeyboardAction getKeyboardAction() const;
	};
}