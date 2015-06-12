/**
 * @file ecs.h
 *
 * This is simply a convenience header that lets us include the entirety of our
 * ECS framework and implementation with a single include directive.
 */
#include "entity/Entity.h"
#include "entity/EntityManager.h"
#include "entity/components/SkillComponent.h"
#include "entity/components/PositionComponent.h"
#include "entity/components/AttackComponent.h"
#include "entity/components/AttributeComponent.h"
#include "entity/components/SpriteComponent.h"
#include "entity/managers/base/ComponentManager.h"
#include "entity/managers/SpriteManager.h"
#include "entity/managers/PositionManager.h"
#include "entity/managers/SkillManager.h"
#include "entity/managers/AttackManager.h"
#include "entity/managers/AttributeManager.h"
#include "entity/systems/System.h"
#include "entity/systems/RenderSystem.h"
#include "entity/systems/AttackSystem.h"
