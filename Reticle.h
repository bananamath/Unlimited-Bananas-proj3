#ifndef __RETICLE_H__
#define __RETICLE_H_

#include "Object.h"
#include "Lure.h"

#define RETICLE_CHAR '+'

namespace df
{
	class Reticle : public df::Object
	{
		private:
			std::string sprite;
			Lure *lure;
			bool can_cast = true;

		public:
			Reticle();
			int draw(void) override;
			int eventHandler(const df::Event *p_e) override;
			void setCast(bool cast);
	};
}
#endif // __RETICLE_H__