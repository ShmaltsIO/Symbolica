#include "CollisionSystem.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "PlayerTagComponent.h"
#include "MoneyTagComponent.h"
#include "WorthComponent.h"
#include "FoodTagComponent.h"
#include "HealthComponent.h"
#include "ObstacleTagComponent.h"
#include "MovementComponent.h"
#include "SystemManager.h"
#include "PlayerControlSystem.h"
#include "Filter.h"
#include "MovementSystem.h"
#include "LevelComponent.h"
#include "ExperienceComponent.h"
#include "StepComponent.h"
#include "DoorTagComponent.h"
#include "GameWinSystem.h"
#include "OpenableComponent.h"
#include "EnemyTagComponent.h"
#include "DamageComponent.h"
#include "AIcontrolsSystem.h"
#include "RoomsSwitchSystem.h"
#include "InventoryComponent.h"
#include "ItemComponent.h"
#include "TextureComponent.h"
#include "ColorComponent.h"
#include "OnPlaceComponent.h"
#include "WeaponTagComponent.h"
#include "ItemTagComponent.h"
#include "ArmorTagComponent.h"
// TODO: Needs filter or not? It can destroy some idiom
// static bool Filter(const Entity& entity) {
//   return entity.Contains<ColliderComponent>();
// }

/**
 * @brief This function look at entites and check them tags.
 * @param entity_1 is first entity for collide (default is player).
 * @param entity_2 is second entity for collide.
 */
