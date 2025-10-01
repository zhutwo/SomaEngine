#pragma once

#include "SomaStd.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"

class Rigidbody;

class PhysicsEngine {

public:
	typedef std::weak_ptr<Rigidbody> WeakRigidbodyPtr;

	float groundedTol = 0.1f;
	
	struct CollisionPair {
	public:
		WeakRigidbodyPtr rigidBodyA;
		WeakRigidbodyPtr rigidBodyB;
	};

	struct CollisionInfo {
	public:
		Vector2 collisionNormal;
		float penetration;
	};

	struct CollisionEvent {
	public:
		CollisionPair collisionPair;
		CollisionInfo collisionInfo;
	};
	
	std::map<CollisionPair, CollisionInfo> collisions;
	std::vector<WeakRigidbodyPtr> rigidBodies;

public:
		
	void AddRigidBody(std::shared_ptr<Rigidbody> rigidBody) {
		rigidBodies.push_back(WeakRigidbodyPtr(rigidBody));
	}

	void IntegrateBodies(sf::Time dt);

	bool IsGrounded(Rigidbody& rigidBody) {
		foreach(PhysicsRBody rb in rigidBodies)
		{
			if (rb != rigidBody)
			{
				if (rigidBody.aabb.bLeft.x < rb.aabb.tRight.x
					&& rigidBody.aabb.tRight.x > rb.aabb.bLeft.x
					&& Mathf.Abs(rigidBody.aabb.bLeft.y - rb.aabb.tRight.y) <= groundedTol)
				{
					if (Mathf.Abs(rigidBody.currentVelocity.y) < groundedTol)
						return true;
				}
			}
		}
		return false;
	}

	void CheckCollisions();

	void ResolveCollisions();

	void PositionalCorrection(CollisionPair c);

	void Update(sf::Time dt) {
		IntegrateBodies(dt);
		CheckCollisions();
		ResolveCollisions();
	}
};