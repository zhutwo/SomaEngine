#pragma once

#include "SomaStd.h"
#include "../Component.h"
#include "SFML/Graphics.hpp"

class PhysicsEngine;
class TransformComponent;

class Rigidbody : public Component 
{
public:

	friend class PhysicsEngine;

	struct AABB {
	public:
		Vector2 bLeft;
		Vector2 tRight;
	};

	float mass = 1.0f;
	// Mass of the RigidBody
	float bounciness = 1.0f;
	// The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
	bool obeysGravity = true;
	// Whether or not this body obeys gravity
	Vector2 gravity = Vector2(0.0f, -9.81f);
	// The gravity vector applied to this body
	
	Vector2 currentVelocity;
	// The current velocity the body is moving at
	Vector2 maxVelocity = Vector2(10.0f, 10.0f);
	// The maximum allowed velocity for this object

	bool grounded;

	Vector2 totalForces;
	
	PhysicsEngine* m_engine;

	AABB aabb;

public:
	
	Rigidbody() = default;
	~Rigidbody() = default;

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool VInit(Json data) override;

	void AddForce(Vector2 force) {
		totalForces += force;
	}

	void Stop() {
		currentVelocity = Vector2(0.0f,0.0f);
		totalForces = Vector2(0.0f, 0.0f);
	}
	
	bool IsGrounded() {
		//grounded = m_engine->IsGrounded(this);
		//return grounded;
		return false;
	}
	
	void SetAABB();

	void Start();

	void Integrate(sf::Time dt);
};