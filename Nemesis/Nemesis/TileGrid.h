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
	~TileGrid();
	static TileGrid* GetInstance();
	static void RemoveInstance();

	void Init();

	bool IsWalkable(Position pos);
	std::string IsType(Position pos);

	void Update();
	void Draw();

	Position GetStartPosition();

	void CleanUp();

private:
	TileGrid(){};

	void SpawnRooms(std::vector<std::vector<TileStatus>> &tiles);
	void ConnectRooms(std::vector<std::vector<TileStatus>> &tiles);
	
private:
	static bool m_instanceFlag;
	static TileGrid* m_single;

	std::vector<std::vector<TileBase*>> m_tiles;

	std::vector<Room> m_rooms;
	std::vector<bool> m_connected;

	Position m_startPosition;
};
