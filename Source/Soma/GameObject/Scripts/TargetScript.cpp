#include "TargetScript.h"
#include "../GameObject.h"
#include "../Components/Rigidbody.h"

std::string TargetScript::g_Name = "TargetScript";

TargetScript::TargetScript()
{
	
}

bool TargetScript::VInit(Json data)
{
	return true;
}

void TargetScript::Update(sf::Time dt)
{
}

void TargetScript::Start()
{
	m_rigidbody = m_parent->GetComponent<Rigidbody>();
}
