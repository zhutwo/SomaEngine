#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "SomaStd.h"

class SceneNode;

typedef std::unique_ptr<SceneNode> SceneNodePtr;
typedef std::vector<SceneNodePtr> SceneNodeList;

/*
SceneNode

Class that provides scene graph data structure functionality for the GameObject class
To be inherited by GameObject
*/

class SceneNode
{
	friend class Scene;

protected:
	SceneNodeList		m_Children;
	SceneNode*			m_pParent;

public:
	SceneNode();
	~SceneNode();

	bool				AttachChild(SceneNodePtr child);
	SceneNodePtr		DetachChild(const SceneNode& node);

	void				Update(sf::Time dt);
	void				UpdateSelf(sf::Time dt);
	void				UpdateChildren(sf::Time dt);

	void				Render(sf::RenderTarget& target) const;
	void				RenderSelf(sf::RenderTarget& target) const;
	void				RenderChildren(sf::RenderTarget& target) const;
};