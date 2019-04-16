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
	typedef std::map<std::string, SharedComponentPtr> ComponentMap;
	typedef std::vector<std::shared_ptr<Renderer>> RendererList;

private:
	std::string									m_name;
	std::string									m_tag;
	GameObjectId								m_id;
	ComponentMap								m_components;
	RendererList								m_renderers;

public:

	TransformPtr								m_transform;
	TransformPtr								m_localTransform;

public:
	GameObject();
	explicit GameObject(GameObjectId id);
	~GameObject(void);

	bool Init(Json data);

	void UpdateSelf(sf::Time dt) override;
	void RenderSelf(sf::RenderTarget& target) const override;
	void Start() override;

	std::string Tag(void) { return m_tag; }

	TransformPtr GetTransform(void);
	TransformPtr GetLocalTransform(void);
	
	template <class ComponentType>
	std::shared_ptr<ComponentType> GetComponent() 
	{
		for (ComponentMap::iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			if (ComponentType* p = dynamic_cast<ComponentType*>(it->second.get()))
			{
				SharedComponentPtr pBase(it->second);
				std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
				return pSub;
				//std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
				//return pWeakSub;  // return the weak pointer
			}
		}
		Helper::Print("Tried to get component not found");
		return std::shared_ptr<ComponentType>();
	}

	//template <>
	//TransformPtr GetComponent<TransformComponent>() { return std::make_shared<TransformComponent>(m_transform); }

	void AddComponent(SharedComponentPtr component);
};