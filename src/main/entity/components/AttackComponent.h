#ifndef ATTACKCOMPONENT_H_
#define ATTACKCOMPONENT_H_

#include "entity/components/SkillComponent.h"

/**
 * Data structure for an attack component.
 */
typedef struct
{
	Entity target; ///< The Entity this Entity is attacking
	skill_t skill; ///< The skill this Entity is attacking with
} AttackComponent;

#endif
