#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "ISystem.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "Entity.h"
#include "GameState.h"

/**
 * @brief System of collisions.
 */
class CollisionSystem: public ISystem {
private:  
    const GameState& game_state_;

    void handlePlayerCollision(Entity* player, Entity* other, std::vector<Entity*>& toDelete);
    void handleEnemyCollision(Entity* enemy, Entity* other);

protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

public:
  CollisionSystem(EntityManager* entity_manager, SystemManager* system_manager, const GameState& game_state):
      ISystem(entity_manager, system_manager), game_state_(game_state) { }

};

#endif  // COLLISION_SYSTEM_H
