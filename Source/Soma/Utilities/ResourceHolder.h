#pragma once

#include "SomaStd.h"
#include "SFML/Graphics.hpp"

class ResourceHolder : private NonCopyable
{
private:
	std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	std::map<std::string, std::shared_ptr<sf::Sprite>> m_sprites;
	ResourceHolder() = default;

public:
	ResourceHolder(const ResourceHolder&) = delete;
	ResourceHolder& operator=(const ResourceHolder&) = delete;

	static ResourceHolder& GetSingleton()
	{
		static ResourceHolder inst;
		return inst;
	}

	void Clear();

	bool LoadTexture(std::string name, std::string path);
	bool LoadSprite(std::string name, std::string textureName);

	std::shared_ptr<sf::Texture> GetTexture(std::string name);
	std::shared_ptr<sf::Sprite> GetSprite(std::string name);
};
