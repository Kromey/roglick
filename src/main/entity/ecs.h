/**
 * @file ecs.h
 *
 * This is simply a convenience header that lets us include the entirety of our
 * ECS framework and implementation with a single include directive.
 */
#include "entity/Entity.h"
#include "entity/EntityManager.h"
#include "entity/components/ComponentManager.h"
#include "entity/components/PositionManager.h"
#include "entity/components/SpriteManager.h"
#include "entity/components/AttributeManager.h"
#include "entity/systems/System.h"
#include "entity/systems/RenderSystem.h"
