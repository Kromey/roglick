#ifndef ATTRIBUTEMANAGER_H_
#define ATTRIBUTEMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/managers/base/LookupComponentManager.h"

/**
 * Data structure to represent current/maximum values of attributes.
 */
typedef struct
{
	int cur; ///< Current value
	int max; ///< Max value
} AttributeVal;

/**
 * Data structure for an attribute component.
 */
typedef struct
{
	AttributeVal Str; ///< Strength
	AttributeVal Dex; ///< Dexterity
	AttributeVal Sta; ///< Stamina
	AttributeVal Int; ///< Intelligence
	AttributeVal Per; ///< Perception
	AttributeVal Acu; ///< Acuity
} AttributeComponent;

/**
 * Enumeration for identifying different attributes.
 */
enum attrtype_t {
	Str,
	Dex,
	Sta,
	Int,
	Per,
	Acu
};

/**
 * AttributeManager is the ComponentManager for Attribute components.
 *
 * Attributes define the basic capabilities of an Entity.
 */
class AttributeManager : public LookupComponentManager<AttributeComponent>
{
	public:
		/**
		 * Default and NULL-equivalent AttributeComponent value.
		 */
		static const AttributeComponent NULL_ATTRIBUTE;

		/**
		 * Return a NULL_ATTRIBUTE AttributeComponent.
		 *
		 * @return NULL_ATTRIBUTE
		 */
		virtual AttributeComponent getNullComponent() { return NULL_ATTRIBUTE; };

		/**
		 * Constructor
		 */
		AttributeManager() {};

		/**
		 * AttributeManager is the ComponentManager sub-class for Attribute.
		 *
		 * @return The Attribute enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Attribute; };

		/**
		 * Retrieve the attributes of the given Entity. Returns NULL_ATTRIBUTE
		 * if the Entity does not have a AttributeComponent.
		 *
		 * @param e Entity to get the attributes of.
		 *
		 * @return The Entity's Attributes
		 */
		virtual AttributeComponent getComponent(Entity e);
		/**
		 * Set the AttributeComponent for the given Entity.
		 *
		 * @param e The Entity
		 * @param attrs Attributes of this Entity
		 */
		virtual void setComponent(Entity e, AttributeComponent attrs);

		/**
		 * Get one particular attribute instead of the whole set.
		 *
		 * @param e The Entity to get the attribute of
		 * @param attr The specific attribute to get
		 *
		 * @return The current and maximum values of the specified attribute
		 */
		AttributeVal getAttribute(Entity e, attrtype_t attr);
		/**
		 * Set one particular attribute instead of the whole set
		 *
		 * @param e The Entity to set the attribute of
		 * @param attr The specific attribute to set
		 * @param val The value to set it to
		 */
		void setAttribute(Entity e, attrtype_t attr, AttributeVal val);

	protected:
		/**
		 * The name may be slightly misleading, but "Stamina" is our catch-all
		 * term for both Sta and Acu; this method will calculate either; for
		 * Sta, Str and Dex should be passed in, and for Acu, Int and Per. Use
		 * the max values of each; the calculation is only valid to compute max
		 * value of Sta/Acu from max values of Str and Dex/Int and Per.
		 *
		 * @param attr1
		 * @param attr2
		 *
		 * @return The calculated max Sta or Acu
		 */
		int calculateStamina(int attr1, int attr2);
};

#endif
