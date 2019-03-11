#include "Component.h"
#include "GameObject.h"

Component::Component()
	: m_isActive(true)
{

}

Component::~Component()
{

}
void Component::SetParent(std::shared_ptr<GameObject> parent)
{
	m_parent = std::weak_ptr<GameObject>(parent);
}

std::weak_ptr<TransformComponent> Component::Transform(void) const
{
	auto p = m_parent.lock();
	return p->GetTransform();
}