#include "GameSystem.h"
#include <conio.h>
#include <iostream>


GameSystem::GameSystem(string levelFileName)
{
	_player.init(1, 100, 10, 10, 0);

	_level.load(levelFileName, _player);

	system("PAUSE");

}

void GameSystem::playGame()
{

	bool isDone = false;

	while (isDone != true) {
		_level.print();
		playerMove();
		_level.updateEnemies(_player);
		
	}

}
void GameSystem::playerMove()
{
	char input;
	printf("Enter To Move: (w/a/s/d) ");
	input = _getch();

	_level.movePlayer(input, _player);

}