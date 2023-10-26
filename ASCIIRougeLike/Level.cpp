#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

Level::Level()
{

}

void Level::load(string fileName, Player &player)
{

	//loads the level
	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);
	}

	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();

	//process the level

	char tile;
	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '@': //player
				player.setPosition(j, i);
				break;
			case 'S': //snake
				_enemies.push_back(Enemy("Snake", tile, 1, 3, 1, 10, 50));
				_enemies.back().setPosition(j, i);
				break;
			case 'g': //goblin
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setPosition(j, i);
				break;
			case 'O': //ogre
				_enemies.push_back(Enemy("Ogre", tile, 4, 20, 20, 200, 500));
				_enemies.back().setPosition(j, i);
				break;
			case 'B': //bandit
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 50, 250));
				_enemies.back().setPosition(j, i);
				break;
			case 'D': //dragon
				_enemies.push_back(Enemy("Dragon", tile, 25, 250, 250, 500, 10000));
				_enemies.back().setPosition(j, i);
				break;

			}
		}
	}

}

void Level::print()
{
	cout << string(100, '\n');

	for (int i = 0; i < _levelData.size(); i++) {
		printf("%s\n", _levelData[i].c_str());
	}
	printf("\n");
}

void Level::movePlayer(char input, Player &player)
{

	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);

	switch (input) {
		//up
	case 'w':
	case 'W':
		processPlayerMove(player, playerX, playerY - 1);
	break;
		//down
	case's':
	case'S':

		processPlayerMove(player, playerX, playerY + 1);
		break;
		//left
	case 'a':
	case 'A':
		processPlayerMove(player, playerX - 1, playerY);
		break;
		//right
	case'd':
	case'D':
		processPlayerMove(player, playerX + 1, playerY);
		break;
	default:
		printf("INVAILD INPUT!\n");
		system("PAUSE");
		break;
	}


}

void Level::updateEnemies(Player &player)
{
	char aiMove;

	int playerX;
	int playerY;
	int enemyX;
	int enemyY;


	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerX, playerY);
		_enemies[i].getPosition(enemyX, enemyY);
		switch (aiMove) {
			//up
		case 'w':
			processEnemyMove(player, i, enemyX, enemyY - 1);
			break;
			//down
		case's':
			processEnemyMove(player, i, enemyX, enemyY + 1);
			break;
			//left
		case 'a':
			processEnemyMove(player, i, enemyX - 1, enemyY);
			break;
			//right
		case'd':
			processEnemyMove(player, i, enemyX + 1, enemyY);
			break;
		}

	}
}

char Level::getTile(int x, int y)
{
	return _levelData[y][x];
}

void Level::setTile(int x, int y, char tile)
{
	_levelData[y][x] = tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY)
{
	int playerX;
	int playerY;

	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);
	
	switch (moveTile) {
	case '*':
		player.setPosition(targetX, targetY);
		setTile(playerX, playerY, '*');
		setTile(targetX, targetY, '@');
		break;
	case '#':
		break;
	default:
		battleEnemy(player, targetX, targetY);
		break;
	}

}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY)
{
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;

	_enemies[enemyIndex].getPosition(enemyX, enemyY);
	player.getPosition(playerX, playerY);

	char moveTile = getTile(targetX, targetY);

	switch (moveTile) {
	case '*':
		_enemies[enemyIndex].setPosition(targetX, targetY);
		setTile(enemyX, enemyY, '*');
		setTile(targetX, targetY, _enemies[enemyIndex].getTile());
		break;
	case '@':
		battleEnemy(player, enemyX, enemyY);
		break;
	case '#':
		break;
	default:
		break;
	}


}

void Level::battleEnemy(Player &player, int targetX, int targetY)
{
	int enemyY;
	int enemyX;
	int playerX;
	int playerY;
	int attackRoll;
	int attackResult;
	string enemyName;

	player.getPosition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {

		_enemies[i].getPosition(enemyX, enemyY);
		enemyName = _enemies[i].getName();
		
		if (targetX == enemyX && targetY == enemyY) {

			//battle
			attackRoll = player.attack();

			printf("\nPlayer attacked %s with a roll of %d\n", enemyName.c_str(), attackRoll);

			attackResult = _enemies[i].takeDamage(attackRoll);

			if (attackResult != 0) {
				setTile(targetX, targetY, '*');
				print();
				printf("Enemy Died!\n");

				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

				system("PAUSE");
				player.addExperience(attackResult);
				
				return;
			}

			attackRoll = _enemies[i].attack();
			printf("\n%s attacked player with a roll of %d\n", enemyName.c_str(), attackRoll);

			attackResult = player.takeDamage(attackRoll);


			if (attackResult != 0) {
				setTile(playerX, playerY, 'x');
				print();
				printf("You Died!\n");
				system("PAUSE");

				exit(0);
			}
			system("PAUSE");

			return;

		}
	}
}