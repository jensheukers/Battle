#include "player.h"

#include "components/movementcomponent.h"
#include <components/sprite.h>

Player::Player() {
	this->localScale = Vec2(32, 32);

	this->AddComponent<MovementComponent>();
	this->AddComponent<Sprite>();

	this->GetComponent<Sprite>()->SetTexture(TextureLoader::LoadTarga("res/textures/placeholder.tga"));
}