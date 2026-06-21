#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <BearLibTerminal.h>
#include <iostream>

#include "IScene.h"
#include "Controls.h"
#include "SceneType.h"
#include "TxtReader.h"

class TitleScene : public IScene {
private:
  const Controls& controls_;
  bool is_start = true;
  int offset = 5;

public:
  TitleScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // TITLE_SCENE_H
