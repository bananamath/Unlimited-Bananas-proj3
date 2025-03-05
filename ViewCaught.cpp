// Game includes
#include "ViewCaught.h"
#include "Fish.h"
#include "Reticle.h"

// Engine includes
#include "WorldManager.h"
#include "ViewObject.h"
#include "utility.h"
#include "DisplayManager.h"
#include "EventStep.h"
#include "ObjectList.h"

using namespace df;

ViewCaught::ViewCaught(std::string name, std::string sprite, int size, std::string rarity)
{
    // Initialize Object attributes.
    setType("ViewCaught");
    setSolidness(SPECTRAL);
    setAltitude(MAX_ALTITUDE);
    setPosition(Vector(40,12));

    // Initialize ViewCaught attributes.
    m_name = name;
    setSprite(sprite);
    m_size = size;
    m_rarity = rarity;
    m_lifetime = 90;

    Reticle* reticle = dynamic_cast <Reticle*> (WM.objectsOfType("Reticle")[0]);
    reticle -> setCast(false);
}

ViewCaught::~ViewCaught()
{
    Reticle* reticle = dynamic_cast <Reticle*> (WM.objectsOfType("Reticle")[0]);
    reticle -> setCast(true);
}

int ViewCaught::eventHandler(const df::Event* p_e)
{
    if (p_e -> getType() == STEP_EVENT)
    {
        // Only lasts for 3 seconds.
        m_lifetime--;

        if (m_lifetime == 0)
        {
            WM.markForDelete(this);
        }

        return 1;
    }

    return 0;
}

// Draw fish and associated information.
int ViewCaught::draw()
{
    getAnimation().draw(getPosition());

    std::string grammar = "a ";

    if (m_name == "Ampersalmon" || m_name == "Eel")
    {
        grammar = "an ";
    }

    std::string temp_str = "Caught " + grammar + m_name + " (" + m_rarity + ") of length " + utility::toString(m_size) + " inches!";
    DM.drawString(Vector(40,18), temp_str,CENTER_JUSTIFIED, MAGENTA);

    return 0;
}