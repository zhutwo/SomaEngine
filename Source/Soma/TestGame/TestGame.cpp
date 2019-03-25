#include "../Scene/Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/SpriteRenderer.h"
#include "SFML/Graphics.hpp"

class TestGame
{
public:
	Scene testScene;
	std::vector<std::shared_ptr<sf::Sprite>> spriteList;
	std::vector<std::shared_ptr<sf::Texture>> textureList;

	TestGame()
	{
	}
	~TestGame() = default;

	void BuildScene()
	{
		std::shared_ptr<GameObject> background = std::make_shared<GameObject>(1);

		std::shared_ptr<sf::Texture> bgtex = std::make_shared<sf::Texture>();
		textureList.push_back(bgtex);
		std::shared_ptr<sf::Sprite> bgsprite = std::make_shared<sf::Sprite>();
		spriteList.push_back(bgsprite);

		if (!bgtex->loadFromFile("Space.png"))
		{
			MessageBox(NULL,
				_T("Failed to load background texture"),
				_T("SomaEngine"),
				NULL);
		}

		bgsprite->setTexture(*bgtex);
		std::shared_ptr<SpriteRenderer> bgsr = std::make_shared<SpriteRenderer>();
		bgsr->SetSprite(*bgsprite);
		bgsr->SetId(1);

		background->AddComponent(std::static_pointer_cast<Component>(bgsr));
		testScene.AttachChild(std::static_pointer_cast<SceneNode>(background));

		std::shared_ptr<GameObject> entities = std::make_shared<GameObject>(2);

		std::shared_ptr<sf::Texture> entex = std::make_shared<sf::Texture>();
		textureList.push_back(entex);
		std::shared_ptr<sf::Sprite> ensprite = std::make_shared<sf::Sprite>();
		spriteList.push_back(ensprite);

		if (!entex->loadFromFile("Entities.png"))
		{
			MessageBox(NULL,
				_T("Failed to load entities texture"),
				_T("SomaEngine"),
				NULL);
		}

		ensprite->setTexture(*entex);
		std::shared_ptr<SpriteRenderer> ensr = std::make_shared<SpriteRenderer>();
		ensr->SetSprite(*ensprite);
		ensr->SetId(2);

		entities->AddComponent(std::static_pointer_cast<Component>(ensr));
		testScene.AttachChild(std::static_pointer_cast<SceneNode>(entities));
	}
};
