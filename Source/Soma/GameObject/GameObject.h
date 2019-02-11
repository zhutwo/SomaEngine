#pragma once

#include "SomaStd.h"
#include "Component.h"
#include "Transform.h"
#include "..\Scene\SceneNode.h"

typedef std::map<ComponentId, SharedComponentPtr> ComponentMap;

class GameObject : public SceneNode
{
private:
	ComponentMap			m_Components;
public:
	Transform				transform;

public:
	GameObject();
	~GameObject();

	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponent();

};