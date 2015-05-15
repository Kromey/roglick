#include "entity/systems/RenderSystem.h"
#include "entity/components/PositionManager.h"
#include "entity/components/SpriteManager.h"

RenderSystem::RenderSystem() : _win(NULL)
{
}

RenderSystem::RenderSystem(Window* win) : _win(win)
{
}

void RenderSystem::execute(EntityManager& em)
{
	//We can only do anything if we have a Window to do it in
	if(NULL != _win)
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

		for(EntityListIt it = entities.begin(); it != entities.end(); ++it)
		{
			//Get the components for this Entity
			PositionComponent pos = pm->getPosition(*it);
			SpriteComponent sprite = sm->getComponent(*it);

			//Now render the given sprite at the specified position
			//The add method handles boundary checking for us so we don't have to!
			_win->add(pos.x, pos.y, sprite.c);
		}
	}
}

void RenderSystem::setWindow(Window* win)
{
	_win = win;
}

