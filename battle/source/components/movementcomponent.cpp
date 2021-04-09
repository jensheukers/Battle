#include "movementcomponent.h"

#include <debug.h>

#include <entity.h>
#include <components/rigidbody.h>
#include <components/animator.h>

void MovementComponent::SetAnimationState(std::string name) {
	if (!GetOwner()->HasComponent<Animator>()) return;

	Animation* animation = GetOwner()->GetComponent<Animator>()->SetActiveAnimation(name);
	
	if (!animation->Mirrored() && this->direction == Direction::Left) {
		animation->Mirror();
	}
	else if (animation->Mirrored() && this->direction == Direction::Right) {
		animation->Mirror();
	}
}

MovementComponent::MovementComponent() {
	direction = Direction::Right;
}

void MovementComponent::BeginPlay() {
	if (!(this->rigidBody = GetOwner()->GetComponent<RigidBody>())) {
		Debug::Log("WARNING: MovementComponent added BEFORE rigidbody, Rigidbody should always be added before MovementComponent");
	}
}

void MovementComponent::Update() {
	this->SetAnimationState("Idle");

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

	this->SetAnimationState("Walk");
}

void MovementComponent::StepRight(float speed) {
	if (rigidBody->RightCastPositive()) return;
	rigidBody->SetVelocity(Vec2((float)speed, rigidBody->GetVelocity().y));
	this->direction = Direction::Right;

	this->SetAnimationState("Walk");
}

void MovementComponent::Jump(float force) {
	if (!rigidBody->DownCastPositive()) return;
	rigidBody->AddForce(Vec2(0, -force));
	this->direction = Direction::Up;
}

Direction MovementComponent::GetDirection() {
	return this->direction;
}