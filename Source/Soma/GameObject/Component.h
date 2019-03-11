#pragma once

#include "SomaStd.h"
#include "SFML/System/Time.hpp"

/*
Base Component class
*/

class Component;

typedef std::shared_ptr<Component> SharedComponentPtr;
typedef unsigned int ComponentId;

class GameObject;
class TransformComponent;

class Component
{
protected:
	
	int							m_Id;
	bool						m_isActive;
	std::weak_ptr<GameObject>	m_parent;

public:
	Component();
	~Component();

	void SetId(int id)
	{
		m_Id = id;
	}

	int GetId(void) const { return m_Id; }

	virtual bool IsRenderer(void) const { return false; }
	virtual void Update(sf::Time dt) {}
	void SetActive(bool active) { m_isActive = active; }
	bool IsActive(void) const { return m_isActive; }
	void SetParent(std::shared_ptr<GameObject> parent);
	std::weak_ptr<TransformComponent> Transform(void) const;
};