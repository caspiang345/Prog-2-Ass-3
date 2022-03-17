#include "Guard.h"

Guard::Guard()
{
	std::uniform_int_distribution<int> dist(0, 7);
	std::default_random_engine engine;
	int startingRoomInt = dist(engine);
	currentRoom = (Room::Name)startingRoomInt;
}

void Guard::update(Player& player, std::map<Room::Name, Room>& dungeonMap, Guard& guard)
{
	guard.changeRoomDirection(guard);
	guard.setNewRoom(guard);

}

Room::Name Guard::getCurrentRoom()
{
	return currentRoom;
}

bool Guard::getClockwise()
{
	return clockwise;
}

void Guard::setNewRoom(Guard& guard)
{
	if (guard.getClockwise() == true) {
		if (guard.getCurrentRoom() == Room::Name::W) {
			currentRoom = Room::Name::NW;
		}
		else {
			int currentRoomNumber = (int)currentRoom;
			currentRoomNumber += 1;
			currentRoom = (Room::Name)currentRoomNumber;
		}
	}
	else {
		if (guard.getCurrentRoom() == Room::Name::NW) {
			currentRoom = Room::Name::W;
		}
		else {
			int currentRoomNumber = (int)currentRoom;
			currentRoomNumber -= 1;
			currentRoom = (Room::Name)currentRoomNumber;
		}
	}
}

void Guard::changeRoomDirection(Guard& guard)
{
	std::default_random_engine engine;
	std::uniform_int_distribution<int> dist(0, 1);
	int clockOrAntiClock = dist(engine);

	if (clockOrAntiClock == 0) {
		clockwise = true;
	}
	else {
		clockwise = false;
	}
}
