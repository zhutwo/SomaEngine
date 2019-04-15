#include "BoxCollider.h"

std::string BoxCollider::g_Name = "BoxCollider";

BoxCollider::BoxCollider()
{
}

bool BoxCollider::VInit(Json data)
{
	if (!data)
	{
		return false;
	}

	m_isTrigger = data["isTrigger"].get<bool>();
	m_size.x = data["size"]["x"].get<float>();
	m_size.y = data["size"]["y"].get<float>();
	m_center.x = data["center"]["x"].get<float>();
	m_center.y = data["center"]["y"].get<float>();
	m_bounds.width = m_size.x;
	m_bounds.height = m_size.y;
	m_bounds.top = m_center.y; //change this
	m_bounds.left = m_center.x;

	return true;
}

sf::FloatRect BoxCollider::GetBounds()
{
	return m_bounds;
}
