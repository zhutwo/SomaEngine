#include "../Scene/Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/SpriteRenderer.h"
#include "SFML/Graphics.hpp"

class TestGame
{
public:
	Scene testScene;
	GameObject player;
	GameObject background;
	GameObject bullet;
	sf::Sprite bgsprite;
	sf::Texture bgtex;

	TestGame()
	{
		bgtex.loadFromFile("Space.png");
		bgsprite.setTexture(bgtex);
		SpriteRenderer bgsr(bgsprite);
		auto p = std::make_shared<Component>(bgsr);
		//background.AddComponent(dynamic_cast(p));
		//testScene.AttachChild(SceneNodePtr(background));
	}
	~TestGame() = default;
};