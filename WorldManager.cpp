#include "WorldManager.h"
#include "LogManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "DisplayManager.h"
#include "EventOut.h"

using namespace df;

WorldManager::WorldManager()
{
    setType("WorldManager");
}

WorldManager& WorldManager::getInstance()
{
    static WorldManager single;
    return single;
}

int WorldManager::startUp()
{
    Manager::startUp();

    return 0;
}

void WorldManager::shutDown()
{
    // Delete all game objects.
    ObjectList list = m_updates;  // Copy list so can delete during iteration.
    for (int i=0; i<list.getCount(); i++)
    {
        delete list[i];
    }

    Manager::shutDown();
}

int WorldManager::insertObject(Object* p_o)
{
    if (m_updates.insert(p_o) == 0)
    {
        LM.writeLog("WorldManager: Inserted object.");
        return 0;
    }

    return -1;
}

int WorldManager::removeObject(Object* p_o)
{
    if (m_updates.remove(p_o) == 0)
    {
        LM.writeLog("WorldManager: Removed object.");
        return 0;
    }

    return -1;
}

ObjectList WorldManager::getAllObjects() const
{
    return m_updates;
}

ObjectList WorldManager::objectsOfType(std::string type)
{
    ObjectList list;
    for (int i=0; i<m_updates.getCount(); i++)
    {
        if (m_updates[i] -> getType() == type)
        {
            list.insert(m_updates[i]);
        }
    }

    return list;
}

void WorldManager::update()
{
    // Update Object positions based on their velocities.
    for (int i=0; i<m_updates.getCount(); i++)
    {
        // Add velocity to position.
        Vector new_pos = m_updates[i] -> predictPosition();

        // If Object should change position, then move.
        if (new_pos.getX() != m_updates[i] -> getPosition().getX() || new_pos.getY() != m_updates[i] -> getPosition().getY())
        {
            moveObject(m_updates[i], new_pos);
        }
    }

    // Delete all marked Objects.
    for (int i=0; i<m_deletions.getCount(); i++)
    {
        LM.writeLog("WorldManager: Deleted object.");
        delete m_deletions[i];
    }

    // Clear list for next update phase.
    m_deletions.clear();
}

int WorldManager::markForDelete(Object* p_o)
{
    // Object might have already been marked, so only add once.
    for (int i=0; i<m_deletions.getCount(); i++)
    {
        if (m_deletions[i] == p_o)  // Object already in list.
        {
            return 0;   // This is still ok.
        }
    }

    // Object not in list, so add.
    m_deletions.insert(p_o);
    LM.writeLog("WorldManager: Marked object for deletion.");
    return 0;
}

void WorldManager::draw()
{
    for (int alt=0; alt<=MAX_ALTITUDE; alt++)
    {
        for (int i=0; i<m_updates.getCount(); i++)
        {
            if (m_updates[i] -> getAltitude() == alt)
            {
                // Bounding box coordinates are relative to Object, so convert to world coordinates.
                Box temp_box = utility::getWorldBox(m_updates[i]);

                // Only draw if Object would be visible on window (intersects view).
                if (utility::boxIntersectBox(temp_box, view))
                {
                    m_updates[i] -> draw();
                }
            }
        }
    }
}

ObjectList WorldManager::getCollisions(const Object* p_o, Vector where)
{
    // Make empty list.
    ObjectList collision_list;

    for (int i=0; i<m_updates.getCount(); i++)
    {
        Object *p_temp_o = m_updates[i];

        if (p_temp_o != p_o)    // Do not consider self.
        {
            // World position bounding box for object at where.
            Box b = utility::getWorldBox(p_o, where);
            
            // World position bounding box for other object
            Box b_temp = utility::getWorldBox(p_temp_o);

            // Same location and both solid?
            if (p_temp_o -> isSolid() && utility::boxIntersectBox(b, b_temp))
            {
                collision_list.insert(p_temp_o);
                LM.writeLog("WorldManager: Found colliding object of type %s", p_temp_o -> getType().c_str());
            }
        }
    }

    return collision_list;
}

