#include "ResourceHolder.h"

bool ResourceHolder::LoadTexture(std::string name, std::string path)
{
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
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

bool ResourceHolder::LoadSoundBuffer(std::string name, std::string path)
{
	std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
	if (!soundBuffer->loadFromFile(path))
	{
		return false;
	}
	m_soundBuffers.insert(std::pair<std::string, std::shared_ptr<sf::SoundBuffer>>(name, soundBuffer));
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

std::shared_ptr<sf::SoundBuffer> ResourceHolder::GetSoundBuffer(std::string name)
{
	auto result = m_soundBuffers.find(name);
	return result->second;
}

void ResourceHolder::LoadResources()
{
	LoadTexture("Space", "Space.png");
	LoadTexture("magikarp", "magikarp.png");
	LoadTexture("snorlax", "snorlax.png");
	LoadTexture("bluefighter", "bluefighter.png");
	LoadTexture("redfighter", "redfighter.png");
	LoadTexture("greenfighter", "greenfighter.png");
	LoadTexture("bullet", "bullet.png");

	LoadSprite("Space", "Space");
	LoadSprite("magikarp", "magikarp");
	LoadSprite("snorlax", "snorlax");
	LoadSprite("bluefighter", "bluefighter");
	LoadSprite("redfighter", "redfighter");
	LoadSprite("greenfighter", "greenfighter");
	LoadSprite("bullet", "bullet");

	LoadSoundBuffer("hit", "hit.wav");
	LoadSoundBuffer("shoot", "shoot.wav");
	LoadSoundBuffer("shoot2", "shoot2.wav");
	LoadSoundBuffer("battle", "battle.wav");
	LoadSoundBuffer("tem", "tem.wav");
}

void ResourceHolder::Clear()
{
	m_textures.clear();
	m_sprites.clear();
	m_soundBuffers.clear();
}
