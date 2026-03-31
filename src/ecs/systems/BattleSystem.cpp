#include "BattleSystem.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "PlayerTagComponent.h"
#include "EnemyTagComponent.h"
#include "HealthComponent.h"
#include "DamageComponent.h"
#include "ExperienceComponent.h"
#include "RadiusComponent.h"
#include "ProtectionComponent.h"
#include "BearLibTerminal.h"

BattleSystem::BattleSystem(EntityManager* entity_manager, SystemManager* system_manager):
 ISystem(entity_manager, system_manager) {}

void BattleSystem::OnPreUpdate() {}

void BattleSystem::OnUpdate() {
    //Entity* player = nullptr;
    // TODO: can do it a more effective?
    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<PlayerTagComponent>()) {
            auto player_radius = entity.Get<RadiusComponent>();
            auto player_health = entity.Get<HealthComponent>();
            auto player_damage = entity.Get<DamageComponent>();
            auto player_protection = entity.Get<ProtectionComponent>();
            for (auto& pair : player_radius->getNeighborhood()) {
                auto entity = GetEntityManager().Get(pair);
                if (entity->Contains<EnemyTagComponent>()) {
                    auto enemy_health = entity->Get<HealthComponent>();
                    auto enemy_damage = entity->Get<DamageComponent>();
                    //terminal_layer(5);
                    terminal_delay(1000);
                    
                    
                    while(enemy_health->getHealth() > 0 && player_health->getHealth() > 0) {
                        if ((int) player_protection->getProtection() >= enemy_damage->getTotalDamage()) {
                            enemy_health->setHealth(0);
                            break;
                        }
                        enemy_health->setHealth(enemy_health->getHealth() - player_damage->getTotalDamage());
                        player_health->setHealth(player_health->getHealth() - enemy_damage->getTotalDamage());
                        //terminal_clear_area(5,5,15,15);
                        terminal_print(40, 40, "Battle");

                        terminal_print(10,10,"Player");
                        terminal_printf(10, 12, "Health: %d", player_health->getHealth());
                        terminal_printf(10, 13, "Damage: %d", player_damage->getTotalDamage());
                        terminal_printf(10, 14, "Protection: %d", player_protection->getProtection());
                        //terminal_printf(10, 12, "Level: %d", player_health->getHealth());
                        terminal_print(40,10,"Enemy");
                        terminal_printf(40, 12, "Health: %d", enemy_health->getHealth());
                        terminal_printf(40, 13, "Damage: %d", enemy_damage->getTotalDamage());
                        terminal_printf(40, 14, "Protection: %d", 0);
                        //terminal_printf(5, 5, "[bbox2*5][bkcolor=gray] shakalaka");
                        //terminal_crop(2,2,8,8);
                        terminal_refresh();
                        terminal_delay(2000);
                    }
                    if (enemy_health->getHealth() <= 0) {
                        GetEntityManager().DeleteEntity(entity->GetId());
                    }
                }
            }
        }
        break;
    }
    //GetSystemManager().Disable<BattleSystem>();
}

void BattleSystem::OnPostUpdate() {}
