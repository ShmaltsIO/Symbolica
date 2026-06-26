#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <TilemapConfig.h>
#include <unordered_map>

#include "UISettings.h"
#include "GameStatistics.h"
#include "GameState.h"
#include "SceneType.h"
#include "SpawnConfig.h"
#include "DungeonGenerator.h"
#include "ItemPrefab.h"

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

  UISettings* ui_settings = nullptr;
  TilemapConfig* tilemapConfig = nullptr; // или unique_ptr, но проще сырой указатель
  GameStatistics* game_stats = nullptr;
  GameState* game_state = nullptr;
  SpawnConfig* spawnConfig = nullptr;
  DungeonGenerator* dungeon_generator = nullptr;

  std::unordered_map<std::string, ItemPrefab> itemPrefabs;
};

#endif  // CONTEXT_H
