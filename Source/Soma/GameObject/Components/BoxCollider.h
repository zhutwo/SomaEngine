#pragma once

#include "SomaStd.h"
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider() = default;
	~BoxCollider() = default;

	static const char *g_Name;
	virtual const char *VGetName() const { return g_Name; }

	virtual bool VInit(Json data) override;
};