#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Engine.h"
#include "IScene.h"
#include "Controls.h"
#include "Grid.h"

/**
 * @brief Game scene is main part of the game.
 * @param engine is TODO
 * @param controls is input's handle.
 * @param player_ is copy of player entity, used in transition between levels.
 * @param previous_level_ is code of previous level.
 */
class GameScene : public IScene {
private:
  const Engine engine{};
  const Controls& controls;
  Entity* player_ = nullptr; // Contains pointer to copied entity player
  Entity player_copy{0};
  std::string previous_level_ = "";
  Grid level_map{20, 20};

 public:
  GameScene(Context* const, const Controls&);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;

  void setPreviousLevel(std::string);
  std::string getPreviousLevel();
  std::string getPreviousLevel() const;

  // void updateLevelMap(Grid);
  // Grid getLevelMap();
  // Grid getLevelMap() const;
};

#endif  // GAME_SCENE_H
