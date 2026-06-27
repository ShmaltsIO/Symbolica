#ifndef AI_CONTROLS_SYSTEM_H
#define AI_CONTROLS_SYSTEM_H

#include "ISystem.h"
#include "Context.h"
#include "EntityManager.h"
#include "SystemManager.h"

class AIcontrolsSystem : public ISystem {
private:
    Context* context_;

public:
    AIcontrolsSystem(EntityManager* entityManager, SystemManager* systemManager, Context* context);
    
    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;
};

#endif