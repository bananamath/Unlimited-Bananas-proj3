#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"

#define WM df::WorldManager::getInstance()

namespace df
{
	const int MAX_ALTITUDE = 4;

	class WorldManager : public Manager
	{
		private:
			WorldManager();	// Private (a singleton).
			WorldManager(WorldManager const&);	// Don't allow copy.
			void operator=(WorldManager const&);	// Don't allow assignment.
			ObjectList m_updates;	// All Objects in world to update.
			ObjectList m_deletions;	// All Objects in world to delete.
			Box boundary;	// World boundary.
			Box view;	// Player view of game world.
			Object *p_view_following;	// Object view is following.

		public:
			// Get the one and only instance of the WorldManager.
			static WorldManager &getInstance();

			// Startup game world (initialize everything to empty).
			// Return 0.
			int startUp();

			// Shutdown game world (delete all game world Objects).
			void shutDown();

			// Insert Object into world. Return 0 if ok, else -1.
			int insertObject(Object *p_o);

			// Remove object from world. Return 0 if ok, else -1.
			int removeObject(Object *p_o);

			// Return list of all Objects in world.
			ObjectList getAllObjects() const;

			// Return list of all Objects in world matching type.
			// List is empty if none found.
			ObjectList objectsOfType(std::string type);

			// Update world.
			// Delete Objects marked for deletion.
			void update();

			// Indicate Object is to be deleted at end of current game loop.
			// Return 0 if ok, else -1.
			int markForDelete(Object *p_o);

			// Draw all Objects.
			void draw();

			// Return list of Objects collided with at position 'where'.
			// Collisions only with solid Objects.
			// Does not consider if p_o is solid or not.
			ObjectList getCollisions(const Object *p_o, Vector where);

			// Move Object.
			// If collision with solid, send collision events.
			// If no collision with solid, move ok else don't move Object.
			// If Object is Spectral, move ok.
			// Return 0 if move ok, else -1 if collision with solid.
			int moveObject(Object *p_o, Vector where);

			// Set game world boundary.
			void setBoundary(Box new_boundary);
			
			// Get game world boundary.
			Box getBoundary() const;

			// Set player view of game world.
			void setView(Box new_view);

			// Get player view of game world.
			Box getView() const;

			// Set view to center window on position view_pos.
			// View edge will not go beyond world boundary.
			void setViewPosition(Vector view_pos);

			// Set view to center window on Object.
			// Set to NULL to stop following.
			// If p_new_view_following not legit, return -1 else return 0.
			int setViewFollowing(Object *p_new_view_following);
	};
}
#endif //__WORLD_MANAGER_H__