// TileGrid.cpp

#include "stdafx.h"
#include "TileGrid.h"
#include "TileWall.h"
#include "TileFloor.h" 
#include "TileEmpty.h"

TileGrid::TileGrid() {

}

TileGrid::~TileGrid() {

}

void TileGrid::Init() {
	std::vector<std::vector<TileStatus>> tiles;
	SpawnRooms(tiles);
	ConnectRooms(tiles);

	m_tiles.resize(WORLDSIZE);
	for (unsigned int y = 0; y < m_tiles.size(); y++) {
		m_tiles.at(y).resize(WORLDSIZE);
		for (unsigned int x = 0; x < m_tiles.at(y).size(); x++) {
			switch (tiles.at(y).at(x)) {
			case UNBUILDABLE:
				m_tiles.at(y).at(x) = new TileWall(Position(x * TILESIZE, y * TILESIZE));
				break;

			case WALL:
				m_tiles.at(y).at(x) = new TileEmpty(Position(x * TILESIZE, y * TILESIZE));
				break;

			case CORRIDOR:
				m_tiles.at(y).at(x) = new TileFloor(Position(x * TILESIZE, y * TILESIZE));
				break;

			case ROOM:
				m_tiles.at(y).at(x) = new TileFloor(Position(x * TILESIZE, y * TILESIZE));
				break;

			case ROOMWALL:
				m_tiles.at(y).at(x) = new TileWall(Position(x * TILESIZE, y * TILESIZE));
				break;

			default:
				std::cout << "creation of tilegrid failed\n";
				break;
			}
		}
	}
}

bool TileGrid::IsWalkable(Position pos) {
	return m_tiles.at(pos.m_y / TILESIZE).at(pos.m_x / TILESIZE)->IsWalkable();
}

std::string TileGrid::IsType(Position pos) {
	return m_tiles.at(pos.m_y / TILESIZE).at(pos.m_x / TILESIZE)->IsType();
}

void TileGrid::Update() {
	for (unsigned int y = 0; y < m_tiles.size(); y++) {
		for (unsigned int x = 0; x < m_tiles.at(y).size(); x++) {
			m_tiles.at(y).at(x)->Update();
		}
	}
}

void TileGrid::Draw() {
	for (unsigned int y = 0; y < m_tiles.size(); y++) {
		for (unsigned int x = 0; x < m_tiles.at(y).size(); x++) {
			m_tiles.at(y).at(x)->Draw();
		}
	}
}

void TileGrid::SpawnRooms(std::vector<std::vector<TileStatus>> &tiles) {


	tiles.resize(WORLDSIZE);
	for (int y = 0; y < WORLDSIZE; y++) {
		tiles.at(y).resize(WORLDSIZE, WALL);
	}

	// level-sides are unbuildable
	for (int x = 0; x < WORLDSIZE; x++) {
		tiles.at(0).at(x) = UNBUILDABLE;
	}
	for (int y = 1; y < WORLDSIZE - 1; y++) {
		tiles.at(y).at(0) = UNBUILDABLE;
		tiles.at(y).at(WORLDSIZE - 1) = UNBUILDABLE;
	}
	for (int x = 0; x < WORLDSIZE; x++) {
		tiles.at(WORLDSIZE - 1).at(x) = UNBUILDABLE;
	}

	// Randomly choose how many rooms to place
	int numberOfRooms = (rand() % 20) + 20;

	// Start spawning rooms
	for (int room = 0; room < numberOfRooms; room++) {
		int roomSize = (rand() % 3) + 2;
		int tries = 0;
		bool success;

		// Try to place a room 10 times or until successful, whatever comes first
		do {
			success = true;

			int midX = (rand() % (WORLDSIZE - roomSize * 2 - 2)) + roomSize + 1;
			int midY = (rand() % (WORLDSIZE - roomSize * 2 - 2)) + roomSize + 1;


			for (int y = midY - roomSize; y <= midY + roomSize; y++) {
				for (int x = midX - roomSize; x <= midX + roomSize; x++) {
					if (tiles.at(y).at(x) != WALL) {
						success = false;
						break;
					}
				}
			}

			if (success) {

				//Make the corners of the room unbuildable
				tiles.at(midY - roomSize - 1).at(midX - roomSize - 1) = UNBUILDABLE;
				tiles.at(midY - roomSize - 1).at(midX + roomSize + 1) = UNBUILDABLE;
				tiles.at(midY + roomSize + 1).at(midX - roomSize - 1) = UNBUILDABLE;
				tiles.at(midY + roomSize + 1).at(midX + roomSize + 1) = UNBUILDABLE;

				//Make the walls
				//Northen and southern walls
				for (int x = midX - roomSize; x <= midX + roomSize; x++) {
					if (tiles.at(midY - roomSize - 1).at(x) != UNBUILDABLE) {
						tiles.at(midY - roomSize - 1).at(x) = ROOMWALL;
					}
					if (tiles.at(midY + roomSize + 1).at(x) != UNBUILDABLE) {
						tiles.at(midY + roomSize + 1).at(x) = ROOMWALL;
					}
				}

				//Side walls
				for (int y = midY - roomSize; y < midY + roomSize + 1; y++) {
					if (tiles.at(y).at(midX - roomSize - 1) != UNBUILDABLE) {
						tiles.at(y).at(midX - roomSize - 1) = ROOMWALL;
					}
					if (tiles.at(y).at(midX + roomSize + 1) != UNBUILDABLE) {
						tiles.at(y).at(midX + roomSize + 1) = ROOMWALL;
					}
				}

				//Room
				for (int y = midY - roomSize; y <= midY + roomSize; y++) {
					for (int x = midX - roomSize; x <= midX + roomSize; x++) {
						tiles.at(y).at(x) = ROOM;
					}
				}

				m_rooms.push_back(Room(midX, midY, roomSize));
				m_connected.push_back(false);
			}
			else {
				tries++;
			}
		} while (tries < 10 && !success);
	}

}

