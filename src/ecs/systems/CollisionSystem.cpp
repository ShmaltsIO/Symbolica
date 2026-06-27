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
          //ic->addItem(ItemComponent(entity_2->GetId(), "Health's potion", "Very useful thing.")); // Smells like a american burger with extra cheese.
          //std::cout << "INVENTORY SIZE: " << ic->getInventory().size() << "COMPONNT: " << entity_2->Get<TransformComponent>() << std::endl;
          entity_2->Delete<TransformComponent>();
        }
        std::cout << "NO" << std::endl;
      }
      // TODO: Create utilits function whcih can return description and name by item level!
      if (entity_2->Contains<WeaponTagComponent>()) {
        auto ic = entity_1->Get<InventoryComponent>();
        if ((ic->getCurrentSize() < ic->getMaxSize()) && !entity_2->Get<OnPlaceComponent>()->getStatus()) {
          //ic->addItem(ItemComponent(entity_2->GetId(), "Sword", "Just a sword.")); // Smells like a american burger with extra cheese.
          entity_2->Delete<TransformComponent>();
        }
      }

      if (entity_2->Contains<ArmorTagComponent>()) {
        auto ic = entity_1->Get<InventoryComponent>();
        if ((ic->getCurrentSize() < ic->getMaxSize()) && !entity_2->Get<OnPlaceComponent>()->getStatus()) {
          //ic->addItem(ItemComponent(entity_2->GetId(), "Armor", "Just a armor.")); // Smells like a american burger with extra cheese.
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

void CollisionSystem::OnPreUpdate() {
    // очистка коллизий (если используется)
}

void CollisionSystem::OnUpdate() {
    if (!game_state_.getPlayer()) return;

    Entity* player = game_state_.getPlayer();
    Vector2D playerPos = player->Get<TransformComponent>()->position_;
    std::vector<Entity*> toDelete;

    // 1. Коллизия игрока со всеми сущностями (можно оптимизировать, проверяя только потенциальные)
    for (auto& entity : GetEntityManager()) {
        if (entity.GetId() == player->GetId()) continue;
        if (!entity.Contains<TransformComponent>()) continue;
        if (entity.Get<TransformComponent>()->position_ == playerPos) {
            handlePlayerCollision(player, &entity, toDelete);
        }
    }

    // Удаляем собранные сущности
    for (Entity* e : toDelete) {
        GetEntityManager().DeleteEntity(e->GetId());
    }
    toDelete.clear();

    // 2. Коллизии врагов друг с другом (если нужны)
    for (auto& enemy1 : GetEntityManager()) {
        if (!enemy1.Contains<EnemyTagComponent>()) continue;
        if (!enemy1.Contains<TransformComponent>()) continue;

        Vector2D pos1 = enemy1.Get<TransformComponent>()->position_;

        for (auto& enemy2 : GetEntityManager()) {
            if (!enemy2.Contains<EnemyTagComponent>()) continue;
            if (!enemy2.Contains<TransformComponent>()) continue;
            if (enemy1.GetId() == enemy2.GetId()) continue;

            if (enemy2.Get<TransformComponent>()->position_ == pos1) {
                handleEnemyCollision(&enemy1, &enemy2);
            }
        }
    }

    // Очистка коллизий (если используется ColliderComponent)
    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<ColliderComponent>()) {
            entity.Get<ColliderComponent>()->Clear();
        }
    }
}

void CollisionSystem::handlePlayerCollision(Entity* player, Entity* other, std::vector<Entity*>& toDelete) {
    // --- Монеты ---
    if (other->Contains<MoneyTagComponent>()) {
        auto* wc_p = player->Get<WorthComponent>();
        auto* wc_o = other->Get<WorthComponent>();
        wc_p->setWorth(wc_p->getWorth() + wc_o->getWorth());
        toDelete.push_back(other);
        return;
    }

    // --- Предметы (еда, оружие, броня) ---
    if (other->Contains<ItemTagComponent>()) {
        auto* ic = player->Get<InventoryComponent>();
        if (ic->getCurrentSize() < ic->getMaxSize()) {
            // В зависимости от типа предмета добавляем в инвентарь
            // Пока упрощённо: просто удаляем предмет
            toDelete.push_back(other);
        }
        return;
    }

    // --- Стены ---
    if (other->Contains<ObstacleTagComponent>()) {
        auto* tc_p = player->Get<TransformComponent>();
        auto* cm_p = player->Get<ColliderComponent>();
        auto* sc_p = player->Get<StepComponent>();
        tc_p->position_ -= cm_p->offset_;  // откат
        sc_p->setSteps(sc_p->getSteps() - 1);
        return;
    }

    // --- Двери ---
    if (other->Contains<DoorTagComponent>()) {
        auto* oc = other->Get<OpenableComponent>();
        if (!oc->getStatus()) {
            // дверь закрыта — открываем или переключаем уровень
            auto* lc = other->Get<LevelComponent>();
            if (lc->getLevel() >= 8) {
                GetSystemManager().Enable<GameWinSystem>();
            }
            else {
                GetSystemManager().Enable<RoomsSwitchSystem>();
            }
        }
        else {
            // дверь открыта — проход, но если она открыта, можно пройти, но логика может быть другой
            // Пока сделаем откат (как стена)
            auto* tc_p = player->Get<TransformComponent>();
            auto* cm_p = player->Get<ColliderComponent>();
            auto* sc_p = player->Get<StepComponent>();
            tc_p->position_ -= cm_p->offset_;
            sc_p->setSteps(sc_p->getSteps() - 1);
        }
        return;
    }

    // --- Враги (бой) ---
    if (other->Contains<EnemyTagComponent>()) {
        auto* hc_p = player->Get<HealthComponent>();
        auto* dc_p = player->Get<DamageComponent>();
        auto* hc_e = other->Get<HealthComponent>();
        auto* dc_e = other->Get<DamageComponent>();
        auto* sc_p = player->Get<StepComponent>();
        sc_p->setSteps(sc_p->getSteps() - 1);

        while (hc_p->getHealth() > 0 && hc_e->getHealth() > 0) {
            hc_p->setHealth(hc_p->getHealth() - dc_e->getDamage());
            hc_e->setHealth(hc_e->getHealth() - dc_p->getDamage());
        }
        if (hc_e->getHealth() <= 0) {
            toDelete.push_back(other);
        }
        return;
    }
}

void CollisionSystem::handleEnemyCollision(Entity* enemy1, Entity* enemy2) {
    // Просто отталкиваем первого врага (можно добавить логику)
    auto* cm_e = enemy1->Get<ColliderComponent>();
    auto* tc_e = enemy1->Get<TransformComponent>();
    tc_e->position_ = cm_e->offset_;
}

void CollisionSystem::OnPostUpdate() {

}
