#ifndef AI_CONTROLS_SYSTEM_H
#define AI_CONTROLS_SYSTEM_H

#include "ISystem.h"
#include "Grid.h"


class AIcontrolsSystem: public ISystem {
private:
    Grid level_map_{0, 0};
public:
    AIcontrolsSystem(EntityManager*, SystemManager*, Grid);

    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;
};

#endif // AI_CONTROLS_SYSTEM_H