#include "gamestate.h"
#include <parser.h>

Scene* GameState::ReadScene(std::string path) {
	Parser* parser = new Parser(path, true);
	Scene* scene = parser->ReadSceneFromFile();
	delete parser;

	return scene;
}

Player* GameState::SpawnPlayer(ControlScheme& scheme) {
	Player* player = new Player(scheme);
	SceneManager::GetActiveScene()->AddChild(player);

	return player;
}

GameState::GameState(StringVector levels) {
	this->levels = levels;
	this->_curLevIndex = -1;

	this->onLevelStartEvent.AddLambda([=]() {
		if (SceneManager::GetActiveScene()->GetKeyValue("BeginGameplay") == "True") {
			//Spawn Players
			int amountPlayers = std::stoi(SceneManager::GetActiveScene()->GetKeyValue("AmountPlayers"));

			for (int i = 0; i < amountPlayers; i++) {
				players.push_back(SpawnPlayer(controlSchemes[i]));
			}
		}
	});

	//Cleanup
	this->onLevelFinishedEvent.AddLambda([=]() {
		for (size_t i = 0; i < players.size(); i++) {
			delete players[i];
			players.erase(players.begin() + i);
		}
	});

	//Player 1
	this->controlSchemes.push_back(ControlScheme());
	//Player 2
	this->controlSchemes.push_back(ControlScheme(KEYCODE_LEFT, KEYCODE_RIGHT, KEYCODE_KP_ENTER));
}

void GameState::NextLevel() {
	if (this->_curLevIndex + 1 != levels.size()) {
		this->_curLevIndex += 1;
		this->currentLevel = this->ReadScene(this->levels[this->_curLevIndex]);
		SceneManager::SetActiveScene(this->currentLevel);
	}

	//When done loading start Gameplay
	this->StartGameplay();
}

void GameState::SetLevel(int index) {
	if (index > -1 && index < levels.size()) {
		this->_curLevIndex = index;
		this->currentLevel = this->ReadScene(this->levels[this->_curLevIndex]);
		SceneManager::SetActiveScene(this->currentLevel);
	}

	//When done loading start Gameplay
	this->StartGameplay();
}

Scene* GameState::GetCurrentLevel() {
	return this->currentLevel;
}

void GameState::StartGameplay() {
	this->onLevelStartEvent.Execute(); //exec delegates
}