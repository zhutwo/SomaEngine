#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Renderer.h"

GameObject::GameObject()
	: m_id(0)
	, m_name("NewGameObject")
	, m_transform(std::make_shared<TransformComponent>())
	, m_localTransform(std::make_shared<TransformComponent>())
{}

GameObject::GameObject(GameObjectId id)
	: m_id(id)
	, m_name("NewGameObject")
	, m_transform(std::make_shared<TransformComponent>())
	, m_localTransform(std::make_shared<TransformComponent>())
{}

GameObject::~GameObject()
{

}

bool GameObject::Init(Json data)
{
	m_name = data["name"].get<std::string>();
	m_tag = data["tag"].get<std::string>();

	m_localTransform->VInit(data["transform"]);
	return true;
}

void GameObject::UpdateSelf(sf::Time dt)
{
	for (ComponentMap::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		if (it->second->IsActive())
		{
			it->second->Update(dt);
		}
	}
}

void GameObject::RenderSelf(sf::RenderTarget& target) const
{
	if (!m_renderers.empty())
	{
		for (int i = 0; i < m_renderers.size(); i++)
		{
			if (m_renderers[i]->IsActive())
			{
				m_renderers[i]->Render(target);
			}
		}
	}
}

void GameObject::Start()
{
	for (ComponentMap::iterator it = m_components.begin(); it != m_components.end(); ++it)
	{
		it->second->Start();
	}
	SceneNode::Start();
}

TransformPtr GameObject::GetTransform(void)
{
	return m_transform;
}

TransformPtr GameObject::GetLocalTransform(void)
{
	return m_localTransform;
}
void GameObject::AddComponent(SharedComponentPtr component)
{
	m_components.insert(std::make_pair(component->VGetName(), component));
	if (component->IsRenderer())
	{
		m_renderers.push_back(std::dynamic_pointer_cast<Renderer>(component));
	}
}