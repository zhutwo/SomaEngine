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