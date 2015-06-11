#ifndef TARGETCOMPONENT_H_
#define TARGETCOMPONENT_H_

#include "entity/components/SkillComponent.h"

/**
 * Data structure for a target component.
 */
typedef struct
{
	Entity target; ///< The Entity this Entity is targeting
	skill_t skill; ///< The skill this Entity is attacking with
} TargetComponent;

#endif
