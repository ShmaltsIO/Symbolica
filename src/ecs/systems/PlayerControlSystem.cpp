#include "PlayerControlSystem.h"
void PlayerControlSystem::OnPreUpdate() {}

void PlayerControlSystem::OnUpdate() {
    auto player = game_state_.getPlayer();
    auto* mc = player->Get<MovementComponent>();
    auto* sc = player->Get<StepComponent>();

    if (controls_.IsPressed(TK_UP) || controls_.IsPressed(TK_W)) {
        mc->direction_ = upVector;
        sc->setSteps(sc->getSteps() + 1);
    }

    if (controls_.IsPressed(TK_RIGHT) || controls_.IsPressed(TK_D)) {
        mc->direction_ = rightVector;
        sc->setSteps(sc->getSteps() + 1);
    }

    if (controls_.IsPressed(TK_DOWN) || controls_.IsPressed(TK_S)) {
        mc->direction_ = downVector;
        sc->setSteps(sc->getSteps() + 1);
    }

    if (controls_.IsPressed(TK_LEFT) || controls_.IsPressed(TK_A)) {
        mc->direction_ = leftVector;
        sc->setSteps(sc->getSteps() + 1);
    }
}

void PlayerControlSystem::OnPostUpdate() {}
