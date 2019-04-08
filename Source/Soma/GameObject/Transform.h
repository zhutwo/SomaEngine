#pragma once

#include "SomaStd.h"
#include "Component.h"
#include "SFML/Graphics/Transformable.hpp"

class TransformComponent : public Component, public sf::Transformable
{
public:
	TransformComponent()
	{
		m_Id = 0;
	}
	~TransformComponent() = default;

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool VInit(Json data) override;
};