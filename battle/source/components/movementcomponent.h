//Movement component
#ifndef IQ_MOVEMENTCOMPONENT_H
#define IQ_MOVEMENTCOMPONENT_H

#include <component.h>
#include <math/vec2.h>

#include <input.h>

enum Direction {
	Up,
	Down,
	Left,
	Right
};

struct ControlScheme {
	int left;
	int right;
	int jump;
	int punch;

	ControlScheme(int left = KEYCODE_A, int right = KEYCODE_D, int jump = KEYCODE_SPACE, int punch = KEYCODE_F) {
		this->left = left;
		this->right = right;
		this->jump = jump;
		this->punch = punch;
	}
};

//Movement component requires a rigidbody on entity
class MovementComponent : public Component {
private:
	class RigidBody* rigidBody; // Rigidbody instance
	Direction direction;

	void SetAnimationState(std::string name);
public:
	ControlScheme controlScheme;

	float movementSpeed = 200.f;
	float jumpForce = 400.f;

	MovementComponent();

	void BeginPlay();

	void Update() override;

	void StepLeft(float speed);
	void StepRight(float speed);
	void Jump(float force);
	void Punch();

	Direction GetDirection();
};

#endif // !IQ_MOVEMENTCOMPONENT_H