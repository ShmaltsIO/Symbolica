#include "MovementSystem.h"

void MovementSystem::OnPreUpdate() {
    player_is_moved_ = false;
}

void MovementSystem::OnUpdate() {
    Entity* player = game_state_.getPlayer();
    if (!player) return;

    auto* map = game_state_.getCurrentMap();
    if (!map) return;

    // 1. Строим множество занятых позиций (все сущности с TransformComponent)
    std::unordered_set<Vector2D> occupied;
    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<TransformComponent>() && !entity.Contains<ItemTagComponent>()) {
            auto* tc = entity.Get<TransformComponent>();
            occupied.insert(tc->position_);
        }
    }

    // 2. Движение игрока
    auto* mc_p = player->Get<MovementComponent>();
    auto* tc_p = player->Get<TransformComponent>();
    Vector2D playerPos = tc_p->position_;

    if (mc_p->direction_ != zeroVector) {
        Vector2D newPos = tc_p->position_ + mc_p->direction_;
        if (map->isWalkable(newPos.getX(), newPos.getY())) {
            occupied.erase(tc_p->position_);
            tc_p->position_ = newPos;
            occupied.insert(newPos);
            playerPos = newPos; // обновляем позицию игрока
            player_is_moved_ = true;
        }
        mc_p->direction_ = zeroVector;
    }

    // 3. Движение врагов
    if (player_is_moved_) {
        for (auto& entity : GetEntityManager()) {
            if (!entity.Contains<EnemyTagComponent>()) continue;
            auto* pttc = entity.Get<PathToTargetComponent>();
            if (!pttc) continue;
            auto& path = pttc->getPathToTarget();
            if (path.size() < 2) continue;

            // Враг двигается к предпоследней клетке (перед игроком)
            Vector2D targetPos = path[1];
            auto* tc_e = entity.Get<TransformComponent>();

            // Если враг уже стоит на целевой клетке – не двигается
            if (tc_e->position_ == targetPos) continue;

            // Враг может войти, если клетка свободна (не занята другой сущностью)
            if (occupied.find(targetPos) == occupied.end()) {
                occupied.erase(tc_e->position_);
                tc_e->position_ = targetPos;
                occupied.insert(targetPos);
            }
            // иначе стоит на месте
        }
    }
    
}

void MovementSystem::OnPostUpdate() {}