#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(const Context& ctx) : ctx_(ctx) {}

void SceneManager::OnRender() {
  if (ctx_.scene != current_scene) {
    // std::cout << "Transition from '" << ctx_.scene_ << "' to '" << current_scene_ << "'" << std::endl;
    if (scenes_.count(current_scene) != 0) {
      scenes_.at(current_scene)->OnExit();
    }
    current_scene = ctx_.scene;
    scenes_.at(current_scene)->OnCreate();
  }
  if (scenes_.count(current_scene) != 0) {
    scenes_.at(current_scene)->OnRender();
  } else {
    // ERROR: scene not exist
  }
}

void SceneManager::OnExit() const {
  if (scenes_.count(current_scene) != 0) {
    scenes_.at(current_scene)->OnExit();
  }
}

void SceneManager::Put(const SceneType& name, IScene* const scene) {
  scenes_[name] = std::unique_ptr<IScene>(scene);
}
