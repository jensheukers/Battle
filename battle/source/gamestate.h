/* Gamestate for battle, handles all background game data*/
#include <scenemanager.h>

#include "player.h"

class GameState {
private:
	StringVector levels;
	Scene* currentLevel;

	unsigned _curLevIndex;
	
	std::vector<Player*> players;

	Scene* ReadScene(std::string path);

	Player* SpawnPlayer();
public:
	Delegate onLevelFinishedEvent;
	Delegate onLevelStartEvent;

	GameState(StringVector levels);

	void NextLevel();

	void SetLevel(int index);

	Scene* GetCurrentLevel();

	void StartGameplay();
};