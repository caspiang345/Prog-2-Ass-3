#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Object.h"
#include "Room.h"
#include <map>

class Guard;

class Player :public Object
{
public:
	void update(Player& player, std::map<Room::Name, Room>& dungeonMap, Guard& guard) override;

	bool getKeyStatus();
	void changeKeyStatus(Player& player, Room& currentRoom);
	void getKey(Player& player);
	std::string roomNameToString(const Room::Name rn);

	int getHealth();
	Room::Name getCurrentRoom() override;
	Room::Direction getAction();
private:
	bool changeGameState(Room::Direction action, Player& player, std::map<Room::Name, Room>& dungeonMap);
	void displayIllegalMove(const Player& player, Room::Direction action);


	int health{ 10 };
	bool hasKey{ false };
};

#endif // !PLAYER_H