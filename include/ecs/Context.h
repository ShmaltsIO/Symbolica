#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>
#include <TilemapConfig.h>

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
  std::string scene_ = "";
  unsigned int score = 0;
  unsigned int steps_completed = 0;
  unsigned int money_collected_ = 0;
  unsigned int enemies_beaten_ = 0;
  unsigned int room_ = 1;
  bool is_load = false;
  bool is_game_over = false;
  bool is_start = false;
  TilemapConfig* tilemapConfig = nullptr; // или unique_ptr, но проще сырой указатель
  // map for statistics
};

#endif  // CONTEXT_H
