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

std::string RenderingSystem::getModifiedString(const Entity& entity) {
  return addColor(entity);
}

std::string RenderingSystem::addColor(const Entity& entity) {
  auto texture = entity.Get<TextureComponent>();
  auto color = entity.Get<ColorComponent>();
  std::string result = "[color=" + color->getColor() + "]" + texture->symbol_ + "[/color]";
  
  return result;
}

// ----------------------------------------------------------------------------
std::string RenderingSystem::getEntityString(const Entity& entity) const {
    auto* texture = entity.Get<TextureComponent>();
    auto* color = entity.Get<ColorComponent>();
    if (!texture || !color) return "";
    return "[color=" + color->getColor() + "]" + texture->symbol_ + "[/color]";
}

// ----------------------------------------------------------------------------
void RenderingSystem::renderLayer0() {
    /*terminal_layer(0);
    for (const auto& entity : GetEntityManager()) {
        if (entity.Contains<GroundTagComponent>() ||
            entity.Contains<ObstacleTagComponent>() ||
            entity.Contains<DoorTagComponent>()) {
            auto* transform = entity.Get<TransformComponent>();
            if (transform) {
                terminal_print(transform->position_.getX(),
                    transform->position_.getY(),
                    getEntityString(entity).c_str());
            }
        }
    }*/

    terminal_layer(0);
    auto* map = game_state_->getCurrentMap();
    if (!map) return;
    for (size_t y = 0; y < map->getHeight(); ++y) {
        for (size_t x = 0; x < map->getWidth(); ++x) {
            TileType tile = map->getTile(x, y);
            char symbol = (tile == TileType::WALL) ? '#' : '.';
            std::string color = (tile == TileType::WALL) ? "gray" : "dark green";
            std::string str = "[color=" + color + "]" + symbol + "[/color]";
            terminal_print(x, y, str.c_str());
        }
    }
}

// ----------------------------------------------------------------------------
void RenderingSystem::renderLayer1() {
    terminal_layer(1);
    for (const auto& entity : GetEntityManager()) {
        if ((entity.Contains<ItemTagComponent>() || entity.Contains<MoneyTagComponent>()) &&
            entity.Contains<TransformComponent>()) {
            auto* transform = entity.Get<TransformComponent>();
            terminal_print(transform->position_.getX(),
                transform->position_.getY(),
                getEntityString(entity).c_str());
        }
    }
}

// ----------------------------------------------------------------------------
void RenderingSystem::renderLayer2() {
    terminal_layer(2);
    for (const auto& entity : GetEntityManager()) {
        if (entity.Contains<PlayerTagComponent>() || entity.Contains<EnemyTagComponent>()) {
            auto* transform = entity.Get<TransformComponent>();
            if (!transform) continue;

            // Рисуем саму сущность
            terminal_print(transform->position_.getX(),
                transform->position_.getY(),
                getEntityString(entity).c_str());

            // Если это игрок – рисуем экипировку поверх
            if (entity.Contains<PlayerTagComponent>()) {
                auto* equipment = entity.Get<EquipmentComponent>();
                if (equipment) {
                    // Грудь
                    if (equipment->getChest() != 0) {
                        auto* item = GetEntityManager().Get(equipment->getChest());
                        if (item) {
                            terminal_print(transform->position_.getX(),
                                transform->position_.getY(),
                                getEntityString(*item).c_str());
                        }
                    }
                    // Правая рука
                    if (equipment->getRightHand() != 0) {
                        auto* item = GetEntityManager().Get(equipment->getRightHand());
                        if (item) {
                            terminal_print(transform->position_.getX(),
                                transform->position_.getY(),
                                getEntityString(*item).c_str());
                        }
                    }
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------
void RenderingSystem::renderStats() {
    if (!game_state_) return;
    Entity* player = game_state_->getPlayer();
    if (!player) return;

    auto* worth = player->Get<WorthComponent>();
    auto* health = player->Get<HealthComponent>();
    auto* steps = player->Get<StepComponent>();

    // Поиск наблюдателя для лимита шагов
    int stepLimit = 100; // запасное значение
    for (const auto& entity : GetEntityManager()) {
        if (entity.Contains<ObserverTagComponent>()) {
            auto* limit = entity.Get<StepLimitComponent>();
            if (limit) {
                stepLimit = limit->getStepLimit();
                break;
            }
        }
    }

    terminal_layer(3);
    if (worth)  terminal_printf(0, 0, "Money: %d", worth->getWorth());
    if (health) terminal_printf(15, 0, "Health: %d", health->getHealth());
    if (steps) {
        int current = steps->getSteps();
        if (current >= stepLimit / 2) {
            terminal_printf(30, 0, "Steps: [color=red]%d[/color]/%d", current, stepLimit);
        }
        else {
            terminal_printf(30, 0, "Steps: %d/%d", current, stepLimit);
        }
    }
}

// ----------------------------------------------------------------------------
void RenderingSystem::OnPreUpdate() {
    terminal_clear();
}

// ----------------------------------------------------------------------------
void RenderingSystem::OnUpdate() {
    renderLayer0();
    renderLayer1();
    renderLayer2();
    renderStats();
    // Можно добавить дополнительный слой для отладки (слой 5), но пока пусто
}

// ----------------------------------------------------------------------------
void RenderingSystem::OnPostUpdate() {
    terminal_refresh();
}