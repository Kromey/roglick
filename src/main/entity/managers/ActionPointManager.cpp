#include "entity/managers/ActionPointManager.h"

const ActionPointComponent ActionPointManager::NULL_ACTIONPOINT = 0;

ActionPointManager::ActionPointManager()
{
}

EntityList ActionPointManager::filterActionableEntities(const EntityList& el)
{
	//Container for our filtered list
	EntityList filtered;

	//Work through the list of Entities we were given
	for(EntityList::iterator it = el.begin(); it != el.end(); ++it)
	{
		//Check if this Entity has positive ActionPoints...
		if(0 < getComponent(*it))
		{
			//...and add it to our filtered list if it does
			filtered.insert(*it);
		}
	}

	//Return our filtered list of Entities
	return filtered;
}

