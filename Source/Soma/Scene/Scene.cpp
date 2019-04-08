#include "Scene.h"

Scene::Scene()
	: m_Name("NewScene")
{

}

Scene::~Scene()
{

}

bool Scene::AttachChild(SceneNodePtr child)
{
	return m_Root.AttachChild(std::move(child));
}

SceneNodePtr Scene::DetachChild(const SceneNode& node)
{
	return m_Root.DetachChild(node);
}

void Scene::Update(sf::Time dt)
{
	m_Root.UpdateChildren(dt);
}

void Scene::Render(sf::RenderTarget& target) const
{
	m_Root.RenderChildren(target);
}