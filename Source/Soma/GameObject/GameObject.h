#pragma once

#include "SomaStd.h"
#include "Component.h"
#include "Transform.h"
#include "..\Scene\SceneNode.h"
#include <typeinfo>

class Component;
class TransformComponent;
class Renderer;

class GameObject : public SceneNode
{
	friend class GameObjectFactory;

public:
	typedef std::map<ComponentId, SharedComponentPtr> ComponentMap;
	typedef std::vector<std::shared_ptr<Renderer>> RendererList;

private:
	std::string									m_name;
	std::string									m_tag;
	GameObjectId								m_id;
	ComponentMap								m_components;
	RendererList								m_renderers;

public:

	std::shared_ptr<TransformComponent>			m_transform;
	std::shared_ptr<TransformComponent>			m_localTransform;

public:
	GameObject();
	explicit GameObject(GameObjectId id);
	~GameObject(void);

	bool Init(Json data);

	void UpdateSelf(sf::Time dt) override;
	void RenderSelf(sf::RenderTarget& target) const override;
	void Start() override;

	std::string Tag(void) { return m_tag; }

	//TransformComponent* GetTransform(void);
	//TransformComponent* GetLocalTransform(void);
	
	template <class ComponentType>
	std::shared_ptr<ComponentType> GetComponent() 
	{
		for (ComponentMap::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			if (typeid(it->second.get()) == typeid(ComponentType))
			{
				SharedComponentPtr pBase(it->second);
				std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
				return pSub;
				//std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
				//return pWeakSub;  // return the weak pointer
			}
		}
		return std::shared_ptr<ComponentType>();
	}

	//template <>
	//std::shared_ptr<TransformComponent> GetComponent<TransformComponent>() { return std::make_shared<TransformComponent>(m_transform); }

	void AddComponent(SharedComponentPtr component);
};