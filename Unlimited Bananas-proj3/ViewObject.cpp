#include "ViewObject.h"
#include "WorldManager.h"
#include "utility.h"
#include "DisplayManager.h"
#include "EventView.h"

using namespace df;

ViewObject::ViewObject()
{
    // Initialize Object attributes.
    setType("ViewObject");

    setSolidness(SPECTRAL);
    setAltitude(MAX_ALTITUDE);

    // Initialize ViewObject attributes.
    setValue(0);
    setDrawValue();
    setBorder(true);
    setLocation(TOP_CENTER);
    setColor(COLOR_DEFAULT);
}

int ViewObject::draw()
{
    // Display view_string + value.
    std::string temp_str = "";
    if (m_border == true)
    {
        temp_str = " " + getViewString() + " " + utility::toString(m_value) + " ";
    }
    else
    {
        temp_str = getViewString() + " " + utility::toString(m_value);
    }

    // Draw centered at position.
    Vector pos = utility::viewToWorld(getPosition());
    DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColor());

    if (m_border == true)
    {
        // Draw box around display.
        Box box(pos, temp_str.length(), 1);
    }

    return 0;
}

int ViewObject::eventHandler(const Event* p_e)
{
    // See if this is 'view' event.
    if (p_e -> getType() == VIEW_EVENT)
    {
        const EventView *p_ve = dynamic_cast <const EventView *> (p_e);

        // See if this event is meant for this object.
        if (p_ve -> getTag() == getViewString())
        {
            if (p_ve -> getDelta())
            {
                setValue(getValue() + p_ve -> getValue());   // Change in value.
            }
            else
            {
                setValue(p_ve -> getValue());   // New value.
            }
            
            return 0;
        }
    }

    return -1;
}

void ViewObject::setLocation(ViewObjectLocation new_location)
{
    Vector position;
    int y_delta = 0;
    bool valid_location = true;

    // Set new position based on location.
    switch (new_location)
    {
        case TOP_LEFT:
            position.setXY(WM.getView().getHorizontal() * 1/6, 1);
            if (getBorder() == false)
            {
                y_delta = -1;
            }
            break;

        case TOP_CENTER:
            position.setXY(WM.getView().getHorizontal() * 3/6, 1);
            if (getBorder() == false)
            {
                y_delta = -1;
            }
            break;

        case TOP_RIGHT:
            position.setXY(WM.getView().getHorizontal() * 5/6, 1);
            if (getBorder() == false)
            {
                y_delta = -1;
            }
            break;

        case CENTER_LEFT:
            position.setXY(WM.getView().getHorizontal() * 1/6, WM.getView().getVertical()/2);
            break;

        case CENTER_CENTER:
            position.setXY(WM.getView().getHorizontal() * 3/6, WM.getView().getVertical()/2);
            break;

        case CENTER_RIGHT:
            position.setXY(WM.getView().getHorizontal() * 5/6, WM.getView().getVertical()/2);
            break;

        case BOTTOM_LEFT:
            position.setXY(WM.getView().getHorizontal() * 1/6, WM.getView().getVertical()-1);
            if (getBorder() == false)
            {
                y_delta = 1;
            }
            break;

        case BOTTOM_CENTER:
            position.setXY(WM.getView().getHorizontal() * 3/6, WM.getView().getVertical()-1);
            if (getBorder() == false)
            {
                y_delta = 1;
            }
            break;

        case BOTTOM_RIGHT:
            position.setXY(WM.getView().getHorizontal() * 5/6, WM.getView().getVertical()-1);
            if (getBorder() == false)
            {
                y_delta = 1;
            }
            break;

        default:
            valid_location = false;
            break;
    }

    if (valid_location == true)
    {
        // Shift, as needed, based on border.
        position.setY(position.getY() + y_delta);

        // Set position of object to new position.
        setPosition(position);

        // Set new location.
        m_location = new_location;
    }
}

ViewObjectLocation ViewObject::getLocation() const
{
    return m_location;
}

void ViewObject::setValue(int new_value)
{
    m_value = new_value;
}

int ViewObject::getValue() const
{
    return m_value;
}

void ViewObject::setBorder(bool new_border)
{
    if (m_border != new_border)
    {
        m_border = new_border;

        // Reset location to account for border setting.
        setLocation(getLocation());
    }
}

bool ViewObject::getBorder() const
{
    return m_border;
}

void ViewObject::setColor(Color new_color)
{
    m_color = new_color;
}

Color ViewObject::getColor() const
{
    return m_color;
}

void ViewObject::setViewString(std::string new_view_string)
{
    view_string = new_view_string;
}

std::string ViewObject::getViewString() const
{
    return view_string;
}

void ViewObject::setDrawValue(bool new_draw_value)
{
    m_draw_value = new_draw_value;
}

bool ViewObject::getDrawValue() const
{
    return m_draw_value;
}