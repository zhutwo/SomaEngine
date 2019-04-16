#include "Component.h"
#include "GameObject.h"

Component::Component()
	: m_isActive(true)
{

}

Component::~Component()
{

}
void Component::SetParent(SharedGameObjectPtr parent)
{
	m_parent = parent;
}

TransformPtr Component::GetTransform(void)
{
	return m_parent->GetTransform();
}

TransformPtr Component::GetLocalTransform(void)
{
	return m_parent->GetLocalTransform();
}
