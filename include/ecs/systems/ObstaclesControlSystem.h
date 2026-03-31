#ifndef OBSTACLES_CONTROL_SYSTEM_H
#define OBSTACLES_CONTROL_SYSTEM_H

#include "ISystem.h"
#include "Entity.h"

// TODO: That's can be useful?...
class ObstaclesControlSystem : public ISystem {
  float starting_point_;

  bool Filter(const Entity& entity) const;
  void OnEachEntity(Entity* entity) const;

 public:
  ObstaclesControlSystem(EntityManager* entity_manager, SystemManager* system_manager, float starting_point);

 protected:
  void OnUpdate() override;
};

#endif  // OBSTACLES_CONTROL_SYSTEM_H
