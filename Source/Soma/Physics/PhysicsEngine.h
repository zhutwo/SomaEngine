#pragma once

#include "SomaStd.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Time.hpp"

class Rigidbody;

class PhysicsEngine : private NonCopyable {

private:
	PhysicsEngine() = default;

public:
	PhysicsEngine(const PhysicsEngine&) = delete;
	PhysicsEngine& operator=(const PhysicsEngine&) = delete;

	static PhysicsEngine& GetSingleton()
	{
		static PhysicsEngine inst;
		return inst;
	}

	typedef std::shared_ptr<Rigidbody> RigidbodyPtr;

	float groundedTol = 0.1f;
	
	struct CollisionPair {
	public:
		RigidbodyPtr rigidBodyA;
		RigidbodyPtr rigidBodyB;
	};

	struct CollisionInfo {
	public:
		Vector2 collisionNormal;
		float penetration;
	};

	struct CollisionEvent {
	public:
		std::shared_ptr<CollisionPair> collisionPair;
		CollisionInfo collisionInfo;
	};
	
	std::map<std::shared_ptr<CollisionPair>, CollisionInfo> collisions;
	std::vector<RigidbodyPtr> rigidBodies;

public:
		
	void AddRigidBody(std::shared_ptr<Rigidbody> rigidBody) {
		rigidBodies.push_back(rigidBody);
	}

	void IntegrateBodies(sf::Time dt);

	/*
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
	*/
	void CheckCollisions();

	void ResolveCollisions();

	void PositionalCorrection(std::shared_ptr<CollisionPair> c);

	void Update(sf::Time dt) {

		IntegrateBodies(dt);
		//CheckCollisions();
		//ResolveCollisions();
	}
};