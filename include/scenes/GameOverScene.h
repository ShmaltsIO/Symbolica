#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include <BearLibTerminal.h>

#include "IScene.h"
#include "Controls.h"
#include "SceneType.h"
#include "TxtReader.h"

class GameOverScene : public IScene {
private:
  const Controls& controls_;

 public:
  GameOverScene(Context* ctx, const Controls& controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // GAME_OVER_SCENE_H
