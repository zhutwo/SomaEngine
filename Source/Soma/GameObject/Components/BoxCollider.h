#pragma once

#include "SomaStd.h"
#include "Collider.h"
#include "SFML/Graphics.hpp"

class BoxCollider : public Collider
{
private:
	sf::FloatRect			m_bounds;
	Vector2					m_size;
	Vector2					m_center;
	bool					m_isTrigger;
public:
	BoxCollider();
	~BoxCollider() = default;

	static std::string g_Name;
	virtual std::string VGetName() const override { return g_Name; }

	virtual bool VInit(Json data) override;

	sf::FloatRect GetBounds();
};