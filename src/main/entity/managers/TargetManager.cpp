#include <utility>

#include "entity/managers/TargetManager.h"

const TargetComponent TargetManager::NULL_TARGET = { NULL_ENTITY, Melee };

TargetManager::TargetManager()
{
}

