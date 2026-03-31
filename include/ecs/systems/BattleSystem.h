#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include "ISystem.h"

class BattleSystem: public ISystem {
public:
    BattleSystem(EntityManager*, SystemManager*);

    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;

};

#endif // BATTLE_SYSTEM_H