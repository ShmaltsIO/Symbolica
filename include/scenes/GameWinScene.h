#ifndef GAME_WIN_SCENE_H
#define GAME_WIN_SCENE_H

#include "IScene.h"
#include "Controls.h"

class GameWinScene: public IScene {
private:
    const Controls& controls_;

public:
  GameWinScene(Context*, const Controls&);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif // GAME_WIN_SCENE_H