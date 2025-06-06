#ifndef _ROUTE_H_
#define _ROUTE_H_
#include"tile.h"
#include<SDL.h>
#include<vector>
class Route
{
public:
	typedef std::vector<SDL_Point> IdxList;//储存索引
public:
	Route()=default;
	Route(const TileMap& map, const SDL_Point& idx_origin) {
		size_t width_map = map[0].size();
		size_t height_map = map.size();
		SDL_Point idx_next = idx_origin;
		while (true) {
			if (idx_next.x >= width_map || idx_next.y >= height_map)//超出地图检查
				break;
			if (check_duplicate_idx(idx_next)) //重复索引点检查,避免死循环
				break;
			else 
				idx_list.push_back(idx_next);//放到索引里面

			//判断下一个点是否存在
			bool is_next_dir_exist = true;
			const Tile& tile = map[idx_next.y][idx_next.x];
			if (tile.special_flag == 0)//防守点，路径结束
				break;
			switch (tile.direction) {
			case Tile::Direction::Up:
				idx_next.y--;
				break;
			case Tile::Direction::Down:
				idx_next.y++;
				break;
			case Tile::Direction::left:
				idx_next.x--;
				break;
			case Tile::Direction::right:
				idx_next.x++;
				break;
			default:
				is_next_dir_exist = false;//没有路标
				break;

			}
			if (!is_next_dir_exist)
				break;

			
		
		}
	}
	~Route()=default;
	const IdxList& get_idx_list()const {
		return idx_list;
	}

private:
	IdxList idx_list;
private:
	bool check_duplicate_idx(const SDL_Point& target_idx)
	//检查有没有重复的索引点
	{
		for (const SDL_Point& idx : idx_list) {
			if (idx.x == target_idx.x && idx.y == target_idx.y) {
				return true;

			}
		}
		return false;
	}

};


#endif // !_ROUTE_H_

