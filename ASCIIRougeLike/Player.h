#pragma once


class Player
{

public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);

	int attack();

	//setter
	void setPosition(int x, int y);

	void addExperience(int experience);

	//getters
	void getPosition(int &x, int &y);

	int takeDamage(int attack);

private:
	//properties
	int _level;
	int _health;
	int _attack;
	int _defense;
	int _experience;

	//position
	int _x;
	int _y;


};

