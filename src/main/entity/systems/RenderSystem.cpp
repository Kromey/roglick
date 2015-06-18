#include "entity/systems/RenderSystem.h"
#include "entity/managers/PositionManager.h"
#include "entity/managers/SpriteManager.h"

RenderSystem::RenderSystem() : _iface(NULL), _win(0)
{
}

RenderSystem::RenderSystem(Interface* iface, Window win) : _iface(iface), _win(win)
{
}

void RenderSystem::execute(EntityManager& em)
{
	//We can only do anything if we have a Window to do it in
	if(NULL != _iface)
	{
		//Let's fetch the ComponentManagers we actually care about
		PositionManager* pm = (PositionManager*)em.getComponentManager(Position);
		SpriteManager* sm = (SpriteManager*)em.getComponentManager(Sprite);

		//Now let's get the list of Entities we want to work with
		EntityList entities = em.getEntities();
		//In our case, only Entities with a Position...
		entities = pm->filterEntitiesWithComponent(entities);
		//...and a Sprite we can render there
		entities = sm->filterEntitiesWithComponent(entities);

		//Start from a clean/known state
		_iface->loadLevel(_win);

		for(EntityList::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			//Get the components for this Entity
			PositionComponent pos = pm->getComponent(*it);
			SpriteComponent sprite = sm->getComponent(*it);

			//Now render the given sprite at the specified position
			//The add method handles boundary checking for us so we don't have to!
			XYPair draw_pos = {pos.x, pos.y};
			_iface->add(_win, draw_pos, sprite.c);
		}
	}
}

void RenderSystem::setWindow(Interface* iface, Window win)
{
	_iface = iface;
	_win = win;
}

