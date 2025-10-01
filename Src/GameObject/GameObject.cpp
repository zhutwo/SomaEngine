#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Renderer.h"

GameObject::GameObject()
	: m_transform(new TransformComponent)
	, m_localTransform(new TransformComponent)
{}

GameObject::~GameObject()
{

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

void GameObject::AddComponent(SharedComponentPtr component)
{
	m_components.insert(std::make_pair(999, component)); // replace 999 with get id
	if (component->IsRenderer())
	{
		m_renderers.push_back(std::dynamic_pointer_cast<Renderer>(component));
	}
}