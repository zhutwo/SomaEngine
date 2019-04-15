#pragma once

#include "SomaStd.h"
#include "../Component.h"

class Rigidbody;

class TargetScript : public Component
{
	std::shared_ptr<Rigidbody>		m_rigidbody;

public:
	TargetScript();
	~TargetScript() = default;

	static std::string g_Name;

	virtual std::string VGetName() const override { return g_Name; }

	virtual bool VInit(Json data) override;

	virtual void Update(sf::Time dt) override;

	virtual void Start() override;
};