void TileGrid::ConnectRooms(std::vector<std::vector<TileStatus>> &tiles) {
	m_connected.at(0) = true;

	bool done = false;
	Direction direction;

	while (!done) {
		done = true;
		int fromRoom;
		int toRoom;
		do {
			fromRoom = rand() % m_rooms.size();
		} while (!m_connected.at(fromRoom));

		do {
			toRoom = rand() % m_rooms.size();
		} while (m_connected.at(toRoom));

		int xDiff;
		int yDiff;

		// Try to find way
		if (!m_connected.at(toRoom)) {
			xDiff = m_rooms.at(toRoom).m_tile.m_x - m_rooms.at(fromRoom).m_tile.m_x;
			yDiff = m_rooms.at(toRoom).m_tile.m_y - m_rooms.at(fromRoom).m_tile.m_y;

			if (xDiff == 0) {
				if (yDiff > 0)
					direction = SOUTH;
				else
					direction = NORTH;
			}
			else if (yDiff == 0) {
				if (xDiff > 0)
					direction = EAST;
				else
					direction = WEST;
			}
			else if (xDiff > 0 && yDiff > 0) {
				if (yDiff > xDiff)
					direction = SOUTH;
				else
					direction = EAST;
			}
			else if (xDiff < 0 && yDiff > 0) {
				if (yDiff > -xDiff)
					direction = SOUTH;
				else
					direction = WEST;
			}
			else if (xDiff > 0 && yDiff < 0) {
				if (-yDiff > xDiff)
					direction = NORTH;
				else
					direction = EAST;
			}
			else if (xDiff < 0 && yDiff < 0) {
				if (-yDiff > -xDiff)
					direction = NORTH;
				else
					direction = WEST;
			}
		}

		Tile opening = m_rooms.at(fromRoom).OpenRoom(direction);
		xDiff = m_rooms.at(toRoom).m_tile.m_x - opening.m_x;
		yDiff = m_rooms.at(toRoom).m_tile.m_y - opening.m_y;

		Tile tileToCheck;
		Tile currentTile = opening;
		std::vector<Tile> visited;

		bool digging = true;
		while (digging) {
			visited.push_back(currentTile);
			switch (direction) {
				//Heading north
			case NORTH:
				// While we are still below the target row
				tileToCheck = currentTile;
				tileToCheck.m_y--;
				yDiff++;
				switch (tiles.at(tileToCheck.m_y).at(tileToCheck.m_x)) {
					// If we find a RoomWall we gonna dig to it and connect it instead.
				case ROOMWALL:
					for (unsigned int i = 0; i < m_rooms.size(); i++) {
						if (m_rooms.at(i).Yours(tileToCheck)) {
							visited.push_back(tileToCheck);
							m_connected.at(i) = true;
							digging = false;
							break;
						}
					}

					break;

					// If we find an Unbuildable we know that it is either a LevelWall or a RoomCorner.
				case UNBUILDABLE:
					// If it is a LevelWall we are going to turn either left or right depending on xDiff.
					if (tileToCheck.m_y == 0) {
						if (xDiff > 0)
							direction = EAST;
						else
							direction = WEST;
					}
					// Else we are gonna cut right through it into the room and connect them instead.
					else {
						for (unsigned int i = 0; i < m_rooms.size(); i++) {
							if (m_rooms.at(i).Yours(tileToCheck)) {
								currentTile = tileToCheck;
								visited.push_back(currentTile);
								tileToCheck.m_y--;
								visited.push_back(tileToCheck);
								m_connected.at(i) = true;
								digging = false;
								break;
							}
						}
					}
					break;

					// If we find a Wall or Corridor we will continue in the same direction until yDiff is 0.
				case WALL:
				case CORRIDOR:
				case ROOM:
					currentTile = tileToCheck;

					if (yDiff == 0) {
						if (xDiff > 0)
							direction = EAST;
						else
							direction = WEST;
					}

					break;
					// If something went wrong
				default:
					std::cout << "Something went wrong in Corridor creation";
				}
				break; // Breaks North

			case EAST:
				// While we are still to the left of the target column
				tileToCheck = currentTile;
				tileToCheck.m_x++;
				xDiff--;
				switch (tiles.at(tileToCheck.m_y).at(tileToCheck.m_x)) {
					// If we find a RoomWall we gonna dig to it and connect it instead.
				case ROOMWALL:
					for (unsigned int i = 0; i < m_rooms.size(); i++) {
						if (m_rooms.at(i).Yours(tileToCheck)) {
							visited.push_back(tileToCheck);
							m_connected.at(i) = true;
							digging = false;
							break;
						}
					}

					break;
					// If we find an Unbuildable we know that it is either a LevelWall or a RoomCorner.
				case UNBUILDABLE:
					// If it is a LevelWall we are going to turn either left or right depending on xDiff.
					if (tileToCheck.m_x == WORLDSIZE - 1) {
						if (yDiff > 0)
							direction = SOUTH;
						else
							direction = NORTH;
					}
					// Else we are gonna cut right through it into the room and connect them instead.
					else {
						for (unsigned int i = 0; i < m_rooms.size(); i++) {
							if (m_rooms.at(i).Yours(tileToCheck)) {
								currentTile = tileToCheck;
								visited.push_back(currentTile);
								tileToCheck.m_x++;
								visited.push_back(tileToCheck);
								m_connected.at(i) = true;
								digging = false;
								break;
							}
						}
					}
					break;

					// If we find a Wall or Corridor we will continue in the same direction
				case WALL:
				case CORRIDOR:
				case ROOM:
					currentTile = tileToCheck;

					if (xDiff == 0) {
						if (yDiff > 0)
							direction = SOUTH;
						else
							direction = NORTH;
					}

					break;
					// If something went wrong
				default:
					std::cout << "Something went wrong in Corridor creation";
					break;
				}
				break; // Breaks East

			case SOUTH:
				// While we are still above the target row
				tileToCheck = currentTile;
				tileToCheck.m_y++;
				yDiff--;
				switch (tiles.at(tileToCheck.m_y).at(tileToCheck.m_x)) {
					// If we find a RoomWall we gonna dig to it and connect it instead.
				case ROOMWALL:
					for (unsigned int i = 0; i < m_rooms.size(); i++) {
						if (m_rooms.at(i).Yours(tileToCheck)) {
							visited.push_back(tileToCheck);
							m_connected.at(i) = true;
							digging = false;
							break;
						}
					}

					break;
					// If we find an Unbuildable we know that it is either a LevelWall or a RoomCorner.
				case UNBUILDABLE:
					// If it is a LevelWall we are going to turn either left or right depending on xDiff.
					if (tileToCheck.m_y == WORLDSIZE - 1) {
						if (xDiff > 0)
							direction = EAST;
						else
							direction = WEST;
					}
					// Else we are gonna cut right through it into the room and connect them instead.
					else {
						for (unsigned int i = 0; i < m_rooms.size(); i++) {
							if (m_rooms.at(i).Yours(tileToCheck)) {
								currentTile = tileToCheck;
								visited.push_back(currentTile);
								tileToCheck.m_y++;
								visited.push_back(tileToCheck);
								m_connected.at(i) = true;
								digging = false;
								break;
							}
						}
					}
					break;

					// If we find a Wall or Corridor we will continue in the same direction
				case WALL:
				case CORRIDOR:
				case ROOM:
					currentTile = tileToCheck;

					if (yDiff == 0) {
						if (xDiff > 0)
							direction = EAST;
						else
							direction = WEST;
					}

					break;
					// If something went wrong
				default:
					std::cout << "Something went wrong in Corridor creation";
					break;
				}
				break; // Breaks South

			case WEST:
				// While we are still to the right of the target column
				tileToCheck = currentTile;
				tileToCheck.m_x--;
				xDiff++;
				switch (tiles.at(tileToCheck.m_y).at(tileToCheck.m_x)) {
					// If we find a RoomWall we gonna dig to it and connect it instead.
				case ROOMWALL:
					for (unsigned int i = 0; i < m_rooms.size(); i++) {
						if (m_rooms.at(i).Yours(tileToCheck)) {
							visited.push_back(tileToCheck);
							m_connected.at(i) = true;
							digging = false;
							break;
						}
					}
					break;

					// If we find an Unbuildable we know that it is either a LevelWall or a RoomCorner.
				case UNBUILDABLE:
					// If it is a LevelWall we are going to turn either left or right depending on xDiff.
					if (tileToCheck.m_x == 0) {
						if (yDiff > 0)
							direction = SOUTH;
						else
							direction = NORTH;
					}
					// Else we are gonna cut right through it into the room and connect them instead.
					else {
						for (unsigned int i = 0; i < m_rooms.size(); i++) {
							if (m_rooms.at(i).Yours(tileToCheck)) {
								currentTile = tileToCheck;
								visited.push_back(currentTile);
								tileToCheck.m_x--;
								visited.push_back(tileToCheck);
								m_connected.at(i) = true;
								digging = false;
								break;
							}
						}
					}
					break;

					// If we find a Wall or Corridor we will continue in the same direction
				case WALL:
				case CORRIDOR:
				case ROOM:
					currentTile = tileToCheck;

					if (xDiff == 0) {
						if (yDiff > 0)
							direction = SOUTH;
						else
							direction = NORTH;
					}

					break;

					// If something went wrong
				default:
					std::cout << "Something went wrong in Corridor creation";
					break;
				}
				break; // Breaks West
			} // End direction switch
		} // End digging

		for (unsigned int i = 0; i < visited.size(); i++) {
			tiles.at(visited.at(i).m_y).at(visited.at(i).m_x) = CORRIDOR;
		}


		done = true;
		// Check to see if all rooms are connected
		for (unsigned int i = 0; i < m_connected.size(); i++) {
			if (!m_connected.at(i)) {
				done = false;
				break;
			}

		}
	}

	for (unsigned int y = 1; y < tiles.size() - 1; y++) {
		for (unsigned int x = 1; x < tiles.at(y).size() - 1; x++) {
			if (tiles.at(y).at(x) == CORRIDOR) {
				if (tiles.at(y - 1).at(x - 1) == WALL)
					tiles.at(y - 1).at(x - 1) = ROOMWALL;
				if (tiles.at(y - 1).at(x) == WALL)
					tiles.at(y - 1).at(x) = ROOMWALL;
				if (tiles.at(y - 1).at(x + 1) == WALL)
					tiles.at(y - 1).at(x + 1) = ROOMWALL;
				if (tiles.at(y).at(x - 1) == WALL)
					tiles.at(y).at(x - 1) = ROOMWALL;
				if (tiles.at(y).at(x) == WALL)
					tiles.at(y).at(x) = ROOMWALL;
				if (tiles.at(y).at(x + 1) == WALL)
					tiles.at(y).at(x + 1) = ROOMWALL;
				if (tiles.at(y + 1).at(x - 1) == WALL)
					tiles.at(y + 1).at(x - 1) = ROOMWALL;
				if (tiles.at(y + 1).at(x) == WALL)
					tiles.at(y + 1).at(x) = ROOMWALL;
				if (tiles.at(y + 1).at(x + 1) == WALL)
					tiles.at(y + 1).at(x + 1) = ROOMWALL;
			}
		}
	}
}

