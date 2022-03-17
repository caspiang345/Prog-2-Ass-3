#include "Room.h"
#include "Player.h"

Room::Name Room::getName()
{
	return name;
}

bool Room::doesRoomHaveKey()
{
	return hasKey;
}

Room::Direction Room::getDoorwayDirection(Room r)
{
	for (auto i = r.doorways.begin(); i != doorways.end(); i++) {
		std::pair<Room::Direction, Room::Name>pair = *i;
		if (pair.second == r.getName()) {
			return pair.first;
		}
	}

	return Room::Direction::none;
}

std::map<Room::Direction, Room::Name> Room::getDoorways(Room r)
{
	std::map<Room::Direction, Room::Name>map;
	map.at(r.getDoorwayDirection(r)) = r.getName();
	return map;
}


void Room::exitRoom(Player player)
{
	auto it = doorways.find(player.getAction());
	if (it != doorways.end()) {
		
	}
	else {
		
	}
}

void Room::addDoor(Room::Direction direction, Room::Name name)
{
	doorways.at(direction) = name;
}

void Room::pickupKey(Room& currentRoom)
{
	if (currentRoom.doesRoomHaveKey() == true) {
		hasKey = false;
	}
}

void Room::dropKey(Room& currentRoom)
{
	int roomWithKey{};
	std::default_random_engine engine;
	std::uniform_int_distribution<int> randomRoom(-2, -1);
	roomWithKey = randomRoom(engine);
	currentRoom.name = (Room::Name)roomWithKey;
	currentRoom.hasKey = true;
}
