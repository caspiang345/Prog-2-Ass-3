#ifndef OBJECT_H
#define OBJECT_H
#include<random>
#include <map>
#include "Room.h"

class Guard;
class Player;

class Object
{
public:
	virtual void update(Player& player, std::map<Room::Name, Room>& dungeonMap, Guard& guard) = 0;
	static std::random_device seed;
	static std::default_random_engine engine;

	virtual Room::Name getCurrentRoom() = 0;
protected:
	Room::Name currentRoom{ Room::Name::cell };
};
#endif // !OBJECT_H