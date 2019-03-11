#include "../Scene/Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/SpriteRenderer.h"
#include "SFML/Graphics.hpp"

class TestGame
{
public:
	Scene testScene;
	//GameObject player;
	std::shared_ptr<GameObject> background;
	//GameObject bullet;
	
	TestGame()
	{
	}
	~TestGame() = default;

	void BuildScene()
	{
		background = std::make_shared<GameObject>();
		sf::Texture bgtex;
		if (!bgtex.loadFromFile("Space.png"))
		{
			MessageBox(NULL,
				_T("Failed to load background texture"),
				_T("SomaEngine"),
				NULL);
		}
		sf::Sprite bgsprite;
		bgsprite.setTexture(bgtex);
		std::shared_ptr<SpriteRenderer> bgsr = std::make_shared<SpriteRenderer>();
		bgsr->SetSprite(bgsprite);
		bgsr->SetId(1);

		background->AddComponent(std::static_pointer_cast<Component>(bgsr));
		testScene.AttachChild(std::static_pointer_cast<SceneNode>(background));
	}
};