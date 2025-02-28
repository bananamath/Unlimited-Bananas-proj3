#include "Event.h"

df::Event::Event()
{
    m_event_type = UNDEFINED_EVENT;
}

df::Event::~Event()
{

}

void df::Event::setType(std::string new_type)
{
    m_event_type = new_type;
}

std::string df::Event::getType() const
{
    return m_event_type;
}