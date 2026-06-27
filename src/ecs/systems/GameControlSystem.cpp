#include "GameControlSystem.h"

#include "SystemManager.h" // what the...

#include "CollisionSystem.h"
#include "GameOverSystem.h"
#include "LevelSystem.h"
#include "MovementSystem.h"
// #include "ObstaclesControlSystem.h"
#include "PlayerControlSystem.h"
#include "BattleSystem.h"
#include "AIcontrolsSystem.h"
#include "RadiusUpdateSystem.h"
#include "RoomsSwitchSystem.h"
#include "InventoryRenderingSystem.h"
#include "RenderingSystem.h"
#include "InventoryControlSystem.h"

GameControlSystem::GameControlSystem(EntityManager* entity_manager, SystemManager* system_manager,
 const Controls& controls):
 ISystem(entity_manager, system_manager), controls_(controls) {}

void GameControlSystem::stop_game() {
    auto sm = GetSystemManagerPtr();
    sm->Disable<CollisionSystem>();
    sm->Disable<GameOverSystem>();
    sm->Disable<LevelSystem>();
    sm->Disable<MovementSystem>();
    sm->Disable<AIcontrolsSystem>();
    sm->Disable<BattleSystem>();
    sm->Disable<RoomsSwitchSystem>();
    // sm->Disable<RadiusUpdateSystem>();
    // sm->Disable<ObstaclesControlSystem>();
    sm->Disable<PlayerControlSystem>();
}

void GameControlSystem::continue_game() {
    auto sm = GetSystemManagerPtr();
    sm->Enable<CollisionSystem>();
    sm->Enable<GameOverSystem>();
    sm->Enable<LevelSystem>();
    sm->Enable<MovementSystem>();
    sm->Enable<AIcontrolsSystem>();
    sm->Enable<BattleSystem>();
    sm->Enable<RoomsSwitchSystem>();
    // sm->Enable<ObstaclesControlSystem>();
    sm->Enable<PlayerControlSystem>();
}

void GameControlSystem::OnPreUpdate() {
    if (is_pause_ && lock_) {
        //std::cout << "Im HERE OnPreUpdate" << std::endl;
        // Disable Systems
        stop_game();
        lock_ = false;
    }
}

void GameControlSystem::OnUpdate() {
    // TODO: each tick you en/dis -able this systems... needs opitimation by spec. bool signal
    // std::cout << "Im HERE OnUpdate" << std::endl;
    if (controls_.IsPressed(TK_E) && !is_pause_) {
        auto sm = GetSystemManagerPtr();
        is_inventory_interface = !is_inventory_interface;
        if (is_inventory_interface) {
            terminal_composition(TK_OFF);
            sm->Enable<InventoryRenderingSystem>();
            sm->Enable<InventoryControlSystem>();
            sm->Disable<RenderingSystem>();
            stop_game();
        } else {
            terminal_composition(TK_ON);
            sm->Disable<InventoryRenderingSystem>();
            sm->Disable<InventoryControlSystem>();
            sm->Enable<RenderingSystem>();
            continue_game();
        }
    }

    if ((controls_.IsPressed(TK_P) || controls_.IsPressed(TK_ESCAPE)) && !is_inventory_interface) {
        is_pause_ = !is_pause_;
    }
    if (is_pause_) {
        // NEAR --- TODO: think about where rendering this menu, and maybe create this in system as field? Or it can be not a scene
        // Now menu lie in GameScene, and i'n not start game...
        terminal_layer(250);
        terminal_print(10, 10, "--- PAUSЕ ---");
        terminal_refresh();
    }
}

void GameControlSystem::OnPostUpdate() {
    if (!is_pause_ && !lock_) {
        // std::cout << "Im HERE OnPostUpdate" << std::endl;
        // Enable systems
        continue_game();
        lock_ = true;
    }
}
