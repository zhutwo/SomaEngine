#pragma once

#include "SomaStd.h"
#include "Renderer.h"
#include "SFML/Graphics.hpp"

class SpriteRenderer : public Renderer
{
private:
	std::shared_ptr<sf::Sprite>			m_sprite;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	SpriteRenderer() = default;
	~SpriteRenderer() = default;

	SpriteRenderer(std::shared_ptr<sf::Sprite> sprite);
	void Render(sf::RenderTarget& target) const;
	void SetSprite(std::shared_ptr<sf::Sprite> sprite);
	void SetSprite(sf::Sprite sprite);

	sf::FloatRect GetBounds(void) const override
	{
		return m_sprite->getGlobalBounds();
	}
};