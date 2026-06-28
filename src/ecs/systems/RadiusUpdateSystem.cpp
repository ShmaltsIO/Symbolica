#include "RadiusUpdateSystem.h"

void RadiusUpdateSystem::OnPreUpdate() {}

void RadiusUpdateSystem::OnUpdate() {
    std::vector<size_t> neighborhood{};

    auto* player = game_state_.getPlayer();

    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<TransformComponent>() && !entity.Contains<GroundTagComponent>()) {
            auto tc_e = entity.Get<TransformComponent>();
            auto tc_p = player->Get<TransformComponent>();
            if (getDistanceBetweenVectors2D(tc_p->position_, tc_e->position_) <= 1) {
                neighborhood.push_back(entity.GetId());
             }
        }
    }

    player->Get<RadiusComponent>()->setNeighborhood(neighborhood);
}

void RadiusUpdateSystem::OnPostUpdate() {}
