// Main entry point.
//
// Copyright (C) Jens Heukers - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jens Heukers, March 2021
#include <core.h>
#include <scenemanager.h>

#include <components/collider.h>
#include <components/rigidbody.h>

#include "source/components/movementcomponent.h"
#include "source/components/healthcomponent.h"

int main(int argc, char * argv[]) {
	Core::Initialize(argc, argv, Vec2(1280, 720), "Battle");
	
	SceneManager::ReadFromFileAndSwap("res/test.scene");

	Entity* testEntity = new Entity();
	testEntity->localScale = Vec2(32, 32);

	testEntity->AddComponent<Sprite>()->SetTexture(TextureLoader::LoadTarga("res/placeholder.tga"));
	testEntity->AddComponent<Collider>();
	testEntity->AddComponent<RigidBody>();
	testEntity->AddComponent<MovementComponent>();
	testEntity->AddComponent<HealthComponent>();

	SceneManager::GetActiveScene()->AddChild(testEntity);

	while (Core::IsActive()) {
		Core::Update(); // Handle updates for engine
	}

	return 0; // return succes
}