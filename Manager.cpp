#include "Manager.h"
#include "ObjectList.h"
#include "WorldManager.h"
#include "LogManager.h"

using namespace df;

Manager::Manager()
{
	m_type = "Manager";
	is_started = false;
}

Manager::~Manager()
{

}

void Manager::setType(std::string type)
{
	m_type = type;
}

std::string Manager::getType() const
{
	return m_type;
}

int Manager::startUp()
{
	LM.writeLog("%s started", getType().c_str());
	is_started = true;
	return 0;
}

void Manager::shutDown()
{
	LM.writeLog("%s shutdown", getType().c_str());
	is_started = false;
}

bool Manager::isStarted() const
{
	if (is_started)
	{
		return true;
	}

	return false;
}

int Manager::onEvent(const Event* p_event) const
{
	int count = 0;

	ObjectList list = WM.getAllObjects();
	for (int i=0; i<list.getCount(); i++)
	{
		list[i] -> eventHandler(p_event);
		count++;
	}

	return count;
}