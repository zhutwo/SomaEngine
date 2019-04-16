#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Components/Rigidbody.h"
#include "Components/AudioSource.h"
#include "Components/BoxCollider.h"
#include "Components/PlayerController.h"
#include "Scripts/TargetScript.h"
#include "Scripts/BulletScript.h"
#include "../Physics/PhysicsEngine.h"

GameObjectFactory::GameObjectFactory(void)
{
	m_lastGameObjectId = INVALID_GAMEOBJECT_ID;

	m_componentFactory.Register<TransformComponent>(Component::GetIdFromName(TransformComponent::g_Name));
	m_componentFactory.Register<SpriteRenderer>(Component::GetIdFromName(SpriteRenderer::g_Name));
	m_componentFactory.Register<AudioSource>(Component::GetIdFromName(AudioSource::g_Name));
	m_componentFactory.Register<Rigidbody>(Component::GetIdFromName(Rigidbody::g_Name));
	m_componentFactory.Register<BoxCollider>(Component::GetIdFromName(BoxCollider::g_Name));
	m_componentFactory.Register<PlayerController>(Component::GetIdFromName(PlayerController::g_Name));
	m_componentFactory.Register<TargetScript>(Component::GetIdFromName(TargetScript::g_Name));
	m_componentFactory.Register<BulletScript>(Component::GetIdFromName(BulletScript::g_Name));
}

SharedGameObjectPtr GameObjectFactory::CreateGameObject(Json data)
{
	SharedGameObjectPtr pGameObject = std::make_shared<GameObject>();

	if (!pGameObject->Init(data))
	{
		Helper::Print("GameObject failed to init");
		//GCC_ERROR("Failed to initialize actor: " + std::string(actorResource));
		return SharedGameObjectPtr();
	}

	for (auto componentData : data["components"])
	{
		SharedComponentPtr pComponent(VCreateComponent(componentData));
		if (pComponent)
		{
			pGameObject->AddComponent(pComponent);
			pComponent->SetParent(pGameObject);
		}
		else
		{
			Helper::Print("GameObject components failed to init");
			return SharedGameObjectPtr();
		}
		if (pComponent->VGetName() == "Rigidbody")
		{
			PhysicsEngine::GetSingleton().AddRigidBody(std::static_pointer_cast<Rigidbody>(pComponent));
		}
	}
	//bool initialTransformSet = false;
	//transform init handled on gameobject init

	for (auto childData : data["children"])
	{
		auto pChild = CreateGameObject(childData);
		pGameObject->AttachChild(pChild);
	}

	return pGameObject;
}

SharedComponentPtr GameObjectFactory::VCreateComponent(Json data)
{
	std::string type = data["type"].get<std::string>();
	SharedComponentPtr pComponent(m_componentFactory.Create(Component::GetIdFromName(type)));
	// initialize the component if we found one
	if (pComponent)
	{
		if (!pComponent->VInit(data))
		{
			Helper::Print("Component failed to init");
			return SharedComponentPtr();
		}
	}
	else
	{
		Helper::Print("Component not found");
		return SharedComponentPtr();  // fail
	}
	// pComponent will be NULL if the component wasn't found.  This isn't necessarily an error since you might have a 
	// custom CreateComponent() function in a sub class.
	return pComponent;
}