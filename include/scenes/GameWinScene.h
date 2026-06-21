#ifndef GAME_WIN_SCENE_H
#define GAME_WIN_SCENE_H

#include <BearLibTerminal.h>

#include "IScene.h"
#include "Controls.h"
#include "SceneType.h"
#include "TxtReader.h"

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