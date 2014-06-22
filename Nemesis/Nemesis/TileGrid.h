// TileGrid.h

#pragma once

#include "Position.h"

class TileBase;

class TileGrid {
public: 
	enum Direction {
		NORTH,
		EAST,
		SOUTH,
		WEST,
		DCOUNT
	};

	enum TileStatus {
		WALL,
		ROOM,
		CORRIDOR,
		ROOMWALL,
		UNBUILDABLE,
		TCOUNT
	};

	struct Tile {
		int m_x;
		int m_y;

		Tile() {};
		Tile(int _x, int _y);
	};

	struct Room {
	public:
		Tile m_tile;
		int m_size;

		Room(){};
		Room(int _x, int _y, int _size);
		Room(Tile _tile, int _size);

		bool Yours(Tile _tile);
		Tile OpenRoom(Direction _dir);
	};

public:
	TileGrid();
	~TileGrid();

	void Init();

	bool IsWalkable(Position pos);
	std::string IsType(Position pos);

	void Update();
	void Draw();

	void SpawnRooms(std::vector<std::vector<TileStatus>> &tiles);
	void ConnectRooms(std::vector<std::vector<TileStatus>> &tiles);

	void CleanUp();

private:
	std::vector<std::vector<TileBase*>> m_tiles;

	std::vector<Room> m_rooms;
	std::vector<bool> m_connected;

	sf::Sprite* m_floorSprite;
	sf::Sprite* m_wallSprite;
};
