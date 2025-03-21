#include "Box.h"

using namespace df;

Box::Box()
{
    m_corner = Vector();
    m_horizontal = 0;
    m_vertical = 0;
}

Box::Box(Vector init_corner, float init_horizontal, float init_vertical)
{
    m_corner = init_corner;
    m_horizontal = init_horizontal;
    m_vertical = init_vertical;
}

void Box::setCorner(Vector new_corner)
{
    m_corner = new_corner;
}

Vector Box::getCorner() const
{
    return m_corner;
}

void Box::setHorizontal(float new_horizontal)
{
    m_horizontal = new_horizontal;
}

float Box::getHorizontal() const
{
    return m_horizontal;
}

void Box::setVertical(float new_vertical)
{
    m_vertical = new_vertical;
}

float Box::getVertical() const
{
    return m_vertical;
}