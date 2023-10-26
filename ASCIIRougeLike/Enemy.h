#pragma once
#include <string>

using namespace std;


class Enemy
{
public:
	Enemy(string name, char tile, int level, int attack, int defense, int health, int xp);

	//setter
	void setPosition(int x, int y);

	//getters
	void getPosition(int &x, int &y);
	string getName() { return _name; }
	char getTile() { return _tile; }

	int attack();
	int takeDamage(int attack);

	char getMove(int playerX, int playerY);

private:
	string _name;
	char _tile;

	int _level;
	int _attack;
	int _defense;
	int _health;
	int _experienceValue;

	//position
	int _x;
	int _y;


};

