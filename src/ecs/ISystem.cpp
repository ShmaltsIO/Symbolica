#include "ISystem.h"

ISystem::ISystem(EntityManager *entity_manager, SystemManager *system_manager)
      : entity_manager_(entity_manager), system_manager_(system_manager) {}

EntityManager* ISystem::GetEntityManagerPtr() const {
    return entity_manager_;
}
EntityManager& ISystem::GetEntityManager() const {
    return *GetEntityManagerPtr();
}
SystemManager* ISystem::GetSystemManagerPtr() const {
    return system_manager_;
}
SystemManager& ISystem::GetSystemManager() const {
    return *GetSystemManagerPtr();
}

void ISystem::OnPreUpdate() {}
void ISystem::OnUpdate() {}
void ISystem::OnPostUpdate() {}