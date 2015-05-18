#include "entity/managers/AttributeManager.h"

#define NOVAL -1

const AttributeComponent AttributeManager::NULL_ATTRIBUTE = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

AttributeComponent AttributeManager::getComponent(Entity e)
{
	//Get the relevant component
	AttributeComponent attrs = LookupComponentManager::getComponent(e);

	//Calculate our Sta and Acu to ensure they're up-to-date
	attrs.Sta.max = calculateStamina(attrs.Str.max, attrs.Dex.max);
	attrs.Acu.max = calculateStamina(attrs.Int.max, attrs.Per.max);

	//Now return the whole set
	return attrs;
}

void AttributeManager::setComponent(Entity e, AttributeComponent attrs)
{
	//Calculate our Sta and Acu to ensure they're up-to-date
	attrs.Sta.max = calculateStamina(attrs.Str.max, attrs.Dex.max);
	attrs.Acu.max = calculateStamina(attrs.Int.max, attrs.Per.max);

	//Now update the component
	LookupComponentManager::setComponent(e, attrs);
}

AttributeVal AttributeManager::getAttribute(Entity e, attrtype_t attr)
{
	//Get our attributes
	AttributeComponent attrs = getComponent(e);

	//Find the one we're interested in
	switch(attr)
	{
		case Str:
			return attrs.Str;
			break;
		case Dex:
			return attrs.Dex;
			break;
		case Sta:
			return attrs.Sta;
			break;
		case Int:
			return attrs.Int;
			break;
		case Per:
			return attrs.Per;
			break;
		case Acu:
			return attrs.Acu;
			break;
		default:
			//Didn't get a valid attrtype, just return the NULL-equivalent value
			AttributeVal av = { 0, 0 };
			return av;
			break;
	}
}

void AttributeManager::setAttribute(Entity e, attrtype_t attr, AttributeVal val)
{
	//Get our current attributes
	AttributeComponent attrs = getComponent(e);

	//Find the one we're interested in and set the new values
	switch(attr)
	{
		case Str:
			attrs.Str = val;
			break;
		case Dex:
			attrs.Dex = val;
			break;
		case Sta:
			attrs.Sta = val;
			break;
		case Int:
			attrs.Int = val;
			break;
		case Per:
			attrs.Per = val;
			break;
		case Acu:
			attrs.Acu = val;
			break;
		default:
			break;
	}

	//Now update our attributes
	setComponent(e, attrs);
}

int AttributeManager::calculateStamina(int attr1, int attr2)
{
	return (attr1 + attr2) / 2;
}

