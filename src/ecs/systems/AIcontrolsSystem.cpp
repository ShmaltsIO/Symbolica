#include "AIcontrolsSystem.h"

void AIcontrolsSystem::OnPreUpdate() {}

void AIcontrolsSystem::OnUpdate() {
    auto* map = game_state_->getCurrentMap();
    if (!map) return;

    Entity* player = game_state_->getPlayer();
    if (!player) return;
    Vector2D playerPos = player->Get<TransformComponent>()->position_;

    for (auto& entity : GetEntityManager()) {
        if (!entity.Contains<EnemyTagComponent>()) continue;

        auto* tc = entity.Get<TransformComponent>();
        auto* pttc = entity.Get<PathToTargetComponent>();
        auto* sight = entity.Get<SightRadiusComponent>();
        if (!sight) continue; // если нет радиуса, пропускаем

        int dist = getDistanceBetweenVectors2D(playerPos, tc->position_);
        if (dist <= sight->getRadius()) {
            std::vector<Vector2D> path = aStar(playerPos, tc->position_, *map);
            pttc->setPathToTarget(path);
        }
        else {
            // Не видит – путь пуст (враг стоит)
            pttc->setPathToTarget({});
        }
    }
}

void AIcontrolsSystem::OnPostUpdate() {}