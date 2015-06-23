#include "entity/systems/RenderSystem.h"
#include "entity/managers/PositionManager.h"
#include "entity/managers/SpriteManager.h"

RenderSystem::RenderSystem() : _display(NULL), _win(0)
{
}

RenderSystem::RenderSystem(Display* display, Window win) : _display(display)
{
	_win = _display->getWindowParent(win);
}

void RenderSystem::execute(EntityManager& em)
{
	//We can only do anything if we have a Window to do it in
	if(NULL != _display)
	{
		//Let's fetch the ComponentManagers we actually care about
		PositionManager* pm = (PositionManager*)em.getComponentManager(Position);
		SpriteManager* sm = (SpriteManager*)em.getComponentManager(Sprite);

		if(NULL == pm || NULL == sm)
		{
			//Nothing we can do if we don't have these managers
			return;
		}

		//Now let's get the list of Entities we want to work with
		EntityList entities = em.getEntities();
		//In our case, only Entities with a Position...
		entities = pm->filterEntitiesWithComponent(entities);
		//...and a Sprite we can render there
		entities = sm->filterEntitiesWithComponent(entities);

		//Start from a clean/known state
		_display->loadLevel(_win);

		for(EntityList::iterator it = entities.begin(); it != entities.end(); ++it)
		{
			//Get the components for this Entity
			PositionComponent pos = pm->getComponent(*it);
			SpriteComponent sprite = sm->getComponent(*it);

			//Now render the given sprite at the specified position
			//The add method handles boundary checking for us so we don't have to!
			XYPair draw_pos = {pos.x, pos.y};
			_display->add(_win, draw_pos, sprite.c);
		}
	}
}

void RenderSystem::setWindow(Display* display, Window win)
{
	_display = display;
	_win = _display->getWindowParent(win);
}

