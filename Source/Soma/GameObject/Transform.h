#pragma once

#include "SomaStd.h"
#include "Component.h"
#include "SFML/Graphics/Transformable.hpp"

class TransformComponent : public Component, public sf::Transformable
{
public:
	TransformComponent();
	~TransformComponent() = default;

	static std::string g_Name;
	virtual std::string VGetName() const override { return g_Name; }

	virtual bool VInit(Json data) override;
};