
#include "SomaStd.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneFactory.h"
#include "../Utilities/ResourceHolder.h"
#include <fstream>

class TestGame
{
public:
	SharedScenePtr pScene;

	TestGame()
	{
	}
	~TestGame() = default;

	void Start() {
		pScene->Start();
	}

	void MainLoop(sf::Time dt, sf::RenderTarget &target)
	{
		pScene->Update(dt);
		pScene->Render(target);
	}

	void BuildSceneJSON()
	{
		ResourceHolder::GetSingleton().LoadResources();

		std::ifstream stream("TestScene.json");
		Json json = Json::parse(stream);

		SceneFactory factory;
		pScene = factory.CreateScene(json);
	}
};
