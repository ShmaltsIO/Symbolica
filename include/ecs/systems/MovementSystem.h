#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <unordered_set>

#include "ISystem.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "PathToTargetComponent.h"
#include "EnemyTagComponent.h"
#include "GameState.h"
#include "Vector2DHash.h"
#include "ItemTagComponent.h"

/**
 * @brief System of movements.
 */
class MovementSystem : public ISystem {
 private:
  bool player_is_moved_ = false;
  const GameState& game_state_;

 public:
  MovementSystem(EntityManager* entity_manager, SystemManager* system_manager, const GameState& game_state):
	  ISystem(entity_manager, system_manager), game_state_(game_state) { }

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;
};

#endif  // MOVEMENT_SYSTEM_H
