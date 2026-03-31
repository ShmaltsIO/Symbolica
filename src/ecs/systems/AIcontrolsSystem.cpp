#include "AIcontrolsSystem.h"
#include "EntityManager.h"
#include "PlayerTagComponent.h"
#include "EnemyTagComponent.h"
#include "TransformComponent.h"
#include "PathToTargetComponent.h"
#include "aStar.h"

AIcontrolsSystem::AIcontrolsSystem(EntityManager* entity_manager, SystemManager* system_manager, Grid level_map):
 ISystem(entity_manager, system_manager), level_map_(level_map) {}

void AIcontrolsSystem::OnPreUpdate() {}

void AIcontrolsSystem::OnUpdate() {
    Vector2D player_pos{0, 0};
    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<PlayerTagComponent>()) {
            auto tc_p = entity.Get<TransformComponent>();
            player_pos = tc_p->position_;
            break;
        }
    }

    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<EnemyTagComponent>()) {
            auto tc_e = entity.Get<TransformComponent>();
            auto pttc_e = entity.Get<PathToTargetComponent>();
            //std::vector<GameObjectsEnum> obstacles = {GameObjectsEnum::WALL, GameObjectsEnum::DOOR_TO, GameObjectsEnum::DOOR_FROM};
            std::vector<Vector2D> path = aStar(Node(player_pos), Node(tc_e->position_), level_map_, {GameObjectsEnum::WALL, GameObjectsEnum::DOOR_TO, GameObjectsEnum::DOOR_FROM}, true);
            if (path.empty()) {
                path.push_back(tc_e->position_);
                path.push_back(tc_e->position_);
                //std::cout << "STOIK " << tc_e->position_ << std::endl;
            }
            // for (unsigned int i = 0; i < path.size(); i++) {
            //     std::cout << "OPTIMUM: " << i << " " << path[i] << std::endl;

            //     std::cout << "BEGIN: " << i << " " << *(path.end() - 2) << std::endl;
            // }
            pttc_e->setPathToTarget(path);
        }
    }
}

void AIcontrolsSystem::OnPostUpdate() {}
