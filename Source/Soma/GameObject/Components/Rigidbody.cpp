#include "Rigidbody.h"
#include "../Renderer.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "BoxCollider.h"
#include "../../Physics/PhysicsEngine.h"

std::string Rigidbody::g_Name = "Rigidbody";

void Rigidbody::Start()
{
	SetAABB();
	//PhysicsEngine::GetSingleton().AddRigidBody(std::make_shared<Rigidbody>(*this));
}

Rigidbody::Rigidbody()
{
}

bool Rigidbody::VInit(Json data)
{
	mass = data["mass"].get<float>();
	obeysGravity = data["useGravity"].get<bool>();

	return true;
}

void Rigidbody::SetAABB() {

	auto col = m_parent->GetComponent<BoxCollider>();
	sf::FloatRect bound = col->GetBounds();
	aabb.bLeft = Vector2(bound.left, bound.top - bound.height);
	aabb.tRight = Vector2(bound.left + bound.width, bound.top);
}

void Rigidbody::Integrate(sf::Time dt) {

	Vector2 acceleration;

	if (obeysGravity && !IsGrounded())
	{
		acceleration = gravity;
	}
	else
	{
		if (abs(currentVelocity.y) < 0.05f)
		{
			currentVelocity.y = 0.0f;
		}
	}

	if (mass == 0.0f)
	{
		acceleration = Vector2(0.0f, 0.0f);
	}
	else
	{
		acceleration += totalForces / mass;
	}

	currentVelocity += acceleration * dt.asSeconds();

	Vector2 temp = GetLocalTransform()->getPosition();
	temp += currentVelocity * dt.asSeconds();
	GetLocalTransform()->setPosition(temp);

	//SetAABB();

	totalForces = Vector2(0.0f, 0.0f);
}