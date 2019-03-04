#include "Rigidbody.h"
#include "../Renderer.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../../Physics/PhysicsEngine.h"

void Rigidbody::Start()
{
	SetAABB();
	m_engine->AddRigidBody(std::make_shared<Rigidbody>(*this));
}

void Rigidbody::SetAABB() {

	sf::FloatRect bound;
	auto p = m_parent.lock()->GetComponent<Renderer>();
	if (!p.expired())
	{
		bound = p.lock()->GetBounds();
	}
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

	Vector2 temp = Transform().lock()->getPosition();
	temp += currentVelocity * dt.asSeconds();
	Transform().lock()->setPosition(temp);
	SetAABB();

	totalForces = Vector2(0.0f, 0.0f);
}