#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <memory>

#include "Context.h"
#include "IScene.h"
#include "SceneType.h"

/**
 * @brief Scene manager conrols a life cycle of scenes.
 *
 * Transisiiton between scenes happenes when context is updating.
 */
class SceneManager {
private:
  std::map<SceneType, std::unique_ptr<IScene>> scenes_;
  const Context& ctx_;
  SceneType current_scene = SceneType::TitleScene;

 public:
  explicit SceneManager(const Context& ctx);
  SceneManager(SceneManager&&) = default;
  SceneManager& operator=(SceneManager&&) = default;
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;
  ~SceneManager() {
	  scenes_.clear();
  }

  void OnRender();
  void OnExit() const;

  /**
   * Method for adding new scene.
   * @param name is name of scene.
   * @param scene is pointer to scene.
   */
  void Put(const SceneType& name, IScene* scene);
};

#endif  // SCENE_MANAGER_H
