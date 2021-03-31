// Main entry point.
//
// Copyright (C) Jens Heukers - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jens Heukers, March 2021
#include <core.h>

#include "source/gamestate.h"

int main(int argc, char * argv[]) {
	Core::Initialize(argc, argv, Vec2(1280, 720), "Battle");
	
	GameState* _gs = new GameState({ "res/scenes/test.scene" });
	_gs->NextLevel();

	while (Core::IsActive()) {
		Core::Update(); // Handle updates for engine
	}

	return 0; // return succes
}