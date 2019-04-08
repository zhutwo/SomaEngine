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

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool VInit(Json data) override;

	SpriteRenderer(std::shared_ptr<sf::Sprite> sprite);
	void Render(sf::RenderTarget& target) const;
	void SetSprite(sf::Sprite sprite);
	void SetSprite(std::shared_ptr<sf::Sprite> spritePtr);
	void LoadSpriteFromTexture(sf::Texture texture);
	void LoadSpriteFromTexture(std::shared_ptr<sf::Texture> texturePtr);

	sf::FloatRect GetBounds(void) const override
	{
		return m_sprite->getGlobalBounds();
	}
};