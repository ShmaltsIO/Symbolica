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
#include "Vector2DHash.h"

void CollisionSystem::OnPreUpdate() {
    // очистка коллизий (если используется)
}

void CollisionSystem::OnUpdate() {
    Entity* player = game_state_.getPlayer();
    if (!player) return;

    std::unordered_map<Vector2D, Entity*> positionMap;
    std::vector<Entity*> toDelete;

    // Проходим по всем сущностям с TransformComponent
    for (auto& entity : GetEntityManager()) {
        if (!entity.Contains<TransformComponent>()) continue;
        auto* tc = entity.Get<TransformComponent>();
        Vector2D pos = tc->position_;

        auto it = positionMap.find(pos);
        if (it != positionMap.end()) {
            // На этой позиции уже есть сущность – обрабатываем коллизию
            Entity* other = it->second;
            // Если одна из сущностей – игрок, вызываем handlePlayerCollision
            if (entity.Contains<PlayerTagComponent>()) {
                handlePlayerCollision(&entity, other, toDelete);
            }
            else if (other->Contains<PlayerTagComponent>()) {
                handlePlayerCollision(other, &entity, toDelete);
            }
            // Если обе враги – обрабатываем вражескую коллизию
            if (entity.Contains<EnemyTagComponent>() && other->Contains<EnemyTagComponent>()) {
                handleEnemyCollision(&entity, other);
            }
            // Можно также обработать другие случаи (например, предмет на предмете – не нужно)
        }
        else {
            // Если позиция свободна, добавляем сущность в карту
            positionMap.emplace(pos, &entity);
        }
    }

    // Удаляем собранные сущности
    for (Entity* e : toDelete) {
        GetEntityManager().DeleteEntity(e->GetId());
    }

    // Очистка коллизий (если используется)
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
