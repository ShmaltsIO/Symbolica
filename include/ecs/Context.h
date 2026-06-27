#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <unordered_map>
#include <memory>

#include "UISettings.h"
#include "GameStatistics.h"
#include "GameState.h"
#include "SceneType.h"
#include "SpawnConfig.h"
#include "ItemPrefab.h"
#include "LevelGenerator.h"
#include "Engine.h"
#include "TilemapConfig.h"

/**
 * @brief Context have information about actual scene, which should be displayed now.
 * 
 * Also uses how container of some information between game's levels.
 * @param scene_ is actual scene.
 * @param score_ is player's scores.
 * @param steps_completed is quantity of completed steps of player.
 * @param money_collected_ is quantity of collected coins.
 * @param enemies_beaten is quantity of beaten enemies.
 * @param chests_opened_ is quantity of opened chests.
 * @param room_ is current game level.
 */
class Context {
 public:
  SceneType scene = SceneType::TitleScene;

  std::unique_ptr<Engine> engine;
  std::unique_ptr<UISettings> ui_settings;
  std::unique_ptr<GameState> game_state;
  std::unique_ptr<GameStatistics> game_stats;

  TilemapConfig* tilemapConfig = nullptr; // или unique_ptr, но проще сырой указатель
  SpawnConfig* spawnConfig = nullptr;
  LevelGenerator* level_generator = nullptr;

  std::unordered_map<std::string, ItemPrefab> itemPrefabs;
};

#endif  // CONTEXT_H
