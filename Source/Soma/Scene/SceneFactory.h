#pragma once

#include "SomaStd.h"
#include "../GameObject/GameObjectFactory.h"

/*
Scene Factory for loading from JSON
*/
class Scene;
//class GameObjectFactory;

class SceneFactory
{
protected:
	GameObjectFactory m_gameObjectFactory;

public:
	SceneFactory(void);

	SharedScenePtr CreateScene(Json data);
};