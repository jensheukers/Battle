#include <entity.h>

#include "components/movementcomponent.h"

class Player : public Entity {
public:
	Player(ControlScheme& scheme);
};