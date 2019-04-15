#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Components/Rigidbody.h"
#include "Components/AudioSource.h"
#include "Components/BoxCollider.h"

GameObjectFactory::GameObjectFactory(void)
{
	m_lastGameObjectId = INVALID_GAMEOBJECT_ID;

	//m_componentFactory.Register<TransformComponent>(Component::GetIdFromName(TransformComponent::g_Name));
	//m_componentFactory.Register<SpriteRenderer>(Component::GetIdFromName(SpriteRenderer::g_Name));
	//m_componentFactory.Register<AudioSource>(Component::GetIdFromName(AudioSource::g_Name));
	//m_componentFactory.Register<Rigidbody>(Component::GetIdFromName(Rigidbody::g_Name));
	//m_componentFactory.Register<BoxCollider>(Component::GetIdFromName(BoxCollider::g_Name));
}

SharedGameObjectPtr GameObjectFactory::CreateGameObject(Json data)
{
	SharedGameObjectPtr pGameObject;
	if (!pGameObject->Init(data))
	{
		//GCC_ERROR("Failed to initialize actor: " + std::string(actorResource));
		return SharedGameObjectPtr();
	}

	Json componentList = data["components"];

	for (auto &componentData : componentList)
	{
		SharedComponentPtr pComponent(VCreateComponent(componentData));
		if (pComponent)
		{
			pGameObject->AddComponent(pComponent);
			pComponent->SetParent(pGameObject);
		}
		else
		{
			// abort on error
			return SharedGameObjectPtr();
		}
	}

	//bool initialTransformSet = false;
	//transform init handled on gameobject init

	Json childList = data["children"];

	for (auto &childData : childList)
	{
		auto pChild = CreateGameObject(childData);
		pGameObject->AttachChild(pChild);
	}

	return pGameObject;
}

SharedComponentPtr GameObjectFactory::VCreateComponent(Json data)
{
	std::string name = data["name"].get<std::string>();
	SharedComponentPtr pComponent(m_componentFactory.Create(Component::GetIdFromName(name)));

	// initialize the component if we found one
	if (pComponent)
	{
		if (!pComponent->VInit(data))
		{
			//GCC_ERROR("Component failed to initialize: " + std::string(name));
			return SharedComponentPtr();
		}
	}
	else
	{
		//GCC_ERROR("Couldn't find GameObjectComponent named " + std::string(name));
		return SharedComponentPtr();  // fail
	}

	// pComponent will be NULL if the component wasn't found.  This isn't necessarily an error since you might have a 
	// custom CreateComponent() function in a sub class.
	return pComponent;
}

/*
SharedGameObjectPtr GameObjectFactory::CreateGameObject(const char* actorResource, TiXmlElement *overrides, const sf::Transformable *pInitialTransform, const GameObjectId serversGameObjectId)
{
	// Grab the root XML node
	TiXmlElement* pRoot = XmlResourceLoader::LoadAndReturnRootXmlElement(actorResource);
	if (!pRoot)
	{
		//GCC_ERROR("Failed to create actor from resource: " + std::string(actorResource));
		return SharedGameObjectPtr();
	}

	// create the actor instance
	GameObjectId nextGameObjectId = serversGameObjectId;
	if (nextGameObjectId == INVALID_GAMEOBJECT_ID)
	{
		nextGameObjectId = GetNextGameObjectId();
	}
	SharedGameObjectPtr pGameObject(new GameObject(nextGameObjectId));
	if (!pGameObject->Init(pRoot))
	{
		//GCC_ERROR("Failed to initialize actor: " + std::string(actorResource));
		return SharedGameObjectPtr();
	}

	bool initialTransformSet = false;

	// Loop through each child element and load the component
	for (TiXmlElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
	{
		SharedComponentPtr pComponent(VCreateComponent(pNode));
		if (pComponent)
		{
			pGameObject->AddComponent(pComponent);
			pComponent->SetOwner(pGameObject);
		}
		else
		{
			// If an error occurs, we kill the actor and bail.  We could keep going, but the actor is will only be
			// partially complete so it's not worth it.  Note that the pGameObject instance will be destroyed because it
			// will fall out of scope with nothing else pointing to it.
			return SharedGameObjectPtr();
		}
	}

	// This is a bit of a hack to get the initial transform of the transform component set before the
	// other components (like PhysicsComponent) read it.
	std::shared_ptr<TransformComponent> pTransformComponent = std::shared_ptr<TransformComponent>(pGameObject->GetComponent<TransformComponent>(TransformComponent::g_Name));
	if (pInitialTransform && pTransformComponent)
	{
		pTransformComponent->setPosition(pInitialTransform->getPosition());
	}

	// Now that the actor has been fully created, run the post init phase
	pGameObject->PostInit();

	return pGameObject;
}
*/