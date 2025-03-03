// Game includes
#include "ViewCaught.h"
#include "Fish.h"

// Engine includes
#include "WorldManager.h"
#include "ViewObject.h"
#include "utility.h"

using namespace df;

ViewCaught::ViewCaught()
{
    // Initialize Object attributes.
    setType("ViewCaught");

    // Initialize ViewObject attributes.
    //setFishData();
}

int ViewCaught::draw()
{

    //draw a black rectangle for background

    //// Display view_string + value.
    //std::string temp_str = "";
    //if (m_border == true)
    //{
    //    temp_str = " " + getViewString() + " " + utility::toString(m_value) + " ";
    //}
    //else
    //{
    //    temp_str = getViewString() + " " + utility::toString(m_value);
    //}

    //// Draw centered at position.
    //Vector pos = utility::viewToWorld(getPosition());
    //DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

    //if (m_border == true)
    //{
    //    // Draw box around display.
    //    Box box(pos, temp_str.length(), 1);
    //}

    return 0;
}

// Set Fish data
void ViewCaught::setFishData(Fish fish) {
    m_fish = fish;
    return;
}

// Get Fish data
Fish ViewCaught::getFishData() const {
    return m_fish;
}