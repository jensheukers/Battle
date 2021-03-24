#include "gamestate.h"
#include <parser.h>

Scene* GameState::ReadScene(std::string path) {
	Parser* parser = new Parser(path, true);
	Scene* scene = parser->ReadSceneFromFile();
	delete parser;

	return scene;
}

GameState::GameState(StringVector levels) {
	this->levels = levels;
	this->_curLevIndex = 0;
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