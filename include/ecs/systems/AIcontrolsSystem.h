#ifndef AI_CONTROLS_SYSTEM_H
#define AI_CONTROLS_SYSTEM_H

#include "ISystem.h"
#include "GameState.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "SightRadiusComponent.h"
#include "EnemyTagComponent.h"
#include "TransformComponent.h"
#include "PathToTargetComponent.h"
#include "aStar.h"

class AIcontrolsSystem : public ISystem {
private:
    GameState* game_state_ = nullptr;

public:
    AIcontrolsSystem(EntityManager* entity_manager, SystemManager* system_manager, GameState* game_state):
    ISystem(entity_manager, system_manager), game_state_(game_state) { }
    
    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;
};

#endif