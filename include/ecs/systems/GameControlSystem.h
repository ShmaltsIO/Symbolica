#ifndef GAME_CONTROL_SYSTEM_H
#define GAME_CONTROL_SYSTEM_H

#include "ISystem.h"
#include "Controls.h"

/**
 * @brief This system reacts on general keys, and depending on them, enables/disables systems.
 * @param controls_ is address of controller of input.
 * @param is_pause_ is bool parametr, needs to check, have games pause or not.
 * @param lock_ is special bool variable, it prevent extra's enables/disables of systems. (For optimization)
 */
class GameControlSystem: public ISystem {
private:
    const Controls& controls_;
    bool is_pause_ = false;
    bool is_inventory_interface = false;
    bool lock_ = true;

    void stop_game();
    void continue_game();

public:
    GameControlSystem(EntityManager*, SystemManager*, const Controls&);

    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;
};

#endif // GAME_CONTROL_SYSTEM_H