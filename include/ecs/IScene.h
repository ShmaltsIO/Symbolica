#ifndef ISCENE_H
#define ISCENE_H

#include "Context.h"

/**
 * @brief Interface for scenes.
 * 
 * Each scene can be create once.
 */
class IScene {
 protected:
  Context* const context_;

 public:
  /**
   * @brief All scenes have pointer to context for transition between scenes.
   */
  explicit IScene(Context* const);
  virtual ~IScene() = default;

  /**
   * @brief This function activated (once) on transiction to this scene.
   */
  virtual void OnCreate() = 0;
  /**
   * @brief This function work each tick.
   */
  virtual void OnRender() = 0;
  /**
   * @brief This function activated (once) on transiction from one scene to other.
   */
  virtual void OnExit() = 0;
};

#endif  // ISCENE_H
