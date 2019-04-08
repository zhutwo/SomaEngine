#include "SpriteRenderer.h"
#include "../Utilities/ResourceHolder.h"

const char* SpriteRenderer::g_Name = "SpriteRenderer";

bool SpriteRenderer::VInit(Json data)
{
	if (!data)
	{
		return false;
	}
	std::string spriteName = data["sprite"].get<std::string>();
	m_sprite = ResourceHolder::GetSingleton().GetSprite(spriteName);

	return true;
}

SpriteRenderer::SpriteRenderer(std::shared_ptr<sf::Sprite> sprite)
	: Renderer()
	, m_sprite(sprite)
{}

void SpriteRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_sprite, states);
}

void SpriteRenderer::Render(sf::RenderTarget& target) const
{
	draw(target, sf::RenderStates::Default);
}

void SpriteRenderer::SetSprite(std::shared_ptr<sf::Sprite> spritePtr)
{
	m_sprite = spritePtr;
}

void SpriteRenderer::SetSprite(sf::Sprite sprite)
{
	m_sprite = std::make_shared<sf::Sprite>(std::move(sprite));
}

void SpriteRenderer::LoadSpriteFromTexture(sf::Texture texture)
{
	m_sprite = std::make_shared<sf::Sprite>();
	m_sprite->setTexture(texture);
}

void SpriteRenderer::LoadSpriteFromTexture(std::shared_ptr<sf::Texture> texturePtr)
{
	m_sprite = std::make_shared<sf::Sprite>();
	m_sprite->setTexture(*texturePtr);
}
