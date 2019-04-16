#include "PlayerController.h"
#include "../GameObject.h"
#include "Rigidbody.h"
#include "AudioSource.h"
#include "SFML/Window/Keyboard.hpp"

std::string PlayerController::g_Name = "PlayerController";


PlayerController::PlayerController()
{
}

bool PlayerController::VInit(Json data)
{
	return true;
}

void PlayerController::Update(sf::Time dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_audio->Play();
	}

	Vector2 vForce;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		vForce.x -= 1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		vForce.x += 1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		vForce.y -= 1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		vForce.y += 1.0f;
	}
	m_rigidbody->AddForce(vForce * m_force);
}

void PlayerController::Start()
{
	m_force = 100.0f;
	m_rigidbody = m_parent->GetComponent<Rigidbody>();
	m_audio = m_parent->GetComponent<AudioSource>();
}
