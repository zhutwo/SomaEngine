#pragma once
#include "SomaStd.h"
#include "Component.h"

class Transform : public Component
{
public:
	Vector3				position;
	Vector3				rotation;
	Vector3				scale;

public:
	Transform();
	~Transform();
};