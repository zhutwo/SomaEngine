#pragma once
#include "SomaStd.h"

class SceneNode;

typedef std::vector<std::shared_ptr<SceneNode>> SceneNodeList;

class SceneNode
{
	friend class Scene;

protected:
	
	SceneNodeList		m_Children;
	SceneNode			*m_pParent;
};