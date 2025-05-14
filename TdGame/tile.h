#ifndef _TILE_H
#define _TILE_H
#include<vector>
#define SIZE_TILE 48
struct Tile {
	int terrain = 0;//地形层
	int decoration = -1;
	int special_flag = -1;
	enum class Direction {
		None = 0,
		Up,
		Down,
		left,
		right
	};
	Direction direction = Direction::None;
	bool has_tower = false;

	
};
typedef std::vector<std::vector<Tile>> TileMap;//别名
#endif // !_TILE_H
 
