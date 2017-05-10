
#include "Engine\IGameEngine.h"
#include "Engine\GameEngine.h"

int main(int, char**){

	Engine::IGameEngine* gameEngine = new Engine::GameEngine();

	int result = gameEngine->Run();

	delete gameEngine;
	gameEngine = nullptr;

#ifdef _DEBUG
	system("pause");
#endif // DEBUG


	return result;
}