#include "SaveConverter.h"

PlayerSaveData SaveConverter::toSaveData(const EntityManager& em, const Context& ctx) {
    PlayerSaveData data;

    // Ищем игрока
    const Entity* player = nullptr;
    for (const auto& entity : em) {
        if (entity.Contains<PlayerTagComponent>()) {
            player = &entity;
            break;
        }
    }
    if (!player) return data;

    // Основные характеристики
    data.health = player->Get<HealthComponent>()->getHealth();
    data.maxHealth = player->Get<HealthComponent>()->getHealthLimit();
    data.damage = player->Get<DamageComponent>()->getDamage();
    data.protection = player->Get<ProtectionComponent>()->getProtection();
    data.level = player->Get<LevelComponent>()->getLevel();
    data.experience = player->Get<ExperienceComponent>()->getExperience();
    data.cash = player->Get<WorthComponent>()->getWorth();
    data.position = player->Get<TransformComponent>()->position_;

    // Текущий уровень
    if (ctx.game_state) {
        data.currentLevelId = ctx.game_state->getRoomNumber();
    }

    // Инвентарь
    const auto* invComp = player->Get<InventoryComponent>();
    if (invComp) {
        for (const auto& item : invComp->getInventory()) {
            ItemData itemData;
            itemData.prefabId = item.getPrefabId();
            itemData.count = item.getCount();
            itemData.stats.damage = item.getStats().damage;
            itemData.stats.health = item.getStats().health;
            itemData.stats.protection = item.getStats().protection;
            itemData.stats.worth = item.getStats().worth;
            data.inventory.push_back(itemData);
        }
    }

    return data;
}

void SaveConverter::fromSaveData(const PlayerSaveData& data, EntityManager& em, Context& ctx) {
    // Находим игрока
    Entity* player = nullptr;
    for (auto& entity : em) {
        if (entity.Contains<PlayerTagComponent>()) {
            player = &entity;
            break;
        }
    }
    if (!player) return;

    // Устанавливаем характеристики
    player->Get<HealthComponent>()->setHealth(data.health);
    player->Get<HealthComponent>()->setHealthLimit(data.maxHealth);
    player->Get<DamageComponent>()->setDamage(data.damage);
    player->Get<ProtectionComponent>()->setProtection(data.protection);
    player->Get<LevelComponent>()->setLevel(data.level);
    player->Get<ExperienceComponent>()->setExperience(data.experience);
    player->Get<WorthComponent>()->setWorth(data.cash);
    player->Get<TransformComponent>()->position_ = data.position;

    // Восстанавливаем инвентарь (очищаем и заполняем заново)
    auto* invComp = player->Get<InventoryComponent>();
    if (invComp) {
        while (invComp->getCurrentSize() > 0) {
            invComp->removeItem(0, 1);
        }
        for (const auto& itemData : data.inventory) {
            invComp->addItem(itemData.prefabId, itemData.count, itemData.stats);
        }
    }

    // Устанавливаем текущий уровень
    if (ctx.game_state) {
        ctx.game_state->setRoomNumber(data.currentLevelId);
        // levelsState пока пропущено
    }
}