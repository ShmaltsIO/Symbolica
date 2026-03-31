#include "RenderingSystem.h"
#include <BearLibTerminal.h>
#include "EntityManager.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "WorthComponent.h"
#include "HealthComponent.h"
#include "SystemManager.h"
#include "MovementSystem.h"
#include "StepComponent.h"
#include "GroundTagComponent.h"
#include "PlayerTagComponent.h"
#include "FoodTagComponent.h"
#include "MoneyTagComponent.h"
#include "ObstacleTagComponent.h"
#include "ObserverTagComponent.h"
#include "StepLimitComponent.h"
#include "ColorComponent.h"
#include "EnemyTagComponent.h"
#include "PathToTargetComponent.h"
#include "RadiusComponent.h"
#include "DoorTagComponent.h"
#include "ItemTagComponent.h"
#include "EquipmentComponent.h"

RenderingSystem::RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

std::string RenderingSystem::getModifiedString(const Entity& entity) {
  return addColor(entity);
}

std::string RenderingSystem::addColor(const Entity& entity) {
  auto texture = entity.Get<TextureComponent>();
  auto color = entity.Get<ColorComponent>();
  std::string result = "[color=" + color->getColor() + "]" + texture->symbol_ + "[/color]";
  
  return result;
}

void RenderingSystem::OnPreUpdate() {
  terminal_clear();
}

void RenderingSystem::OnUpdate() {
  // Ground and walls is 0 layer
  terminal_layer(0);
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<GroundTagComponent>() || entity.Contains<ObstacleTagComponent>() || entity.Contains<DoorTagComponent>()) {
      auto transform = entity.Get<TransformComponent>();
      
      std::string color = getModifiedString(entity);

      terminal_print(transform->position_.getX(), transform->position_.getY(), color.c_str());
    }
  }


  // Items layer is 1
  terminal_layer(1);
  for (auto& entity : GetEntityManager()) {
    if ((entity.Contains<ItemTagComponent>() || entity.Contains<MoneyTagComponent>()) && entity.Contains<TransformComponent>()) {
      auto transform = entity.Get<TransformComponent>();

      std::string color = getModifiedString(entity);

      terminal_print(transform->position_.getX(), transform->position_.getY(), color.c_str());
    }
  }

  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<PlayerTagComponent>() || entity.Contains<EnemyTagComponent>()) {
      auto transform = entity.Get<TransformComponent>();

      std::string color = getModifiedString(entity);
    
      terminal_print(transform->position_.getX(), transform->position_.getY(), color.c_str());

      if (entity.Contains<PlayerTagComponent>()) {
        auto ec_p = entity.Get<EquipmentComponent>();
        // TODO: create for to pairs, and if second is not 0, print first...
        if (ec_p->getChest() != 0) {
          auto item = GetEntityManager().Get(ec_p->getChest());

          std::string item_color = getModifiedString(*item);

          terminal_print(transform->position_.getX(), transform->position_.getY(), item_color.c_str());
        }

        if (ec_p->getRightHand() != 0) {
          auto item = GetEntityManager().Get(ec_p->getRightHand());

          std::string item_color = getModifiedString(*item);
          std::cout << item_color << std::endl;

          terminal_print(transform->position_.getX(), transform->position_.getY(), item_color.c_str());
        }
      }
    }
  }

  // TODO: It can be more beautiful..
  // Game stats is 2 layer
  terminal_layer(3);
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<PlayerTagComponent>()) {
      auto wc = entity.Get<WorthComponent>();
      auto hc = entity.Get<HealthComponent>();
      auto sc = entity.Get<StepComponent>();
      // Observer...
      auto observer = GetEntityManager().Get(3);
      auto lsc = observer->Get<StepLimitComponent>();

      terminal_printf(0, 0, "Money: %d", wc->getWorth());
      terminal_printf(15, 0, "Healht: %d", hc->getHealth());
      if (sc->getSteps() >= lsc->getStepLimit() / 2) {
        terminal_printf(30, 0, "Steps: [color=red]%d[/color]/%d", sc->getSteps(), lsc->getStepLimit());
      } else {
        terminal_printf(30, 0, "Steps: %d/%d", sc->getSteps(), lsc->getStepLimit());
      }
      
      
      break; // if del the next if
    }
    // if (entity.Contains<DoorTagComponent>()) {
    //   auto wc = entity.Get<WorthComponent>();

    //   terminal_printf(45, 0, "Next level's pay: %d", wc->getWorth());
    // }
  }

  terminal_layer(5);
  // TEST
  
  // Render path from enemy to player... just a funny :)
  // TODO: create a bool field, that's will enable this if player did cheats ON
  // for (auto& en : GetEntityManager()) {
  //   if (en.Contains<EnemyTagComponent>()) {
  //     auto pttc_e = en.Get<PathToTargetComponent>();
    
  //     for (auto& v : pttc_e->getPathToTarget()) {
  //       terminal_print(v.getX(), v.getY(), "[color=blue]0[/color]");
  //     }
  //   }
  // }

  // Visualizate radius of player
  // for (auto& en : GetEntityManager()) {
  //   if (en.Contains<PlayerTagComponent>()) {
  //     auto rc_p = en.Get<RadiusComponent>();

  //     for (auto& p : rc_p->getNeighborhood()) {
  //       auto pos = GetEntityManager().Get(p)->Get<TransformComponent>()->position_;
  //       terminal_print(pos.getX(), pos.getY(), "[color=purple]0[/color]");
  //     }
  //   }
  // }
  // ---
}

void RenderingSystem::OnPostUpdate() {
  terminal_refresh();
}

