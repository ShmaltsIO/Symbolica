#ifndef LEVEL_MAP_UPDATE_SYSTEM_H
#define LEVEL_MAP_UPDATE_SYSTEM_H

#include "ISystem.h"
#include "Grid.h"

class LevelMapUpdateSystem: public ISystem {
private:
    Grid level_map_{0, 0};
public:
    LevelMapUpdateSystem(EntityManager*, SystemManager*, Grid&);

    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;
};

#endif // LEVEL_MAP_UPDATE_SYSTEM_H