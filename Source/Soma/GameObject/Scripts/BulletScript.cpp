#include "BulletScript.h"
#include "../GameObject.h"
#include "../Components/Rigidbody.h"

std::string BulletScript::g_Name = "BulletScript";

BulletScript::BulletScript()
{
}

bool BulletScript::VInit(Json data)
{
	return true;
}

void BulletScript::Update(sf::Time dt)
{
}

void BulletScript::Start()
{
	m_speed = 50.0f;
	m_rigidbody = m_parent->GetComponent<Rigidbody>();
}