int WorldManager::moveObject(Object* p_o, Vector where)
{
    if (p_o -> isSolid()) // Need to be solid for collisions.
    {
        // Get collisions.
        ObjectList list = getCollisions(p_o, where);
        
        if (!list.isEmpty())
        {
            bool do_move = true; // Assume can move.

            for (int i=0; i<list.getCount(); i++)
            {
                Object *p_temp_o = list[i];

                // Create collision event.
                EventCollision c(p_o, p_temp_o, where);

                // Send to both objects.
                p_o -> eventHandler(&c);
                p_temp_o -> eventHandler(&c);

                // If both HARD, then cannot move.
                if (p_o -> getSolidness() == HARD && p_temp_o -> getSolidness() == HARD)
                {
                    do_move = false;    // Can't move.
                }
            }

            if (!do_move)
            {
                LM.writeLog("WorldManager: Move cancelled for object %s", p_o -> getType().c_str());
                return -1;  // Move not allowed.
            }
        }
    }

    Vector temp = p_o -> getPosition();

    // If here, no collision between two HARD objects so allow move.
    p_o -> setPosition(where);

    // Only sends out of bounds event if Object moves outside, not if it stays outside.
    if (temp.getX() >= 0 && temp.getX() <= boundary.getHorizontal() && temp.getY() >= 0 && temp.getY() <= boundary.getVertical())
    {
        // If Object out of bounds, generate out of bounds event and send to Object.
        if (p_o -> getPosition().getX() < 0 || p_o -> getPosition().getX() > boundary.getHorizontal() || p_o -> getPosition().getY() < 0 || p_o -> getPosition().getY() > boundary.getVertical())
        {
            EventOut ov;
            p_o -> eventHandler(&ov);
        }
    }

    // If view is following this object, adjust view.
    if (p_view_following == p_o)
    {
        setViewPosition(p_o -> getPosition());
    }

    return 0;
}

void WorldManager::setBoundary(Box new_boundary)
{
    boundary = new_boundary;
}

Box WorldManager::getBoundary() const
{
    return boundary;
}

void WorldManager::setView(Box new_view)
{
    view = new_view;
}

Box WorldManager::getView() const
{
    return view;
}

void WorldManager::setViewPosition(Vector view_pos)
{
    // Make sure horizontal not out of world boundary.
    float x = view_pos.getX() - view.getHorizontal()/2;
    if (x + view.getHorizontal() > boundary.getHorizontal())
    {
        x = boundary.getHorizontal() - view.getHorizontal();
    }
    if (x < 0)
    {
        x = 0;
    }

    // Make sure vertical not out of world boundary.
    float y = view_pos.getY() - view.getVertical()/2;
    if (y + view.getVertical() > boundary.getVertical())
    {
        y = boundary.getVertical() - view.getVertical();
    }
    if (y < 0)
    {
        y = 0;
    }

    // Set view.
    Vector new_corner(x,y);
    view.setCorner(new_corner);
}

int WorldManager::setViewFollowing(Object* p_new_view_following)
{
    // Set to NULL to turn 'off' following.
    if (p_new_view_following == NULL)
    {
        p_view_following = NULL;
        return 0;
    }

    bool found = false;
    // Iterate over all Objects. Make sure p_new_view_following is one of the Objects, then set found to true.
    for (int i=0; i<m_updates.getCount(); i++)
    {
        if (m_updates[i] == p_new_view_following)
        {
            found = true;
        }
    }

    // If found, adjust attribute accordingly and set view position.
    if (found == true)
    {
        p_view_following = p_new_view_following;
        setViewPosition(p_view_following -> getPosition());
        return 0;
    }

    // If we get here, was not legit. Don't change current view.
    return -1;
}