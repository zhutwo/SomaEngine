#include "SceneFactory.h"
#include "Scene.h"
#include "SceneNode.h"
#include "../GameObject/GameObject.h"

SceneFactory::SceneFactory(void)
{
}

SharedScenePtr SceneFactory::CreateScene(Json data)
{
	SharedScenePtr pScene = std::make_shared<Scene>();
	pScene->m_Name = data["name"].get<std::string>();
	Json heirarchyData = data["heirarchy"];
	for (auto gameObjectData : heirarchyData)
	{
		auto pGameObject = m_gameObjectFactory.CreateGameObject(gameObjectData);
		pScene->AttachChild(std::static_pointer_cast<SceneNode>(pGameObject));
	}
	return pScene;
}
