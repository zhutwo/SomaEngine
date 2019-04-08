#include "Transform.h"

const char* TransformComponent::g_Name = "TransformComponent";

bool TransformComponent::VInit(Json data)
{
	if (!data)
	{
		return false;
	}

	Vector2 position;
	position.x = data["localPosition"]["x"].get<float>();
	position.y = data["localPosition"]["y"].get<float>();
	setPosition(position);

	Vector2 scale;
	scale.x = data["localScale"]["x"].get<float>();
	scale.y = data["localScale"]["y"].get<float>();
	setScale(scale);

	float rotation = data["localRotation"].get<float>();
	setRotation(rotation);

	return true;
}
