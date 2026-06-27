#include "GameScene.h"

// Компоненты
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "ColorComponent.h"
#include "HealthComponent.h"
#include "DamageComponent.h"
#include "ProtectionComponent.h"
#include "LevelComponent.h"
#include "ExperienceComponent.h"
#include "WorthComponent.h"
#include "StepComponent.h"
#include "InventoryComponent.h"
#include "EquipmentComponent.h"
#include "ColliderComponent.h"
#include "MovementComponent.h"
#include "LocationComponent.h"
#include "RadiusComponent.h"
#include "NameComponent.h"
#include "OnPlaceComponent.h"

// Теги
#include "PlayerTagComponent.h"
#include "ObstacleTagComponent.h"
#include "GroundTagComponent.h"
#include "EnemyTagComponent.h"
#include "DoorTagComponent.h"
#include "ItemTagComponent.h"
#include "MoneyTagComponent.h"
#include "FoodTagComponent.h"
#include "WeaponTagComponent.h"
#include "ArmorTagComponent.h"
#include "ObserverTagComponent.h"

// Системы
#include "RenderingSystem.h"
#include "PlayerControlSystem.h"
#include "MovementSystem.h"
#include "CollisionSystem.h"
#include "LevelSystem.h"
#include "GameOverSystem.h"
#include "GameControlSystem.h"
#include "GameWinSystem.h"
#include "AIcontrolsSystem.h"
#include "RadiusUpdateSystem.h"
#include "RoomsSwitchSystem.h"
#include "BattleSystem.h"
#include "InventoryRenderingSystem.h"
#include "InventoryControlSystem.h"

// Утилиты
#include "SaveConverter.h"
#include "LevelGenerator.h"
#include "EntityFabric.h"
#include "GameState.h"
#include "SavePlayerReader.h"
#include "SavePlayerWriter.h"

// Константы
#include "TileType.h"
#include "GameObjectsTexture.h"

#include <iostream>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

GameScene::GameScene(Context* context, const Controls& controls)
    : IScene(context), controls_(controls) {
}

void GameScene::OnCreate() {
    // Добавляем системы один раз (при создании сцены)
    auto sys = context_->engine->GetSystemManager();

    sys->AddSystem<RenderingSystem>(context_->game_state.get());
    sys->AddSystem<PlayerControlSystem>(controls_, *context_->game_state.get());
    sys->AddSystem<MovementSystem>(*context_->game_state.get());
    sys->AddSystem<CollisionSystem>(*context_->game_state.get());
    sys->AddSystem<LevelSystem>();
    sys->AddSystem<GameOverSystem>(context_);
    sys->AddSystem<GameControlSystem>(controls_);
    sys->AddSystem<GameWinSystem>(context_);
    sys->AddSystem<AIcontrolsSystem>(context_);
    sys->AddSystem<RadiusUpdateSystem>();
    sys->AddSystem<RoomsSwitchSystem>(context_);
    sys->AddSystem<BattleSystem>();
    sys->AddSystem<InventoryRenderingSystem>();
    sys->AddSystem<InventoryControlSystem>(controls_);

    sys->EnableAll();

    sys->Disable<GameWinSystem>();
    sys->Disable<InventoryRenderingSystem>();

    // Загружаем первый уровень
    currentLevelId_ = context_->game_state->getRoomNumber();
    loadLevel(currentLevelId_);
}

