#include "SceneNode.h"
#include <cassert>

SceneNode::SceneNode()
{
	m_pParent = nullptr;
}

SceneNode::~SceneNode()
{

}

bool SceneNode::AttachChild(SceneNodePtr child)
{
	child->m_pParent = this;
	m_Children.push_back(child);
	return true;
}

SceneNodePtr SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(m_Children.begin(), m_Children.end(), [&](SceneNodePtr& p) { return p.get() == &node; });
	assert(found != m_Children.end());

	SceneNodePtr result = *found;
	result->m_pParent = nullptr;
	m_Children.erase(found);
	return result;
}

void SceneNode::Update(sf::Time dt)
{
	UpdateSelf(dt);
	UpdateChildren(dt);
}

void SceneNode::UpdateChildren(sf::Time dt)
{
	for (SceneNodePtr& child : m_Children)
	{
		child->Update(dt);
	}
}

void SceneNode::Render(sf::RenderTarget& target) const
{
	RenderSelf(target);
	RenderChildren(target);
}

void SceneNode::RenderChildren(sf::RenderTarget& target) const
{
	for (const SceneNodePtr& child : m_Children)
	{
		child->Render(target);
	}
}

void SceneNode::Start()
{
	for (const SceneNodePtr& child : m_Children)
	{
		child->Start();
	}
}
