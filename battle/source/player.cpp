#include "player.h"

#include "components/movementcomponent.h"
#include <components/sprite.h>

#include "components/rigidbody.h"
#include "components/collider.h"

Player::Player() {
	this->localScale = Vec2(32, 32);

	this->AddComponent<BoxCollider>();
	this->AddComponent<RigidBody>();
	this->AddComponent<MovementComponent>();
	this->AddComponent<Sprite>();

	this->GetComponent<Sprite>()->SetTexture(TextureLoader::LoadTarga("res/placeholder.tga"));
}