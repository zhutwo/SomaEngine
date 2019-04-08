#include "ResourceHolder.h"

bool ResourceHolder::LoadTexture(std::string name, std::string path)
{
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>(path);
	if (!texture->loadFromFile(path))
	{
		return false;
	}
	m_textures.insert(std::pair<std::string, std::shared_ptr<sf::Texture>>(name, texture));
	return true;
}

bool ResourceHolder::LoadSprite(std::string name, std::string textureName)
{
	auto texture = GetTexture(textureName);
	if (!texture)
	{
		return false;
	}
	std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
	sprite->setTexture(*texture);
	m_sprites.insert(std::pair<std::string, std::shared_ptr<sf::Sprite>>(name, sprite));
	return true;
}

std::shared_ptr<sf::Texture> ResourceHolder::GetTexture(std::string name)
{
	auto result = m_textures.find(name);
	return result->second;
}

std::shared_ptr<sf::Sprite> ResourceHolder::GetSprite(std::string name)
{
	auto result = m_sprites.find(name);
	return result->second;
}

void ResourceHolder::Clear()
{
	m_textures.clear();
	m_sprites.clear();
}
