#pragma once

#include "SomaStd.h"
#include "Component.h"
#include "..\Scene\SceneNode.h"

class Component;
class TransformComponent;
class Renderer;

class GameObject : public SceneNode
{
public:
	typedef std::map<ComponentId, SharedComponentPtr> ComponentMap;
	typedef std::vector<std::shared_ptr<Renderer>> RendererList;

private:
	GameObjectId								m_id;
	ComponentMap								m_components;
	RendererList								m_renderers;
	std::shared_ptr<TransformComponent>			m_transform;
	std::shared_ptr<TransformComponent>			m_localTransform;

public:
	explicit GameObject(GameObjectId id);
	~GameObject(void);

	void UpdateSelf(sf::Time dt) override;
	void RenderSelf(sf::RenderTarget& target) const override;

	std::weak_ptr<TransformComponent> GetTransform(void) { return std::weak_ptr<TransformComponent>(m_transform); }
	std::weak_ptr<TransformComponent> GetLocalTransform(void) { return std::weak_ptr<TransformComponent>(m_localTransform); }
	
	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponent() 
	{
		for (ComponentMap::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			if (true)
			{
				SharedComponentPtr pBase(it->second);
				std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
				std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
				return pWeakSub;  // return the weak pointer
			}
		}
		return std::weak_ptr<ComponentType>();
	}

	template <>
	std::weak_ptr<TransformComponent> GetComponent<TransformComponent>() { return std::weak_ptr<TransformComponent>(m_transform); }

	void AddComponent(SharedComponentPtr component);
};