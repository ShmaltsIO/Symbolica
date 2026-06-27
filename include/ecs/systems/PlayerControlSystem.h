#ifndef PLAYER_CONTROL_SYSTEM_H
#define PLAYER_CONTROL_SYSTEM_H

#include "ISystem.h"
#include "Controls.h"
#include "GameState.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "MovementComponent.h"
#include "StepComponent.h"
#include "Vector2D.h"

class PlayerControlSystem: public ISystem {
private:
    const Controls& controls_;
    const GameState& game_state_;

public:
    PlayerControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls, const GameState& game_state):
        ISystem(entity_manager, system_manager), controls_(controls), game_state_(game_state) { }

    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;
};

#endif // PLAYER_CONTROL_SYSTEM_H