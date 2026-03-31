#include "ObstaclesControlSystem.h"

#include "EntityManager.h"
#include "ObstacleTagComponent.h"
#include "TransformComponent.h"

bool ObstaclesControlSystem::Filter(const Entity& entity) const {
  return entity.Contains<ObstacleTagComponent>() && entity.Contains<TransformComponent>();
}
void ObstaclesControlSystem::OnEachEntity(Entity* entity) const {
  auto tc = entity->Get<TransformComponent>();

  if (tc->position_.getX() < 0) {
    //tc->position_.x = starting_point_;
    tc->position_.setX(starting_point_);
  }
}
void ObstaclesControlSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      OnEachEntity(&entity);
    }
  }
}
ObstaclesControlSystem::ObstaclesControlSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                               float starting_point)
    : ISystem(entity_manager, system_manager), starting_point_(starting_point) {}
