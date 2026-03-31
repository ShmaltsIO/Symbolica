#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include "ISystem.h"

/**
 * @brief System of movements.
 */
class MovementSystem : public ISystem {
 private:
  bool player_is_moved_ = false;
 public:
  MovementSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;
};

#endif  // MOVEMENT_SYSTEM_H
