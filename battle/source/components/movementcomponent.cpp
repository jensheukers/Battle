#include "movementcomponent.h"

#include <debug.h>

#include <entity.h>
#include <components/rigidbody.h>

MovementComponent::MovementComponent() {
	direction = Direction::Right;
}

void MovementComponent::BeginPlay() {
	if (!(this->rigidBody = GetOwner()->GetComponent<RigidBody>())) {
		Debug::Log("WARNING: MovementComponent added BEFORE rigidbody, Rigidbody should always be added before MovementComponent");
	}
}

void MovementComponent::Update() {
	if (Input::GetKey(controlScheme.right)) {
		this->StepRight(movementSpeed);
	}

	if (Input::GetKey(controlScheme.left)) {
		this->StepLeft(movementSpeed);
	}

	if (Input::GetKeyDown(controlScheme.jump)) {
		this->Jump(jumpForce);
	}
}

void MovementComponent::StepLeft(float speed) {
	if (rigidBody->LeftCastPositive()) return;
	rigidBody->SetVelocity(Vec2(-(float)speed, rigidBody->GetVelocity().y));
	this->direction = Direction::Left;
}

void MovementComponent::StepRight(float speed) {
	if (rigidBody->RightCastPositive()) return;
	rigidBody->SetVelocity(Vec2((float)speed, rigidBody->GetVelocity().y));
	this->direction = Direction::Right;
}

void MovementComponent::Jump(float force) {
	if (!rigidBody->DownCastPositive()) return;
	rigidBody->AddForce(Vec2(0, -force));
	this->direction = Direction::Up;
}

Direction MovementComponent::GetDirection() {
	return this->direction;
}