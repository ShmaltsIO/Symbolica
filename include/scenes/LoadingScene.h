#ifndef LOADING_SCENE_H
#define LOADING_SCENE_H

#include "IScene.h"

class LoadingScene: public IScene {
public:
  LoadingScene(Context*);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif // LOADING_SCENE_H