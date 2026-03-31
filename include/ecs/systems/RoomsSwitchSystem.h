#ifndef ROOMS_SWITCH_SYSTEM_H
#define ROOMS_SWITCH_SYSTEM_H

#include "ISystem.h"
#include "Context.h"

class RoomsSwitchSystem: public ISystem {
private:
    Context* context_;

protected:
    void OnUpdate() override;

public:
    RoomsSwitchSystem(EntityManager* const, SystemManager* const, Context*);
};

#endif // ROOMS_SWITCH_SYSTEM_H