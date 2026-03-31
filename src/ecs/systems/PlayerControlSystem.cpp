#include "PlayerControlSystem.h"
#include "EntityManager.h"
#include "MovementComponent.h"
#include "Vector2D.h"
#include "PlayerControlComponent.h"
#include "PlayerTagComponent.h"
#include "StepComponent.h"

PlayerControlSystem::PlayerControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controller):
    ISystem(entity_manager, system_manager), controls_(controller) {}

void PlayerControlSystem::OnPreUpdate() {}

void PlayerControlSystem::OnUpdate() {
    if (controls_.IsPressed(TK_UP) || controls_.IsPressed(TK_W)) {
        for (auto& e : GetEntityManager()) {
            if (e.Contains<PlayerTagComponent>()) {
                auto mc = e.Get<MovementComponent>();
                mc->direction_ = upVector;

                auto sc = e.Get<StepComponent>();
                sc->setSteps(sc->getSteps() + 1);
            }
        }
    }

    if (controls_.IsPressed(TK_RIGHT) || controls_.IsPressed(TK_D)) {
        for (auto& e : GetEntityManager()) {
            if (e.Contains<PlayerTagComponent>()) {
                auto mc = e.Get<MovementComponent>();
                mc->direction_ = rightVector;

                auto sc = e.Get<StepComponent>();
                sc->setSteps(sc->getSteps() + 1);
            }
        }
    }

    if (controls_.IsPressed(TK_DOWN) || controls_.IsPressed(TK_S)) {
        for (auto& e : GetEntityManager()) {
            if (e.Contains<PlayerTagComponent>()) {
                auto mc = e.Get<MovementComponent>();
                mc->direction_ = downVector;

                auto sc = e.Get<StepComponent>();
                sc->setSteps(sc->getSteps() + 1);
            }
        }
    }
    if (controls_.IsPressed(TK_LEFT) || controls_.IsPressed(TK_A)) {
        for (auto& e : GetEntityManager()) {
            if (e.Contains<PlayerTagComponent>()) {
                auto mc = e.Get<MovementComponent>();
                mc->direction_ = leftVector;

                auto sc = e.Get<StepComponent>();
                sc->setSteps(sc->getSteps() + 1);
            }
        }
    }
}

void PlayerControlSystem::OnPostUpdate() {}
