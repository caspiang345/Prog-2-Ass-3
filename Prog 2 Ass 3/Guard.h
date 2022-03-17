#ifndef GUARD_H
#define GUARD_H
#include "Object.h"
#include "Room.h"
#include <random>
#include <map>

class Guard : public Object
{
public:
	Guard();
	void update(Player& player, std::map<Room::Name, Room>& dungeonMap, Guard& guard) override;
	Room::Name getCurrentRoom() override;

	bool getClockwise();
	void setNewRoom(Guard& guard);
	void changeRoomDirection(Guard& guard);
private:
	bool clockwise{ true };
};

#endif // !GUARD_H