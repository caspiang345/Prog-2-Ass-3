#include "Player.h"

void Player::update(Player& player, std::map<Room::Name, Room>& dungeonMap, Guard& guard) {
	std::cout << "View:   ";
	std::string currentRoom = player.roomNameToString(player.getCurrentRoom());
	std::cout << currentRoom << std::endl;
	std::cout << "Health: " << player.health << std::endl;
	std::cout << "Equip:  ";
	if (player.hasKey) {
		std::cout << "1 jailer's key";
	}
	std::cout << std::endl;
	Room::Direction d = player.getAction();
	if (player.changeGameState(d, player, dungeonMap) == true) {

	}
	else {
		player.displayIllegalMove(player, d);
	}
}

bool Player::getKeyStatus()
{
	return hasKey;
}

void Player::changeKeyStatus(Player& player, Room& currentRoom) {
	if (currentRoom.doesRoomHaveKey() == true && player.getCurrentRoom() == currentRoom.getName()) {
		currentRoom.pickupKey(currentRoom);
		player.getKey(player);
	}
}

void Player::getKey(Player& player) {
	hasKey = true;
}

int Player::getHealth()
{
	return health;
}

Room::Name Player::getCurrentRoom()
{
	return currentRoom;
}

bool Player::changeGameState(Room::Direction action, Player& player, std::map<Room::Name, Room>& dungeonMap)
{
	Room playerCurrentRoom = dungeonMap.at(player.currentRoom);
	//pick up the key if it is in this room.
	if (playerCurrentRoom.doesRoomHaveKey() == true)
	{
		player.hasKey = true;
		playerCurrentRoom.dropKey(playerCurrentRoom);
	}

	//if we are trying to go to the exit, but we don't have the key, it is illegal.
	if (player.currentRoom == Room::Name::gate && !player.hasKey && action == Room::Direction::E)
	{
		return false;
	}
	//check for door;
	Room::Name roomName = playerCurrentRoom.getDoorways(playerCurrentRoom).at(action);
	auto iter = std::find_if(dungeonMap.at(roomName).getDoorways(playerCurrentRoom).begin(), dungeonMap.at(roomName).getDoorways(playerCurrentRoom).end(), [=](std::pair<const Room::Direction, Room::Name> p)
		{
			return (p.first == action);
		});

	if (iter != dungeonMap.at(roomName).getDoorways(playerCurrentRoom).end())
	{
		//found a door in the direction we are trying to go, so go that way.
		std::pair <const Room::Direction, Room::Name> p = *iter;
		player.currentRoom = p.second;
		player.health--;
		return true;
	}

	return false; //if there is not a connected room in that direction, it is illegal.
}

void Player::displayIllegalMove(const Player& player, Room::Direction action)
{
	if (player.currentRoom == Room::Name::gate && !player.hasKey && action == Room::Direction::E)
	{
		std::cout << "The door is locked. \n Perhaps if you had a key???" << std::endl;
	}
	else
	{
		std::cout << "You cannot go that way." << std::endl;
	}
	std::cout << std::endl;
}

Room::Direction Player::getAction()
{
	char action;
	std::cout << std::endl;
	std::cout << "Select action: ";
	std::cin >> action;
	switch (action)
	{
	case 'w':
		return Room::Direction::N;
		break;
	case 'a':
		return Room::Direction::W;
		break;
	case 'd':
		return Room::Direction::E;
		break;
	case 's':
		return Room::Direction::S;
		break;

	default:
		return Room::Direction::none;
		break;
	}
}

std::string Player::roomNameToString(Room::Name rn) {
	std::string roomName{};
	if (rn == Room::Name::cell) {
		roomName = "cell";
	}
	else if (rn == Room::Name::closet) {
		roomName = "closet";
	}
	else if (rn == Room::Name::E) {
		roomName = "E";
	}
	else if (rn == Room::Name::exit) {
		roomName = "exit";
	}
	else if (rn == Room::Name::gate) {
		roomName = "gate";
	}
	else if (rn == Room::Name::NE) {
		roomName = "NE";
	}
	else if (rn == Room::Name::NW) {
		roomName = "NW";
	}
	else if (rn == Room::Name::pantry) {
		roomName = "pantry";
	}
	else if (rn == Room::Name::S) {
		roomName = "S";
	}
	else if (rn == Room::Name::SE) {
		roomName = "SE";
	}
	else if (rn == Room::Name::SW) {
		roomName = "SW";
	}
	else if (rn == Room::Name::W) {
		roomName = "W";
	}

	return roomName;
}