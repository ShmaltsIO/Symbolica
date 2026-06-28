#include "MovementSystem.h"

void MovementSystem::OnPreUpdate() {
    player_is_moved_ = false;
}

void MovementSystem::OnUpdate() {
    // 1. ƒвижение игрока
    if (game_state_.getPlayer()) {
        auto* player = game_state_.getPlayer();
        auto* mc = player->Get<MovementComponent>();
        auto* tc = player->Get<TransformComponent>();
        auto* cm = player->Get<ColliderComponent>();
        cm->offset_ = mc->direction_; // запоминаем направление дл€ отката

        Vector2D vec = tc->position_ + mc->direction_;

        if (mc->direction_ != zeroVector && game_state_.getCurrentMap()->isWalkable(vec.getX(), vec.getY())) {
            tc->position_ += mc->direction_;
            player_is_moved_ = true;
            mc->direction_ = zeroVector;
        }
    }

    // 2. ƒвижение врагов (только если игрок сдвинулс€)
    if (player_is_moved_) {
        for (auto& enemy : GetEntityManager()) {
            if (!enemy.Contains<EnemyTagComponent>()) continue;

            auto* pttc = enemy.Get<PathToTargetComponent>();
            auto& path = pttc->getPathToTarget();
            if (path.size() >= 2) {
                auto* tc = enemy.Get<TransformComponent>();
                tc->position_ = path[path.size() - 2];
            }
        }
    }
}

void MovementSystem::OnPostUpdate() {}