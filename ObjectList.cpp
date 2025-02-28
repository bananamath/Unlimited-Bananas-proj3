#include <stdexcept>

#include "ObjectList.h"
#include "LogManager.h"

using namespace df;

ObjectList::ObjectList()
{
    m_count = 0;
}

int ObjectList::insert(Object* p_o)
{
    // Inserts into the list if it is not full.
    if (isFull())
    {
        return -1;
    }

    m_p_obj[m_count] = p_o;
    m_count++;

    return 0;
}

int ObjectList::remove(Object* p_o)
{
    // If the specified object is in the list, removes it and shifts every pointer after it backwards.
    for (int i=0; i<m_count; i++)
    {
        if (m_p_obj[i] == p_o)
        {
            for (int j=i; j<m_count-1; j++)
            {
                m_p_obj[j] = m_p_obj[j+1];
            }

            m_count--;
            return 0;
        }
    }

    return -1;
}

void ObjectList::clear()
{
    m_count = 0;
}

int ObjectList::getCount() const
{
    return m_count;
}

bool ObjectList::isEmpty() const
{
    return m_count == 0;
}

bool ObjectList::isFull() const
{
    return m_count == 1000;
}

Object*& ObjectList::operator[](int index)
{
    if (index >= m_count || index < 0)
    {
        throw std::out_of_range("Index out of range.");
    }

    return m_p_obj[index];
}