TileGrid::Room::Room(int _x, int _y, int _size) {
	m_tile.m_x = _x;
	m_tile.m_y = _y;
	m_size = _size;
}

bool TileGrid::Room::Yours(Tile _tile) {
	if (_tile.m_x <= m_tile.m_x + m_size + 1 && _tile.m_x >= m_tile.m_x - m_size - 1 &&
		_tile.m_y <= m_tile.m_y + m_size + 1 && _tile.m_y >= m_tile.m_y - m_size - 1)
		return true;
	else
		return false;

}

TileGrid::Tile TileGrid::Room::OpenRoom(TileGrid::Direction _dir) {
	Tile tile;

	switch (_dir) {
	case NORTH:
		tile.m_y = m_tile.m_y - m_size - 1;
		tile.m_x = m_tile.m_x - m_size + (rand() % (m_size * 2 + 1));
		break;

	case EAST:
		tile.m_x = m_tile.m_x + m_size + 1;
		tile.m_y = m_tile.m_y - m_size + (rand() % (m_size * 2 + 1));
		break;

	case SOUTH:
		tile.m_y = m_tile.m_y + m_size + 1;
		tile.m_x = m_tile.m_x - m_size + (rand() % (m_size * 2 + 1));
		break;

	case WEST:
		tile.m_x = m_tile.m_x - m_size - 1;
		tile.m_y = m_tile.m_y - m_size + (rand() % (m_size * 2 + 1));
		break;
	}

	return tile;
}