void CollisionSystem::Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;
  }

  if (entity_1->Contains<PlayerTagComponent>()) {

    if (entity_2->Contains<MoneyTagComponent>()) {
      auto wc_1 = entity_1->Get<WorthComponent>();
      auto wc_2 = entity_2->Get<WorthComponent>();

      // Earn some money and destroy coin
      wc_1->setWorth(wc_1->getWorth() + wc_2->getWorth());
      GetEntityManager().DeleteEntity(entity_2->GetId());
    }
    // TODO: RE-make this with if (itemTag!)
    if (entity_2->Contains<ItemTagComponent>()) {
      if (entity_2->Contains<FoodTagComponent>()) {
        auto ic = entity_1->Get<InventoryComponent>();
        if ((ic->getCurrentSize() < ic->getMaxSize()) && !entity_2->Get<OnPlaceComponent>()->getStatus()) {
          ic->addItem(ItemComponent(entity_2->GetId(), "Health's potion", "Very useful thing.")); // Smells like a american burger with extra cheese.
          //std::cout << "INVENTORY SIZE: " << ic->getInventory().size() << "COMPONNT: " << entity_2->Get<TransformComponent>() << std::endl;
          entity_2->Delete<TransformComponent>();
        }
        std::cout << "NO" << std::endl;
      }
      // TODO: Create utilits function whcih can return description and name by item level!
      if (entity_2->Contains<WeaponTagComponent>()) {
        auto ic = entity_1->Get<InventoryComponent>();
        if ((ic->getCurrentSize() < ic->getMaxSize()) && !entity_2->Get<OnPlaceComponent>()->getStatus()) {
          ic->addItem(ItemComponent(entity_2->GetId(), "Sword", "Just a sword.")); // Smells like a american burger with extra cheese.
          entity_2->Delete<TransformComponent>();
        }
      }

      if (entity_2->Contains<ArmorTagComponent>()) {
        auto ic = entity_1->Get<InventoryComponent>();
        if ((ic->getCurrentSize() < ic->getMaxSize()) && !entity_2->Get<OnPlaceComponent>()->getStatus()) {
          ic->addItem(ItemComponent(entity_2->GetId(), "Armor", "Just a armor.")); // Smells like a american burger with extra cheese.
          entity_2->Delete<TransformComponent>();
        }
      }
    }
    

    if (entity_2->Contains<ObstacleTagComponent>()) {
      auto cm_1 = entity_1->Get<ColliderComponent>();
      auto tc_1 = entity_1->Get<TransformComponent>();
      auto sc_1 = entity_1->Get<StepComponent>();
      // Offset our player on prev. position
      tc_1->position_ -= cm_1->offset_;
      sc_1->setSteps(sc_1->getSteps() - 1);
      std::cout << "Wall, bro" << std::endl;
    }

    if (entity_2->Contains<DoorTagComponent>()) {
      // if all def yes then is_open = true
      // if entities enemy .count == 0 then is_open change
      auto oc_2 = entity_2->Get<OpenableComponent>();
      // auto wc_1 = entity_1->Get<WorthComponent>();
      // auto wc_2 = entity_2->Get<WorthComponent>();
      // if (wc_1->getWorth() >= wc_2->getWorth()) {
      //   wc_1->setWorth(wc_1->getWorth() - wc_2->getWorth());
      //   oc_2->setOpen();
      // }
      if (!oc_2->getStatus()) {
        auto comp = entity_2->Get<LevelComponent>();
        std::cout << "DOOR COLLISION: " << comp->getLevel() << std::endl;
        if (comp->getLevel() >= 8) {
          GetSystemManager().Enable<GameWinSystem>();
        } else {
          GetSystemManager().Enable<RoomsSwitchSystem>();
        }
      } else {
        auto cm_1 = entity_1->Get<ColliderComponent>();
        auto tc_1 = entity_1->Get<TransformComponent>();
        auto sc_1 = entity_1->Get<StepComponent>();
        tc_1->position_ -= cm_1->offset_;
        sc_1->setSteps(sc_1->getSteps() - 1);
        //std::cout << terminal_state(TK_COLOR) << std::endl; standart color is 0
        //terminal_color("red");
        //terminal_print(tc_1->position_.getX(), tc_1->position_.getY()-1, "LOCK");
      }
    }

    if (entity_2->Contains<EnemyTagComponent>()) {
      //GetSystemManager().Disable<AIcontrolsSystem>();
      //GetSystemManager().Disable<MovementSystem>();
      auto hc_1 = entity_1->Get<HealthComponent>();
      auto dc_1 = entity_1->Get<DamageComponent>();

      auto dc_2 = entity_2->Get<DamageComponent>();
      auto hc_2 = entity_2->Get<HealthComponent>();

      //auto cm_1 = entity_1->Get<ColliderComponent>();
      //auto tc_1 = entity_1->Get<TransformComponent>();
      auto sc_1 = entity_1->Get<StepComponent>();
      
      //tc_1->position_ -= cm_1->offset_;
      sc_1->setSteps(sc_1->getSteps() - 1);

      while (hc_1->getHealth() > 0 && hc_2->getHealth() > 0) {
        hc_1->setHealth(hc_1->getHealth() - dc_2->getDamage());
        hc_2->setHealth(hc_2->getHealth() - dc_1->getDamage());
      }
      
      if (hc_2->getHealth() <= 0) {
        GetEntityManager().DeleteEntity(entity_2->GetId());
      }
      // std::cout << "Battle, bround" << std::endl;
    }

  }

  if (entity_1->Contains<EnemyTagComponent>()) {
    if (entity_2->Contains<EnemyTagComponent>()) {
      auto cm_1 = entity_1->Get<ColliderComponent>();
      auto tc_1 = entity_1->Get<TransformComponent>();

      tc_1->position_ = cm_1->offset_;

      std::cout << "Enemy, bro" << std::endl;
    }
  }

  //GetSystemManager().Enable<AIcontrolsSystem>();
  //GetSystemManager().Enable<MovementSystem>();
}

CollisionSystem::CollisionSystem(EntityManager* const entity_manager, SystemManager* const system_manager):
 ISystem(entity_manager, system_manager) {}

void CollisionSystem::OnPreUpdate() {}

void CollisionSystem::OnUpdate() {
  // TODO: Can create list with priotitets, and then we will know, where consides a player, but it was tree
  auto player = GetEntityManager().Get(2);
  
  auto tcp = player->Get<TransformComponent>();
  
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<TransformComponent>()) {
      auto tc = entity.Get<TransformComponent>();
      if ((tcp->position_ == tc->position_ && tcp->position_ == tc->position_)) {
        Collide(player, &entity);
      }
    }
  }

  // For enemies collision
  for (auto& enemy : GetEntityManager()) {
    if (enemy.Contains<EnemyTagComponent>()) {
      auto tc_e = enemy.Get<TransformComponent>();
      for (auto& enemy_other : GetEntityManager()) {
        if (enemy_other.Contains<TransformComponent>()) {
          auto tc_eo = enemy_other.Get<TransformComponent>();
          if (tc_e->position_ == tc_eo->position_) {
            Collide(&enemy, &enemy_other);
          }
        }

      }
    }
  }

  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<ColliderComponent>()) {
      entity.Get<ColliderComponent>()->Clear();
    }
  }
}

void CollisionSystem::OnPostUpdate() {}
