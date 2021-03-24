/* Gamestate for battle, handles all background game data*/
#include <scenemanager.h>

class GameState {
private:
	StringVector levels;
	Scene* currentLevel;

	unsigned _curLevIndex;

	Scene* ReadScene(std::string path);
public:
	Delegate onLevelFinishedEvent;
	Delegate onLevelStartEvent;

	GameState(StringVector levels);

	void NextLevel();

	void SetLevel(int index);

	Scene* GetCurrentLevel();

	void StartGameplay();
};