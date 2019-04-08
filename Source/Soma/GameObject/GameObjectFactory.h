#pragma once

#include "SomaStd.h"

/*
GameObject Factory for loading from JSON
*/
class Component;

class GameObjectFactory
{
	GameObjectId m_lastGameObjectId;

protected:
	GenericObjectFactory<Component, ComponentId> m_componentFactory;

public:
	GameObjectFactory(void);

	//SharedGameObjectPtr CreateGameObject(const char* actorResource, TiXmlElement* overrides, const sf::Transformable* initialTransform, const GameObjectId serversActorId);
	SharedGameObjectPtr CreateGameObject(Json data);

	//protected:
		// [rez] This function can be overridden by a subclass so you can create game-specific C++ components.  If you do
		// this, make sure you call the base-class version first.  If it returns NULL, you know it's not an engine component.
	virtual SharedComponentPtr VCreateComponent(Json data);

private:
	GameObjectId GetNextGameObjectId(void) { ++m_lastGameObjectId; return m_lastGameObjectId; }
};