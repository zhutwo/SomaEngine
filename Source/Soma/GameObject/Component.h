#pragma once

#include "SomaStd.h"
#include "SFML/System/Time.hpp"
#include <unordered_map>

/*
Base Component class
*/

class GameObject;
class TransformComponent;

class Component
{
protected:
	
	ComponentId					m_Id;
	bool						m_isActive;
	SharedGameObjectPtr			m_parent;

public:
	Component();
	~Component();

	void SetId(ComponentId id)
	{
		m_Id = id;
	}

	ComponentId GetId(void) const { return m_Id; }

	// These functions are meant to be overridden by the implementation classes of the components.
	virtual bool VInit(Json data) = 0;
	virtual void VPostInit(void) { }
	virtual bool IsRenderer(void) const { return false; }
	virtual void Update(sf::Time dt) {}
	virtual void Start() {}

	// This function should be overridden by the interface class.
	virtual ComponentId VGetId(void) const { return GetIdFromName(VGetName()); }
	virtual std::string VGetName() const = 0;
	static ComponentId GetIdFromName(std::string componentStr)
	{
		auto rawId = std::hash<std::string>{}(componentStr);
		return static_cast<ComponentId>(rawId);
	}
	void SetActive(bool active) { m_isActive = active; }
	bool IsActive(void) const { return m_isActive; }
	void SetParent(SharedGameObjectPtr parent);
};