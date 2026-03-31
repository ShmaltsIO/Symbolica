#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <memory>

#include "Context.h"
#include "IScene.h"

/**
 * @brief Scene manager conrols a life cycle of scenes.
 *
 * Transisiiton between scenes happenes when context is updating.
 */
class SceneManager {
private:
  std::map<std::string, std::unique_ptr<IScene>> scenes_;
  const Context& ctx_;
  std::string current_scene_ = "";

 public:
  explicit SceneManager(const Context& ctx);

  void OnRender();
  void OnExit() const;

  /**
   * Method for adding new scene.
   * @param name is name of scene.
   * @param scene is pointer to scene.
   */
  void Put(const std::string& name, IScene* scene);
};

#endif  // SCENE_MANAGER_H
