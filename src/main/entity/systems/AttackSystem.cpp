#include "entity/systems/AttackSystem.h"
#include "entity/managers/AttackManager.h"
#include "entity/managers/SkillManager.h"
#include "entity/managers/AttributeManager.h"

AttackSystem::AttackSystem()
{
}

void AttackSystem::execute(EntityManager& em)
{
	//Let's fetch the ComponentManagers we actually care about
	AttackManager* tm = (AttackManager*)em.getComponentManager(Attack);
	SkillManager* sm = (SkillManager*)em.getComponentManager(Skill);
	//We'll only need this after we implement doing damage
	//AttributeManager* am = (AttributeManager*)em.getComponentManager(Attribute);

	//Now let's get the list of Entities we want to work with
	EntityList entities = em.getEntities();
	//In our case, only Entities with an AttackComponent
	entities = tm->filterEntitiesWithComponent(entities);

	for(EntityList::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		//Get the components for this Entity
		AttackComponent target = tm->getComponent(*it);

		//Make the attack
		///@todo Need to be able to supply a message to be displayed
		SkillCheckResult attack = sm->check(*it, target.skill);
		if(attack.successful)
		{
			//The target now gets a chance to defend
			//The attack's DoS is a penalty on this check
			///@todo Choose the best/appropriate defense
			SkillCheckResult defense = sm->check(target.target, Dodge, 0-attack.dos);
			if(!defense.successful)
			{
				//To get here, we had to:
				// a) Succeed on our attack, and
				// b) Watch our target fail their defense
				//This means we hit! Hooray!
				///@todo Deal appropriate damage
				//For now we'll just kill the target outright
				em.destroyEntity(target.target);
			}
		}

		//The attack has been resolved, clean up
		tm->removeComponent(*it);
	}
}

