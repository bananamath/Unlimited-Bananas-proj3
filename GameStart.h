#pragma once

#include "ViewObject.h"
#include "Music.h"

namespace df
{
	class GameStart : public ViewObject
	{
		private:
			void start();
			Music *p_music;

		public:
			GameStart();
			int eventHandler(const Event *p_e) override;
			int draw() override;
	};
}