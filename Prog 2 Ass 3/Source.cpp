#include<iostream>
#include<vector>
#include<map>
#include<random>
#include<algorithm>
#include <fstream>
#include "Room.h"
#include "Player.h"
#include "Guard.h"

//Bigger map
//guard chasing.
//find key and exit.
//bonus:guard moves towards player.

/* GUI Functions */

void splashScreen();


/* Engine Functions*/
std::map<Room::Name, Room> buildMap();
void randomizeKey(std::map<Room::Name, Room>& dungeonMap);
bool gameIsNotDone(Player player, Guard guard);
void displayGameDone(Player player, Guard guard, const std::map<Room::Name, Room>& dungeonMap);

int main() {

	/*Splash Screen*/
	system("CLR");
	splashScreen();

	/*set up game*/
	std::map<Room::Name, Room> dungeonMap{ buildMap() };
	Player player;
	Guard guard;

	/*Until Game Termination Condition Do: */
	while (gameIsNotDone(player, guard))
	{
		/*Display Game State*/
		system("CLS");
		std::cout << "P:" << (int)player.getCurrentRoom() << std::endl;
		std::cout << "G:" << (int)guard.getCurrentRoom() << std::endl;
		player.update(player, dungeonMap, guard);
		guard.update(player, dungeonMap, guard);
	}

	/*Display Termination Game State*/
	displayGameDone(player, guard, dungeonMap);

	return 0;

}


std::map<Room::Name, Room> buildMap()
{
	//enum class Name { cell, gate, armory, jailers, exit };
	std::map<Room::Name, Room> dungeonMap;
	std::ifstream fin;
	fin.open("dungeonLayout.txt");

	int name{ 0 };
	int numDoors{ 0 };
	while (name < (int)Room::Name::numHallwayRooms - 1)
	{
		fin >> name >> numDoors;
		for (int i{ 0 }; i < numDoors; i++)
			{
				int direction;
				int room;
				fin >> direction >> room;
				Room dungeonRoom = dungeonMap[(Room::Name)name];

				dungeonMap[(Room::Name)name].addDoor((Room::Direction)direction, (Room::Name)room);
			}
			name++;
		}

		randomizeKey(dungeonMap);

	return dungeonMap;
}

void randomizeKey(std::map<Room::Name, Room>& dungeonMap)
{
	std::bernoulli_distribution closetVsPantry(.5);
	std::default_random_engine engine;
	if (closetVsPantry(engine))
	{
		dungeonMap[Room::Name::closet].dropKey(dungeonMap.at(Room::Name::closet));
	}
	else
	{
		dungeonMap[Room::Name::pantry].dropKey(dungeonMap.at(Room::Name::pantry));
	}
}

void clearConsole() {
	system("cls");
}

void pauseConsole() {
	system("PAUSE");
}

void splashScreen() {
	std::cout << "DUNGEON ADVENTURE" << std::endl;
	std::cout << std::endl;
	std::cout << "Your name here (2020)" << std::endl;
	std::cout << "CPSC 2376, Programming II, Level 1 Quest" << std::endl;
	std::cout << "UA Little Rock, Computer Science Dept." << std::endl;
	std::cout << std::endl;
	std::cout << "INSTRUCTIONS:" << std::endl;
	std::cout << std::endl;
	std::cout << "Find the key and get out of the dungeon!" << std::endl;
	std::cout << std::endl;
	std::cout << "        (North)          " << std::endl;
	std::cout << "           w             " << std::endl;
	std::cout << "           |             " << std::endl;
	std::cout << "(West) a --+-- d (East)  " << std::endl;
	std::cout << "           |             " << std::endl;
	std::cout << "           s             " << std::endl;
	std::cout << "        (South)          " << std::endl;
	std::cout << std::endl;
	pauseConsole();
}


void displayGameDone(Player player, Guard guard, const std::map<Room::Name, Room>& dungeonMap)
{

	clearConsole();
	if (player.getHealth() > 0)
	{
		if (player.getCurrentRoom() == Room::Name::exit)
		{
			std::cout << "You found the key and escaped!" << std::endl;
		}
		else if (player.getCurrentRoom() == guard.getCurrentRoom())
		{
			std::cout << "The guard caught you and you are thrown back in your cell!" << std::endl;
		}
	}
	else
	{
		std::cout << "YOU DIED...RIP." << std::endl;
	}

	std::cout << std::endl;
	pauseConsole();
}



//Check the end-of-game conditions.  If the player is out
//of health or the player has reached the exit
//then the game is over.
bool gameIsNotDone(Player player, Guard guard)
{
	return !(
		player.getHealth() <= 0
		|| player.getCurrentRoom() == Room::Name::exit
		|| player.getCurrentRoom() == guard.getCurrentRoom()
		);
}