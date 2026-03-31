#include "GameWinSystem.h"
#include "EntityManager.h"
#include "DoorTagComponent.h"
#include "OpenableComponent.h"
#include "PlayerTagComponent.h"

GameWinSystem::GameWinSystem(EntityManager* const entity_manager, SystemManager* const system_manager, Context* ctx)
      : ISystem(entity_manager, system_manager), ctx_(ctx) {}

void GameWinSystem::OnUpdate() {
    // for (auto& entity : GetEntityManager()) {
    //     if (entity.Contains<DoorTagComponent>() && entity.Get<OpenableComponent>()->getStatus()) {
    //         //
    //     }
    // }
    ctx_->scene_ = "game_win";
}


