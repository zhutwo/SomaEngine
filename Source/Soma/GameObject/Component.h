#pragma once

#include "SomaStd.h"
#include "GameObject.h"

typedef std::shared_ptr<Component> SharedComponentPtr;
typedef unsigned int ComponentId;

class Component
{
public:
	Component();
	~Component();
};