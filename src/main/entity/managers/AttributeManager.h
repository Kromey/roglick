#ifndef ATTRIBUTEMANAGER_H_
#define ATTRIBUTEMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/managers/base/MultiLookupComponentManager.h"
#include "entity/components/AttributeComponent.h"

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
class AttributeManager :
	public MultiLookupComponentManager<attrtype_t, AttributeComponent>
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
		virtual AttributeComponent getNullSubComponent() { return NULL_ATTRIBUTE; };

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

		//Make sure we get all of our parent's getComponent methods
		//We have to do this to prevent our override below obliterating all the
		//other overloads -- which we want to keep!
		using MultiLookupComponentManager::getComponent;
		/**
		 * Retrieve the attributes of the given Entity. Returns NULL_ATTRIBUTE
		 * if the Entity does not have a AttributeComponent.
		 *
		 * @param e Entity to get the attributes of.
		 *
		 * @return The Entity's Attributes
		 */
		virtual std::map<attrtype_t, AttributeComponent> getComponent(Entity e);

	protected:
		/**
		 * The name may be slightly misleading, but "Stamina" is our catch-all
		 * term for both Sta and Acu; this method will calculate either; for
		 * Sta, Str and Dex should be passed in, and for Acu, Int and Per. Use
		 * the max values of each; the calculation is only valid to compute max
		 * value of Sta/Acu from max values of Str and Dex/Int and Per.
		 *
		 * @param attrs Map of the current attributes
		 * @param type1 The first type to use in the calculation
		 * @param type2 The second type to use in the calculation
		 * @param sta_type The type we are calculating
		 *
		 * @return The calculated max Sta or Acu
		 */
		AttributeComponent calculateStamina(std::map<attrtype_t, AttributeComponent>& attrs, attrtype_t type1, attrtype_t type2, attrtype_t sta_type);
};

#endif