void GameScene::loadLevel(int levelNumber) {
    auto* entityManager = context_->engine->GetEntityManager();
    auto* systemManager = context_->engine->GetSystemManager();

    // Сохраняем состояние игрока (если он существует)
    PlayerSaveData saveData;
    Entity* oldPlayer = nullptr;
    for (auto& entity : *entityManager) {
        if (entity.Contains<PlayerTagComponent>()) {
            oldPlayer = &entity;
            break;
        }
    }

    if (oldPlayer) {
        // Сохраняем данные игрока (кроме позиции – её зададим заново)
        saveData = SaveConverter::toSaveData(*entityManager, *context_);
        // Очищаем старые сущности (кроме игрока, но мы его сохранили, можно удалить всё)
        entityManager->DeleteAll();
    }


    std::string levelPath = "levels/level_" + std::to_string(levelNumber) + "/map.json";
    if (fs::exists(levelPath)) {
        LevelReader reader;
        reader.setPathToFile(levelPath);
        Map map = reader.read();        // загрузка из файла
        context_->game_state->setCurrentMap(std::make_unique<Map>(std::move(map)));
    }
    else {
        // Генерируем новый уровень
        auto* levelGen = context_->level_generator;
        if (!levelGen) {
            std::cerr << "LevelGenerator is null!" << std::endl;
            return;
        }

        // Генерация карты и сущностей (кроме игрока)
        Map map = levelGen->generateLevel(80, 40, levelNumber);
        levelGen->getRoomFiller().getEntityFabric()->createMapTiles(map, 1);

        LevelWriter writer;
        writer.setPathToFile(levelPath);
        writer.write(map);
        context_->game_state->setCurrentMap(std::make_unique<Map>(std::move(map)));
    }
    
    // Создаём игрока
    EntityFabric fabric(entityManager);
    Entity* player = fabric.createPlayer();
    // Устанавливаем начальную позицию (например, в центре первой комнаты)
    // Пока ставим в (5,5) – позже нужно будет получить из карты
    player->Get<TransformComponent>()->position_ = Vector2D(10, 5);

    // Если есть сохранённые данные – восстанавливаем их (кроме позиции)
    if (oldPlayer) {
        // Устанавливаем сохранённые характеристики (здоровье, опыт, инвентарь)
        // Но позицию оставляем новую
        SaveConverter::fromSaveData(saveData, *entityManager, *context_);
        // После fromSaveData игрок перезаписывается, но его позиция будет из saveData,
        // поэтому мы её переустанавливаем вручную
        player->Get<TransformComponent>()->position_ = Vector2D(5, 5);
    }

    // Включаем необходимые системы (если они были отключены)
    systemManager->Enable<GameControlSystem>();
    systemManager->Enable<MovementSystem>();
    systemManager->Enable<CollisionSystem>();
    // и т.д.

    // Создаём наблюдателя (Observer) для проверки условий победы/поражения
    Entity* observer = entityManager->CreateEntity();
    observer->Add<ObserverTagComponent>();
    observer->Add<TransformComponent>(Vector2D(0, 0));
    observer->Add<StepLimitComponent>(100);

    context_->game_state.get()->setObserver(observer);
    context_->game_state.get()->setPlayer(player);

    levelLoaded_ = true;
    currentLevelId_ = levelNumber;
}

void GameScene::clearLevel() {
    auto* entityManager = context_->engine->GetEntityManager();
    entityManager->DeleteAll();
    // Можно также сбросить карту в GameState
    context_->game_state->setCurrentMap(nullptr);
    levelLoaded_ = false;
}

void GameScene::OnRender() {
    // Обновляем движок
    context_->engine->OnUpdate();
    
    // Проверяем, не изменился ли номер уровня (например, через RoomsSwitchSystem)
    int newLevelId = context_->game_state->getRoomNumber();
    if (newLevelId != currentLevelId_) {
        // Переход на новый уровень
        loadLevel(newLevelId);
    }
}

void GameScene::OnExit() {
    // Сохраняем состояние перед выходом
    SavePlayerWriter writer;
    writer.setPathToFile("saves/savegame.json");
    PlayerSaveData saveData = SaveConverter::toSaveData(*context_->engine->GetEntityManager(), *context_);
    writer.write(saveData);

    // Очищаем уровень
    clearLevel();

    // Отключаем системы (по желанию)
    auto* sys = context_->engine->GetSystemManager();
    sys->DisableAll();
}