#include <iostream>
#include <memory>

#include "EntityManager.h"
#include "EntityFabric.h"
#include "SavePlayerReader.h"
#include "SavePlayerWriter.h"
#include "SaveConverter.h"
#include "Context.h"
#include "InventoryComponent.h"

void testSaveLoad() {
    // 1. Контекст и менеджер сущностей
    Context ctx;
    EntityManager em;
    EntityFabric fabric(&em);
    ctx.game_state = std::make_unique<GameState>();  // чтобы не было nullptr

    // 2. Создаём игрока с данными
    Entity* player = fabric.createPlayer();
    player->Get<TransformComponent>()->position_ = Vector2D(5, 10);
    player->Get<HealthComponent>()->setHealth(30);
    player->Get<LevelComponent>()->setLevel(3);
    player->Get<WorthComponent>()->setWorth(100);

    // 3. Добавляем предметы в инвентарь
    auto* inv = player->Get<InventoryComponent>();
    ItemStats stats1{ 0, 10, 0, 5 };  // heal, damage, protection, worth
    inv->addItem("health_potion", 2, stats1);
    ItemStats stats2{ 0, 5, 1, 20 }; // меч
    inv->addItem("sword", 1, stats2);

    // 4. Сохраняем в файл
    PlayerSaveData saveData = SaveConverter::toSaveData(em, ctx);
    SavePlayerWriter writer;
    writer.setPathToFile("test_save.json");
    writer.write(saveData);
    std::cout << "DONE\n";

    // 5. Удаляем игрока, чтобы проверить загрузку с нуля
    em.DeleteAll();
    // Создаём нового (пустого) игрока, чтобы потом загрузить в него данные
    Entity* newPlayer = fabric.createPlayer();
    // Сбрасываем контекст (если нужно)

    // 6. Загружаем сохранение
    SavePlayerReader reader;
    reader.setPathToFile("test_save.json");
    if (reader.fileExists()) {
        PlayerSaveData loaded = reader.read();
        SaveConverter::fromSaveData(loaded, em, ctx);
        std::cout << "LOAD DONE.\n";
    }
    else {
        std::cout << "NOOOOOOO.\n";
        return;
    }

    // 7. Проверяем загруженные данные
    Entity* loadedPlayer = nullptr;
    for (auto& entity : em) {
        if (entity.Contains<PlayerTagComponent>()) {
            loadedPlayer = &entity;
            break;
        }
    }
    if (loadedPlayer) {
        std::cout << "" << loadedPlayer->Get<HealthComponent>()->getHealth() << "\n";
        std::cout << "" << loadedPlayer->Get<TransformComponent>()->position_.getX()
            << ", " << loadedPlayer->Get<TransformComponent>()->position_.getY() << "\n";
        std::cout << "" << loadedPlayer->Get<LevelComponent>()->getLevel() << "\n";
        std::cout << "" << loadedPlayer->Get<WorthComponent>()->getWorth() << "\n";
        auto* invLoaded = loadedPlayer->Get<InventoryComponent>();
        std::cout << "" << invLoaded->getCurrentSize() << "\n";
        for (const auto& item : invLoaded->getInventory()) {
            std::cout << "  - " << item.getPrefabId() << " x" << item.getCount()
                << " " << item.getStats().damage
                << "," << item.getStats().health << ")\n";
        }
    }
    else {
        std::cout << "Player not found\n";
    }
}