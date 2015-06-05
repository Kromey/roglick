#include "entity/managers/AttributeManager.h"

const AttributeComponent AttributeManager::NULL_ATTRIBUTE = {0, 0};

std::map<attrtype_t, AttributeComponent> AttributeManager::getComponent(Entity e)
{
	//Get the relevant component
	std::map<attrtype_t, AttributeComponent> attrs = MultiLookupComponentManager::getComponent(e);

	//Calculate Sta -- we need Str and Int
	AttributeComponent stamina = calculateStamina(attrs, Str, Dex, Sta);
	//Calculate Acu -- we need Int and Per
	AttributeComponent acuity = calculateStamina(attrs, Int, Per, Acu);

	if(stamina.max != 0)
	{
		attrs[Sta] = stamina;
	}
	if(acuity.max != 0)
	{
		attrs[Acu] = acuity;
	}

	//Now return the whole set
	return attrs;
}

AttributeComponent AttributeManager::calculateStamina(std::map<attrtype_t, AttributeComponent>& attrs, attrtype_t type1, attrtype_t type2, attrtype_t sta_type)
{
	//Search for our attributes
	typename std::map<attrtype_t,AttributeComponent>::iterator attr1_it = attrs.find(type1);
	typename std::map<attrtype_t,AttributeComponent>::iterator attr2_it = attrs.find(type2);
	typename std::map<attrtype_t,AttributeComponent>::iterator sta_it = attrs.find(sta_type);

	//Default to our NULL-equivalent if we don't find a value
	AttributeComponent attr1 = getNullSubComponent();
	AttributeComponent attr2 = getNullSubComponent();
	AttributeComponent sta = getNullSubComponent();

	//Now get the correct attributes, if we did find them
	if(attrs.end() != attr1_it)
	{
		//Get our attribute
		attr1 = attr1_it->second; //first is key, second is value
	}
	if(attrs.end() != attr2_it)
	{
		//Get our attribute
		attr2 = attr2_it->second; //first is key, second is value
	}
	if(attrs.end() != sta_it)
	{
		//Get our attribute
		sta = sta_it->second; //first is key, second is value
	}

	//Finally! We can now calculate what our max should be
	sta.max = (attr1.max + attr2.max) / 2;

	return sta;
}

