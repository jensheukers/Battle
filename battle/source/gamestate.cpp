#include "gamestate.h"
#include <parser.h>

Scene* GameState::ReadScene(std::string path) {
	Parser* parser = new Parser(path, true);
	Scene* scene = parser->ReadSceneFromFile();
	delete parser;

	return scene;
}

Player* GameState::SpawnPlayer() {
	Player* player = new Player();
	SceneManager::GetActiveScene()->AddChild(player);

	return player;
}

GameState::GameState(StringVector levels) {
	this->levels = levels;
	this->_curLevIndex = -1;

	this->onLevelStartEvent.AddLambda([=]() {
		if (SceneManager::GetActiveScene()->GetKeyValue("BeginGameplay") == "True") {
			//Spawn Players
			players.push_back(SpawnPlayer());
		}
	});

	//Cleanup
	this->onLevelFinishedEvent.AddLambda([=]() {
		for (size_t i = 0; i < players.size(); i++) {
			delete players[i];
			players.erase(players.begin() + i);
		}
	});
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