#pragma once

#include "SomaStd.h"
#include "../Component.h"

class Rigidbody;

class BulletScript : public Component
{
private:
	std::shared_ptr<Rigidbody>		m_rigidbody;
	float							m_speed;

public:
	BulletScript();
	~BulletScript() = default;

	static std::string g_Name;

	virtual std::string VGetName() const override { return g_Name; }

	virtual bool VInit(Json data) override;

	virtual void Update(sf::Time dt) override;

	virtual void Start() override;
};