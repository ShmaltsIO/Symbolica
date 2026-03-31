#include "LevelSystem.h"
#include "EntityManager.h"
#include "PlayerTagComponent.h"
#include "ExperienceComponent.h"
#include "LevelComponent.h"
#include "HealthComponent.h"


LevelSystem::LevelSystem(EntityManager* entity_manager, SystemManager* system_manager): 
 ISystem(entity_manager, system_manager) {}

void LevelSystem::OnPreUpdate() {}

void LevelSystem::OnUpdate() {
    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<PlayerTagComponent>()) {
            auto ecp = entity.Get<ExperienceComponent>();
            if (ecp->getExperience() >= ecp->getExperienceLimit()) {
                auto lcp = entity.Get<LevelComponent>();
                auto hcp = entity.Get<HealthComponent>();

                ecp->setExperienceLimit(lcp->getLevel()*10 + ecp->getExperienceLimit());
                lcp->setLevel(lcp->getLevel() + 1);
                hcp->setHealthLimit(hcp->getHealthLimit() + 10);
                hcp->setHealth(hcp->getHealthLimit());
                ecp->setExperience(0);
            }
            break;
        }
    }
}

void LevelSystem::OnPostUpdate() {}