#include <cmath>
#include <sstream>

#include "utility.h"
#include "WorldManager.h"

using std::stringstream;

using namespace utility;

// Return true if positions intersect, else false.
bool utility::positionsIntersect(Vector p1, Vector p2)
{
    if (abs(p1.getX() - p2.getX()) <= 1 && abs(p1.getY() - p2.getY()) <= 1)
    {
        return true;
    }

    return false;
}

bool utility::boxIntersectBox(Box A, Box B)
{
    float Ax1 = A.getCorner().getX();
    float Ax2 = A.getCorner().getX() + A.getHorizontal();
    float Ay1 = A.getCorner().getY();
    float Ay2 = A.getCorner().getY() + A.getVertical();

    float Bx1 = B.getCorner().getX();
    float Bx2 = B.getCorner().getX() + B.getHorizontal();
    float By1 = B.getCorner().getY();
    float By2 = B.getCorner().getY() + B.getVertical();

    // Test horizontal overlap (x_overlap).
    bool x_overlap = false;
    // Either left side of A in B or left side of B in A?
    if ((Bx1 <= Ax1 && Ax1 <= Bx2) || (Ax1 <= Bx1 && Bx1 <= Ax2))
    {
        x_overlap = true;
    }

    // Test vertical overlap (y_overlap).
    bool y_overlap = false;
    // Either left side of A in B or left side of B in A?
    if ((By1 <= Ay1 && Ay1 <= By2) || (Ay1 <= By1 && By1 <= Ay2))
    {
        y_overlap = true;
    }

    if (x_overlap && y_overlap)
    {
        return true;    // Boxes do intersect.
    }
    else
    {
        return false;   // Boxes do not intersect.
    }
}

Box utility::getWorldBox(const Object* p_o)
{
    return getWorldBox(p_o, p_o -> getPosition());
}

Box utility::getWorldBox(const Object* p_o, Vector where)
{
    Box box = p_o -> getBox();
    Vector corner = box.getCorner();

    corner.setX(corner.getX() + where.getX());
    corner.setY(corner.getY() + where.getY());
    box.setCorner(corner);

    return box;
}

Vector utility::worldToView(Vector world_pos)
{
    Vector view_origin = WM.getView().getCorner();
    float view_x = view_origin.getX();
    float view_y = view_origin.getY();

    Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);

    return view_pos;
}

Vector utility::viewToWorld(Vector view_pos)
{
    Vector view_origin = WM.getView().getCorner();
    float view_x = view_origin.getX();
    float view_y = view_origin.getY();

    Vector world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);

    return world_pos;
}

std::string utility::toString(int i)
{
    std::stringstream ss;	// Create stringstream.
    ss << i;	// Add number to stream.
    return ss.str();	// Return string with contents of stream.
}