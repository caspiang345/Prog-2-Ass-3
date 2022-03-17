#ifndef ROOM_H
#define ROOM_H
#include<map>
#include <iostream>
#include <tuple>
#include <random>
#include <algorithm>

class Player;

class Room
{
public:
	enum class Name { exit = -4, cell, closet, pantry, NW, gate, NE, E, SE, S, SW, W, numHallwayRooms };
	enum class Direction { N, S, E, W, none };

	Room::Name getName();
	bool doesRoomHaveKey();
	Room::Direction getDoorwayDirection(Room r);
	std::map<Room::Direction, Room::Name> getDoorways(Room r);

	void exitRoom(Player player);
	void addDoor(Room::Direction direction, Room::Name name);
	void pickupKey(Room& currentRoom);
	void dropKey(Room& currentRoom);

private:
	Name name{ Name::NW };
	std::map<Direction, Name> doorways;
	bool hasKey{ false };

};




#endif // !ROOM_H