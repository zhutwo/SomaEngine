#include "PhysicsEngine.h"
#include "../GameObject/Components/Rigidbody.h"
#include "../GameObject/Transform.h"

void PhysicsEngine::IntegrateBodies(sf::Time dt) {
	for (int i = 0; i < rigidBodies.size(); i++)
	{
		rigidBodies[i].lock()->Integrate(dt);
	}
}
/*
void PhysicsEngine::CheckCollisions() {
	for (int i = 0; i < rigidBodies.size(); i++)
	{
		for (int j = i; j < rigidBodies.size(); j++)
		{
			auto bodyA = rigidBodies[i].lock();
			auto bodyB = rigidBodies[j].lock();
			if (bodyA != bodyB && bodyA->IsActive() && bodyB->IsActive())
			{
				CollisionPair pair;
				CollisionInfo colInfo;
				pair.rigidBodyA = WeakRigidbodyPtr(bodyA);
				pair.rigidBodyB = WeakRigidbodyPtr(bodyB);

				Vector2 distance = bodyB->Transform().lock()->getPosition() - bodyA->Transform().lock()->getPosition();

				Vector2 halfSizeA = (bodyA->aabb.tRight - bodyA->aabb.bLeft) / 2.0f;
				Vector2 halfSizeB = (bodyB->aabb.tRight - bodyB->aabb.bLeft) / 2.0f;

				Vector2 gap = Vector2(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

				auto found = collisions.find(pair);

				// Seperating Axis Theorem test
				if (gap.x < 0.0f && gap.y < 0.0f)
				{
					//Debug.Log("Collided!!!");

					if (&found->first == &pair)
					{
						collisions.erase(found);
					}

					if (gap.x > gap.y)
					{
						if (distance.x > 0.0f)
						{
							// ... Update collision normal
							colInfo.collisionNormal = Vector2(1.0f, 0.0f);
						}
						else
						{
							// ... Update collision normal
							colInfo.collisionNormal = Vector2(-1.0f, 0.0f);
						}
						colInfo.penetration = gap.x;
					}
					else
					{
						if (distance.y > 0.0f)
						{
							// ... Update collision normal
							colInfo.collisionNormal = Vector2(0.0f, 1.0f);
						}
						else
						{
							// ... Update collision normal
							colInfo.collisionNormal = Vector2(0.0f, -1.0f);
						}
						colInfo.penetration = gap.y;
					}
					collisions.insert(std::make_pair(pair, colInfo));
				}
				else if (&found->first == &pair)
				{
					collisions.erase(found);
				}

			}
		}
	}
}

void PhysicsEngine::ResolveCollisions() {
	for (std::map<CollisionPair, CollisionInfo>::iterator it = collisions.begin(); it != collisions.end(); ++it)
	{
		CollisionPair pair = it->first;
		float minBounce = std::min(pair.rigidBodyA.lock()->bounciness, pair.rigidBodyB.lock()->bounciness);
		float velAlongNormal = Vec2Dot(pair.rigidBodyB.lock()->currentVelocity - pair.rigidBodyA.lock()->currentVelocity, collisions[pair].collisionNormal);

		if (velAlongNormal > 0.0f)
		{
			continue;
		}

		float j = -(1.0f + minBounce) * velAlongNormal;
		float invMassA, invMassB;
		if (pair.rigidBodyA.lock()->mass == 0.0f)
			invMassA = 0.0f;
		else
			invMassA = 1.0f / pair.rigidBodyA.lock()->mass;

		if (pair.rigidBodyB.lock()->mass == 0.0f)
			invMassB = 0.0f;
		else
			invMassB = 1.0f / pair.rigidBodyB.lock()->mass;

		j /= invMassA + invMassB;

		Vector2 impulse = j * collisions[pair].collisionNormal;

		// ... update velocities
		pair.rigidBodyA.lock()->currentVelocity -= impulse * invMassA;
		pair.rigidBodyB.lock()->currentVelocity += impulse * invMassB;

		if (abs(collisions[pair].penetration) > 0.01f)
		{
			PositionalCorrection(pair);
		}
	}
}

void PhysicsEngine::PositionalCorrection(CollisionPair c) {
	const float percent = 0.2f;

	float invMassA, invMassB;
	if (c.rigidBodyA.lock()->mass == 0.0f)
		invMassA = 0.0f;
	else
		invMassA = 1.0f / c.rigidBodyA.lock()->mass;

	if (c.rigidBodyB.lock()->mass == 0.0f)
		invMassB = 0.0f;
	else
		invMassB = 1.0f / c.rigidBodyB.lock()->mass;

	Vector2 correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

	Vector2 temp = c.rigidBodyA.lock()->Transform().lock()->getPosition();
	temp -= invMassA * correction;
	c.rigidBodyA.lock()->Transform().lock()->setPosition(temp);

	temp = c.rigidBodyA.lock()->Transform().lock()->getPosition();
	temp += invMassB * correction;
	c.rigidBodyA.lock()->Transform().lock()->setPosition(temp);
}
*/