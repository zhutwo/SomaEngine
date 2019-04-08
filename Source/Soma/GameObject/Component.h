#pragma once

#include "SomaStd.h"
#include "SFML/System/Time.hpp"

/*
Base Component class
*/

class Component;

class GameObject;
class TransformComponent;

class Component
{
protected:
	
	ComponentId					m_Id;
	bool						m_isActive;
	WeakGameObjectPtr			m_parent;

public:
	Component();
	~Component();

	void SetId(int id)
	{
		m_Id = id;
	}

	int GetId(void) const { return m_Id; }

	// These functions are meant to be overridden by the implementation classes of the components.
	virtual bool VInit(Json data) = 0;
	virtual void VPostInit(void) { }
	virtual bool IsRenderer(void) const { return false; }
	virtual void Update(sf::Time dt) {}

	// This function should be overridden by the interface class.
	virtual ComponentId VGetId(void) const { return GetIdFromName(VGetName()); }
	virtual const char *VGetName() const = 0;
	static ComponentId GetIdFromName(const char* componentStr)
	{
		void* rawId = HashedString::hash_name(componentStr);
		return reinterpret_cast<ComponentId>(rawId);
	}

	void SetActive(bool active) { m_isActive = active; }
	bool IsActive(void) const { return m_isActive; }
	void SetParent(std::shared_ptr<GameObject> parent);
	std::weak_ptr<TransformComponent> Transform(void) const;
};