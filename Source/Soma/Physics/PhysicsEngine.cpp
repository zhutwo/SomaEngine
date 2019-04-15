#include "PhysicsEngine.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/Components/Rigidbody.h"
#include "../GameObject/Transform.h"

void PhysicsEngine::IntegrateBodies(sf::Time dt) {
	for (int i = 0; i < rigidBodies.size(); i++)
	{
		rigidBodies[i]->Integrate(dt);
	}
}

void PhysicsEngine::CheckCollisions() {
	for (int i = 0; i < rigidBodies.size(); i++)
	{
		for (int j = i; j < rigidBodies.size(); j++)
		{
			auto bodyA = rigidBodies[i];
			auto bodyB = rigidBodies[j];
			if (bodyA != bodyB && bodyA->IsActive() && bodyB->IsActive())
			{
				std::shared_ptr<CollisionPair> pair = std::make_shared<CollisionPair>();
				CollisionInfo colInfo;
				pair->rigidBodyA = RigidbodyPtr(bodyA);
				pair->rigidBodyB = RigidbodyPtr(bodyB);

				Vector2 distance = bodyB->m_parent->m_transform->getPosition() - bodyA->m_parent->m_transform->getPosition();

				Vector2 halfSizeA = (bodyA->aabb.tRight - bodyA->aabb.bLeft) / 2.0f;
				Vector2 halfSizeB = (bodyB->aabb.tRight - bodyB->aabb.bLeft) / 2.0f;

				Vector2 gap = Vector2(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);

				auto found = collisions.find(pair);

				// Seperating Axis Theorem test
				if (gap.x < 0.0f && gap.y < 0.0f)
				{
					//Debug.Log("Collided!!!");

					if (found->first == pair)
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
				else if (found->first == pair)
				{
					collisions.erase(found);
				}

			}
		}
	}
}

void PhysicsEngine::ResolveCollisions() {
	for (std::map<std::shared_ptr<CollisionPair>, CollisionInfo>::iterator it = collisions.begin(); it != collisions.end(); ++it)
	{
		std::shared_ptr<CollisionPair> pair = it->first;
		float minBounce = std::min(pair->rigidBodyA->bounciness, pair->rigidBodyB->bounciness);
		float velAlongNormal = Vec2Dot(pair->rigidBodyB->currentVelocity - pair->rigidBodyA->currentVelocity, collisions[pair].collisionNormal);

		if (velAlongNormal > 0.0f)
		{
			continue;
		}

		float j = -(1.0f + minBounce) * velAlongNormal;
		float invMassA, invMassB;
		if (pair->rigidBodyA->mass == 0.0f)
			invMassA = 0.0f;
		else
			invMassA = 1.0f / pair->rigidBodyA->mass;

		if (pair->rigidBodyB->mass == 0.0f)
			invMassB = 0.0f;
		else
			invMassB = 1.0f / pair->rigidBodyB->mass;

		j /= invMassA + invMassB;

		Vector2 impulse = j * collisions[pair].collisionNormal;

		// ... update velocities
		pair->rigidBodyA->currentVelocity -= impulse * invMassA;
		pair->rigidBodyB->currentVelocity += impulse * invMassB;

		if (abs(collisions[pair].penetration) > 0.01f)
		{
			PositionalCorrection(pair);
		}
	}
}

void PhysicsEngine::PositionalCorrection(std::shared_ptr<CollisionPair> c) {
	const float percent = 0.2f;

	float invMassA, invMassB;
	if (c->rigidBodyA->mass == 0.0f)
		invMassA = 0.0f;
	else
		invMassA = 1.0f / c->rigidBodyA->mass;

	if (c->rigidBodyB->mass == 0.0f)
		invMassB = 0.0f;
	else
		invMassB = 1.0f / c->rigidBodyB->mass;

	Vector2 correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;

	Vector2 temp = c->rigidBodyA->m_parent->m_transform->getPosition();
	temp -= invMassA * correction;
	c->rigidBodyA->m_parent->m_transform->setPosition(temp);

	temp = c->rigidBodyA->m_parent->m_transform->getPosition();
	temp += invMassB * correction;
	c->rigidBodyA->m_parent->m_transform->setPosition(temp);
}