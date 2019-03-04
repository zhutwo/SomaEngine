#pragma once

#include "SomaStd.h"
#include "Component.h"
#include "SFML/Graphics/Transformable.hpp"

class TransformComponent : public Component, public sf::Transformable
{
public:
	TransformComponent() = default;
	~TransformComponent() = default;
};