#include "Object.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"

using namespace df;


Object::Object()
{
    m_type = "Object";

    m_altitude = MAX_ALTITUDE/2;
    m_solidness = HARD;

    WM.insertObject(this);

    m_id = id;
    id++;
}

Object::~Object()
{
    WM.removeObject(this);
}

void Object::setId(int new_id)
{
    m_id = new_id;
}

int Object::getId() const
{
    return m_id;
}

void Object::setType(std::string new_type)
{
    m_type = new_type;
}

std::string Object::getType() const
{
    return m_type;
}

void Object::setPosition(Vector new_pos)
{
    m_position.setXY(new_pos.getX(), new_pos.getY());
}

Vector Object::getPosition() const
{
    return m_position;
}

int Object::eventHandler(const Event* p_e)
{
    return 0;
}

int Object::setAltitude(int new_altitude)
{
    if (new_altitude >= 0 && new_altitude <= MAX_ALTITUDE)
    {
        m_altitude = new_altitude;
    }

    return 0;
}

int Object::getAltitude() const
{
    return m_altitude;
}

void Object::setSpeed(float speed)
{
    m_speed = speed;
}

float Object::getSpeed() const
{
    return m_speed;
}

void Object::setDirection(Vector new_direction)
{
    m_direction = new_direction;
}

Vector Object::getDirection() const
{
    return m_direction;
}

void Object::setVelocity(Vector new_velocity)
{
    m_speed = new_velocity.getMagnitude();
    new_velocity.normalize();
    m_direction = new_velocity;
}

Vector Object::getVelocity() const
{
    Vector velocity = m_direction;
    velocity.scale(m_speed);
    return velocity;
}

Vector Object::predictPosition()
{
    // Add velocity to position.
    Vector new_pos = m_position + getVelocity();

    // Return new position.
    return new_pos;
}

bool Object::isSolid() const
{
    if (m_solidness == HARD || m_solidness == SOFT)
    {
        return true;
    }

    return false;
}

int Object::setSolidness(Solidness new_solid)
{
    if (new_solid == HARD)
    {
        m_solidness = HARD;
        return 0;
    }
    else if (new_solid == SOFT)
    {
        m_solidness = SOFT;
        return 0;
    }
    else if (new_solid == SPECTRAL)
    {
        m_solidness = SPECTRAL;
        return 0;
    }

    return -1;
}

Solidness Object::getSolidness() const
{
    return m_solidness;
}

int Object::setSprite(std::string sprite_label)
{
    Sprite *p_sprite = RM.getSprite(sprite_label);
    if (p_sprite == NULL)
    {
        LM.writeLog("Object: Failed to set sprite, could not find '%s'.", sprite_label.c_str());
        return -1;
    }

    m_animation.setSprite(p_sprite);
    setBox(m_animation.getBox());

    return 0;
}

void Object::setAnimation(const Animation& new_animation)
{
    m_animation = new_animation;
}

Animation& Object::getAnimation()
{
    return m_animation;
}

int Object::draw()
{
    return m_animation.draw(m_position);
}

void Object::setBox(Box new_box)
{
    m_box = new_box;
}

Box Object::getBox() const
{
    return m_box;
}