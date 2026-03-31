#ifndef PLAYER_CONTROL_SYSTEM_H
#define PLAYER_CONTROL_SYSTEM_H

#include "ISystem.h"
#include "Controls.h"

class PlayerControlSystem: public ISystem {
private:
    const Controls& controls_;
public:
    PlayerControlSystem(EntityManager*, SystemManager*, const Controls&);

    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;
};

#endif // PLAYER_CONTROL_SYSTEM_H