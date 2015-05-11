#include "entity/components/AttributeManager.h"

#define NOVAL -1

const AttributeComponent AttributeManager::NULL_ATTRIBUTE = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

void AttributeManager::addComponent(Entity e)
{
	setAttribute(e, NULL_ATTRIBUTE);
}

void AttributeManager::removeComponent(Entity e)
{
	int idx = getComponentIndex(e);

	//Set our map to reflect that this Entity no longer has any attributes
	setComponentIndex(e, NOVAL);

	//Find the largest index in our entity_map
	int max_idx = idx;
	Entity max_e = e;
	getMaxComponentIndex(max_e, max_idx);

	if(max_idx != idx)
	{
		//Fill the new gap with our current last component
		_attributes[idx] = _attributes[max_idx];
		setComponentIndex(max_e, idx);

		//Now shrink our vector to fit our new size
		_attributes.resize(_attributes.size() - 1);
	}
}

AttributeComponent AttributeManager::getAttribute(Entity e)
{
	if(entityHasComponent(e))
	{
		//Look up where the Entity's attribute is kept...
		int idx = getComponentIndex(e);
		//...and fetch it
		return _attributes[idx];
	} else {
		//Entity has no attribute
		return NULL_ATTRIBUTE;
	}
}

void AttributeManager::setAttribute(Entity e, AttributeComponent attrs)
{
	if(entityHasComponent(e))
	{
		int idx = getComponentIndex(e);
		_attributes[idx] = attrs;
	} else {
		//Brand spankin' new AttributeComponent
		//Add this to our vector of attributes
		_attributes.push_back(attrs);
		setComponentIndex(e, _attributes.size()-1);
	}
}

AttributeVal AttributeManager::getAttribute(Entity e, attrtype_t attr)
{
	//Get our attributes
	AttributeComponent attrs = getAttribute(e);

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
	AttributeComponent attrs = getAttribute(e);

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
	setAttribute(e, attrs);
}

