#include "MovementSystem.h"

#include "EntityManager.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "Vector2D.h"
#include "PlayerTagComponent.h"
#include "SystemManager.h"
#include "ColliderComponent.h"
#include "EnemyTagComponent.h"
#include "PathToTargetComponent.h"
#include "ItemTagComponent.h"
#include "OnPlaceComponent.h"
#include "HealthComponent.h"
#include "StepComponent.h"
#include "StepLimitComponent.h"

MovementSystem::MovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager), player_is_moved_(false) {}

void MovementSystem::OnPreUpdate() {}

void MovementSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<PlayerTagComponent>()) {
      auto transform_component = entity.Get<TransformComponent>();
      auto movement_component = entity.Get<MovementComponent>();
      auto collider_component = entity.Get<ColliderComponent>();

      collider_component->offset_ = movement_component->direction_;
      // TODO: operator != not working correcctly, it always 0 - false
      if (!(movement_component->direction_ == zeroVector)) {
        player_is_moved_ = true;
        std::cout << "MOVe SYS" << std::endl;
        for (auto& item : GetEntityManager()) {
          if (item.Contains<ItemTagComponent>()) {
            if (item.Get<OnPlaceComponent>()->getStatus()) {
              item.Get<OnPlaceComponent>()->disable();
            }
          }
        }
        auto step_limit_c = GetEntityManager().Get(3)->Get<StepLimitComponent>();
        if (entity.Get<StepComponent>()->getSteps() >= step_limit_c->getStepLimit() / 2) {
          auto hc_p = entity.Get<HealthComponent>();
          hc_p->setHealth(hc_p->getHealth() - 1);
        }
      }
      //std::cout<<"DIRECTION BEFORE, OnUpd: " << movement_component->direction_ << std::endl;

      transform_component->position_ += movement_component->direction_;  // TODO: multiply by delta time
      //std::cout<<"POSITION: " <<transform_component->position_ << std::endl;
      movement_component->direction_ = zeroVector;
    }
    
    if (entity.Contains<EnemyTagComponent>() && player_is_moved_) {
      auto tc_e = entity.Get<TransformComponent>();
      auto pttc_e = entity.Get<PathToTargetComponent>();
      auto cc_e = entity.Get<ColliderComponent>();

      // for (auto& v : pttc_e->getPathToTarget()) {
      //   std::cout << "MY WAY: " << v << std::endl;
      // }
      cc_e->offset_ = *(pttc_e->getPathToTarget().end() - 1);
      tc_e->position_ = *(pttc_e->getPathToTarget().end() - 2);
      std::cout << "TARGET: " << pttc_e->getPathToTarget()[1] << std::endl;
      std::cout << "END: " << pttc_e->getPathToTarget()[pttc_e->getPathToTarget().size()-1] << std::endl;
      std::cout << "BEGIN: " << pttc_e->getPathToTarget()[0] << std::endl;
    }
  }
  player_is_moved_ = false;

}

void MovementSystem::OnPostUpdate() {}
