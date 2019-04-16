#pragma once
#include "SomaStd.h"
#include "../Component.h"

class GameObject;
class Rigidbody;
class AudioSource;

class PlayerController : public Component
{
	std::shared_ptr<Rigidbody>					m_rigidbody;
	std::shared_ptr<AudioSource>				m_audio;
	float										m_force;
	SharedGameObjectPtr							m_bullet;

public:
	PlayerController();
	~PlayerController() = default;

	static std::string g_Name;

	virtual std::string VGetName() const override { return g_Name; }

	virtual bool VInit(Json data) override;

	virtual void Update(sf::Time dt) override;

	virtual void Start() override;
};