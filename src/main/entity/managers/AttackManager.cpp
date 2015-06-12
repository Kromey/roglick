#include <utility>

#include "entity/managers/AttackManager.h"

const AttackComponent AttackManager::NULL_ATTACK = { NULL_ENTITY, Melee };

AttackManager::AttackManager()
{
}

