#include "AIcontrolsSystem.h"
#include "EntityManager.h"
#include "PlayerTagComponent.h"
#include "EnemyTagComponent.h"
#include "TransformComponent.h"
#include "PathToTargetComponent.h"
#include "aStar.h"
#include "GameState.h"

AIcontrolsSystem::AIcontrolsSystem(EntityManager* entityManager, SystemManager* systemManager, Context* context)
    : ISystem(entityManager, systemManager), context_(context) {
}

void AIcontrolsSystem::OnPreUpdate() {}

void AIcontrolsSystem::OnUpdate() {
    auto* map = context_->game_state->getCurrentMap();
    if (!map) return;

    Vector2D playerPos;
    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<PlayerTagComponent>()) {
            auto tc = entity.Get<TransformComponent>();
            playerPos = tc->position_;
            break;
        }
    }

    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<EnemyTagComponent>()) {
            auto tc = entity.Get<TransformComponent>();
            auto pttc = entity.Get<PathToTargetComponent>();
            std::vector<Vector2D> path = aStar(playerPos, tc->position_, *map);
            if (path.empty()) {
                path.push_back(tc->position_);
                path.push_back(tc->position_);
            }
            pttc->setPathToTarget(path);
        }
    }
}

void AIcontrolsSystem::OnPostUpdate() {}