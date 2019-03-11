#include "SpriteRenderer.h"

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

void SpriteRenderer::SetSprite(std::shared_ptr<sf::Sprite> sprite)
{
	m_sprite = sprite;
}

void SpriteRenderer::SetSprite(sf::Sprite sprite)
{
	m_sprite = std::make_shared<sf::Sprite>(std::move(sprite));
}