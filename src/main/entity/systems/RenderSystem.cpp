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
	}
}

void RenderSystem::setWindow(Window* win)
{
	_win = win;
}

