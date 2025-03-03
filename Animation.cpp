#include "Animation.h"
#include "LogManager.h"

using namespace df;

Animation::Animation()
{
    m_name = "";
    m_index = 0;
    m_slowdown_count = 0;
}

void Animation::setSprite(Sprite* p_new_sprite)
{
    m_p_sprite = p_new_sprite;
}

Sprite* Animation::getSprite() const
{
    return m_p_sprite;
}

void Animation::setName(std::string new_name)
{
    m_name = new_name;
}

std::string Animation::getName() const
{
    return m_name;
}

void Animation::setIndex(int new_index)
{
    m_index = new_index;
}

int Animation::getIndex() const
{
    return m_index;
}

void Animation::setSlowdownCount(int new_slowdown_count)
{
    m_slowdown_count = new_slowdown_count;
}

int Animation::getSlowdownCount() const
{
    return m_slowdown_count;
}

int Animation::draw(Vector position)
{
    // If sprite not defined, don't continue further.
    if (m_p_sprite == NULL)
    {
        return -1;
    }

    // Ask Sprite to draw current frame.
    int index = m_index;
    m_p_sprite -> draw(index, position);

    // If slowdown count is -1, then animation is frozen.
    if (m_slowdown_count == -1)
    {
        return 0;
    }

    // Increment counter.
    int count = m_slowdown_count;
    count++;

    // Advance sprite index, if appropriate.
    if (count >= getSprite() -> getSlowdown())
    {
        count = 0;  // Reset counter

        index++;  // Advance frame.

        // If at last frame, loop to beginning.
        if (index >= m_p_sprite -> getFrameCount())
        {
            index = 0;
        }

        // Set index for next draw().
        m_index = index;
    }

    // Set counter for next draw().
    m_slowdown_count = count;

    return 0;
}

Box Animation::getBox() const
{
    // If no Sprite, return unit Box cenetered at (0,0).
    if (m_p_sprite == NULL)
    {
        Box box(Vector(-0.5f,-0.5f), 1, 1);
        return box;
    }

    Vector corner(-1 * m_p_sprite -> getWidth()/2.0f, -1 * m_p_sprite -> getHeight()/2.0f);
    Box box(corner, m_p_sprite -> getWidth(), m_p_sprite -> getHeight());

    return box;
}