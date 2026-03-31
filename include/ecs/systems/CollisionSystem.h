#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "ISystem.h"
#include "Entity.h"

/**
 * @brief System of collisions.
 */
class CollisionSystem: public ISystem {
private:  
  void Collide(Entity*, Entity*);

protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

public:
  CollisionSystem(EntityManager* entity_manager, SystemManager* system_manager);

};

#endif  // COLLISION_SYSTEM_H
