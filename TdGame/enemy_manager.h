#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#include "enemy.h"
#include "manager.h"
#include "config_manager.h"
#include"home_manager.h"

#include "slim_enemy.h"
#include "king_slim_enemy.h"
#include "skeleton_enemy.h"
#include "goblin_enemy.h"
#include "goblin_priest_enemy.h"


#include <vector>
#include <SDL.h>

class EnemyManager : public Manager<EnemyManager>
{
	friend class Manager<EnemyManager>;

public:
	typedef std::vector<Enemy*> EnemyList;

public:
	void on_update(double delta)
	{
		for (Enemy* enemy : enemy_list)
			enemy->on_update(delta);

		process_home_collision();
		
	}

	void on_render(SDL_Renderer* renderer)
	{
		for (Enemy* enemy : enemy_list)
			enemy->on_render(renderer);
	}

	void spawn_enemy(EnemyType type, int idx_spawn_point)
	{
		static Vector2 position;
		static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
		static const Map::spawnerRoutePool& spawner_route_pool
			= ConfigManager::instance()->map.get_idx_spawner_pool();

		const auto& itor = spawner_route_pool.find(idx_spawn_point);
		if (itor == spawner_route_pool.end())
			return;//find() ����Ҳ���������������������Ƿ��� .end()

		Enemy* enemy = nullptr;

		switch (type)
		{
		case EnemyType::Slim:
			enemy = new SlimEnemy();
			break;
		case EnemyType::KingSlim:
			enemy = new KingSlimeEnemy();
			break;
		case EnemyType::Skeleton:
			enemy = new SkeletonEnemy();
			break;
		case EnemyType::Goblin:
			enemy = new GoblinEnemy();
			break;
		case EnemyType::GoblinPriest:
			enemy = new GoblinPriestEnemy();
			break;
		default:
			enemy = new SlimEnemy();
			break;
		}
		//�ż���ʱ�Ļص�����
		enemy->set_on_skill_released(
			[&](Enemy* enemy_src)
			{
				double recover_raduis = enemy_src->get_recover_radius();
				if (recover_raduis < 0) return;

				const Vector2 pos_src = enemy_src->get_position();
				for (Enemy* enemy_dst : enemy_list)//��Ѫ
				{
					const Vector2& pos_dst = enemy_dst->get_position();
					double distance = (pos_dst - pos_src).length();
					if (distance <= recover_raduis)
						enemy_dst->increase_hp(enemy_src->get_recover_intensity());
				}
			});

		const Route::IdxList& idx_list = itor->second.get_idx_list();
		//ת��Ϊ��������
		position.x = rect_tile_map.x + idx_list[0].x * SIZE_TILE + SIZE_TILE / 2;
		position.y = rect_tile_map.y + idx_list[0].y * SIZE_TILE + SIZE_TILE / 2;

		enemy->set_position(position);//���õĳ�ʼλ��
		enemy->set_route(&itor->second);//Ѱ··��

		enemy_list.push_back(enemy);
	}

	bool check_cleared()
	{
		return enemy_list.empty();
	}

	EnemyManager::EnemyList& get_enemy_list()
	{
		return enemy_list;
	}

protected:
	EnemyManager() = default;

	~EnemyManager()
	{
		for (Enemy* enemy : enemy_list)
			delete enemy;
	}//����ÿһ������

private:
	EnemyList enemy_list;

private:
	//������ײ
	void process_home_collision()
	{
		static const SDL_Point& idx_home = ConfigManager::instance()->map.get_idx_home();
		static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
		static const Vector2 position_home_tile =
		{
			(double)rect_tile_map.x + idx_home.x * SIZE_TILE,
			(double)rect_tile_map.y + idx_home.y * SIZE_TILE
		};

		for (Enemy* enemy : enemy_list)
		{
			if (enemy->can_remove()) continue;

			const Vector2& position = enemy->get_position();

			if (position.x >= position_home_tile.x
				&& position.y >= position_home_tile.y
				&& position.x <= position_home_tile.x + SIZE_TILE
				&& position.y <= position_home_tile.y + SIZE_TILE)//���˵��˼ҵĸ���
			{
				enemy->make_invalid();

				HomeManager::instance()->decrease_hp(enemy->get_damage());
			}
		}
	}



	 

	

};

#endif // !_ENEMY_MANAGER_H_
