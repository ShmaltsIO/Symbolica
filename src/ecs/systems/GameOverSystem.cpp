#include "GameOverSystem.h"
#include "Entity.h"
#include "EntityManager.h"
#include "PlayerTagComponent.h"
#include "HealthComponent.h"
#include "ObserverTagComponent.h"
#include "StepComponent.h"
#include "StepLimitComponent.h"

GameOverSystem::GameOverSystem(EntityManager* const entity_manager, SystemManager* const system_manager, Context* ctx)
      : ISystem(entity_manager, system_manager), ctx_(ctx) {}

void GameOverSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<PlayerTagComponent>()) {
      auto observer = GetEntityManager().Get(3);
      if (entity.Get<HealthComponent>()->getHealth() <= 0 
        || entity.Get<StepComponent>()->getSteps() >= observer->Get<StepLimitComponent>()->getStepLimit()) {
        ctx_->scene_ = "game_over";
      }
    }
  }
}
