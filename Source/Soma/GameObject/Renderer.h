#pragma once

#include "SomaStd.h"
#include "Component.h"
#include "SFML/Graphics.hpp"

/*
Base Renderer class
*/

class Renderer : public Component, public sf::Drawable
{
public:
	Renderer() = default;
	~Renderer() = default;

	bool IsRenderer(void) const override { return true; }
	virtual void Render(sf::RenderTarget& target) const = 0;
	virtual sf::FloatRect GetBounds(void) const = 0;
};