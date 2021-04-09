#include "player.h"

#include <components/sprite.h>

#include <components/rigidbody.h>
#include <components/collider.h>
#include <components/animator.h>

Player::Player(ControlScheme& scheme) {
	this->localScale = Vec2(64, 64);

	this->AddComponent<BoxCollider>();
	this->AddComponent<RigidBody>();
	this->AddComponent<MovementComponent>();
	this->AddComponent<Sprite>();

	this->AddComponent<Animator>();


	this->GetComponent<Sprite>()->SetTexture(TextureLoader::LoadTarga("res/character/character.tga"));
	this->GetComponent<Animator>()->AddAnimation("res/character/walk.animation");
	this->GetComponent<Animator>()->AddAnimation("res/character/punch.animation");

	this->GetComponent<MovementComponent>()->controlScheme = scheme;
}