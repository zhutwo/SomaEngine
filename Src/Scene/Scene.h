#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "SomaStd.h"
#include "SceneNode.h"

class Scene
{
protected:
	SceneNode 			m_Root;
public:
	Scene();
	~Scene();

	bool				AttachChild(SceneNodePtr child);
	SceneNodePtr		DetachChild(const SceneNode& node);

	void				Update(sf::Time dt);
	void				Render(sf::RenderTarget& target) const;
};