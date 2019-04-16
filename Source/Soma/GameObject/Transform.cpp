#include "Transform.h"

std::string TransformComponent::g_Name = "TransformComponent";

TransformComponent::TransformComponent()
{
}

bool TransformComponent::VInit(Json data)
{
	Vector2 position;
	position.x = 100.0f * data["localPosition"]["x"].get<float>();
	position.y = -100.0f * data["localPosition"]["y"].get<float>();
	setPosition(position);

	Vector2 scale;
	scale.x = data["localScale"]["x"].get<float>();
	scale.y = data["localScale"]["y"].get<float>();
	setScale(scale);

	float rotation = data["rotation"].get<float>();
	setRotation(rotation);
	
	return true;
}
