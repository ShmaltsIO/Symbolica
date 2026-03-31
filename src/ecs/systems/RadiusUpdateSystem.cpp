#include "RadiusUpdateSystem.h"
#include "EntityManager.h"
#include "PlayerTagComponent.h"
#include "EnemyTagComponent.h"
#include "RadiusComponent.h"
#include "TransformComponent.h"
#include "GroundTagComponent.h"
#include <vector>

RadiusUpdateSystem::RadiusUpdateSystem(EntityManager* entity_manager, SystemManager* system_manager):
 ISystem(entity_manager, system_manager) {}

void RadiusUpdateSystem::OnPreUpdate() {}

void RadiusUpdateSystem::OnUpdate() {
    std::vector<size_t> neighborhood{};

    for (auto& player : GetEntityManager()) {
        if (player.Contains<PlayerTagComponent>()) {
            for (auto& entity : GetEntityManager()) {
                if (entity.Contains<TransformComponent>() && !entity.Contains<GroundTagComponent>()) {
                    auto tc_e = entity.Get<TransformComponent>();
                    auto tc_p = player.Get<TransformComponent>();
                    if (getDistanceBetweenVectors2D(tc_p->position_, tc_e->position_) <= 1) {
                        neighborhood.push_back(entity.GetId());
                    }
                }
            }
        }
        player.Get<RadiusComponent>()->setNeighborhood(neighborhood);
        break;
    }
}

void RadiusUpdateSystem::OnPostUpdate() {}
