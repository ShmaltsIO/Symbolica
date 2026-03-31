#include "InventoryRenderingSystem.h"
#include "BearLibTerminal.h"
#include "EntityManager.h"
#include "PlayerTagComponent.h"
#include "InventoryComponent.h"
#include "WorthComponent.h"
#include "FoodTagComponent.h"
#include "ArmorTagComponent.h"
#include "WeaponTagComponent.h"
#include "DamageComponent.h"
#include "ProtectionComponent.h"
#include "EquipmentComponent.h"

InventoryRenderingSystem::InventoryRenderingSystem(EntityManager* entity_manager, SystemManager* system_manager):
 ISystem(entity_manager, system_manager) {}

void InventoryRenderingSystem::OnPreUpdate() {
    for (int i = 0; i < 10; i++) {
        terminal_layer(i);
        terminal_clear_area(20, 2, 40, 40);
    }
}

void InventoryRenderingSystem::OnUpdate() {
    for (auto& player : GetEntityManager()) {
        if (player.Contains<PlayerTagComponent>()) {
            // TODO: optimize to different screens
            auto ic_p = player.Get<InventoryComponent>();
            unsigned int current_size = ic_p->getCurrentSize();
            unsigned int max_size = ic_p->getMaxSize();
            unsigned int current_item_number = ic_p->getSelectedItemNumber();
            
            terminal_layer(250);
            terminal_printf(20, 2, "╔══════════════════════════════════╗");
            terminal_printf(20, 3, "║        === Inventory ===         ║");
            terminal_printf(20, 4, "T══════════════════════════════════T");
            terminal_printf(20, 5, "║                                  ║");
            terminal_printf(20, 6, "║                      ╔═════════╗ ║");
            terminal_printf(20, 7, "║                      ║         ║ ║");
            terminal_printf(20, 8, "║                      ║         ║ ║");
            terminal_printf(20, 9, "║                      ║         ║ ║");
            terminal_printf(20, 10, "║                      ║         ║ ║");
            terminal_printf(20, 11, "║                      ╚═════════╝ ║");
            terminal_printf(20, 12, "║                                  ║");
            terminal_printf(20, 13, "║                                  ║");
            terminal_printf(20, 14, "║                                  ║");
            terminal_printf(20, 15, "║                                  ║");
            terminal_printf(20, 16, "║                                  ║");
            terminal_printf(20, 17, "║                                  ║");
            terminal_printf(20, 18, "║                                  ║");
            terminal_printf(20, 19, "║                                  ║");
            terminal_printf(20, 20, "║                                  ║");
            terminal_printf(20, 21, "║                                  ║");
            terminal_printf(20, 22, "╚══════════════════════════════════╝");
            terminal_printf(22, 21, "Capacity: %d/%d", current_size, max_size);
            // TODO: create max size
            int i = 22;
            int j = 6;
            std::cout << "CUR SIZE: " << current_size << "CUR IT NUM: " << current_item_number << std::endl;
            if (current_size > 0 && current_item_number != 0) {
                auto item = ic_p->getInventory()[current_item_number-1];
                auto item_entity = GetEntityManager().Get(item.getItemId());
                auto ec_p = player.Get<EquipmentComponent>();

                terminal_printf(i, j, "%d) %s", current_item_number, item.getName().c_str());    
                        
                // TODO: Include this sets in settings
                terminal_set("0x1000: /home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/assets/tileFood.png, resize=56x56, resize-filter=nearest;");
                terminal_set("0x1001: /home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/assets/tileBronzeSword.png, resize=56x56, resize-filter=nearest;");
                terminal_set("0x1002: /home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/assets/tileDiamondSword.png, resize=56x56, resize-filter=nearest;");
                terminal_set("0x1003: /home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/assets/tileIronArmor.png, resize=56x56, resize-filter=nearest;");
                terminal_set("0x1004: /home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/assets/tileDiamondArmor.png, resize=56x56, resize-filter=nearest;");
                
                if (item_entity->Contains<FoodTagComponent>()) {
                    terminal_put(i + 23, j + 1, 0x1000);
                    terminal_printf(i, j + 10, "Description: %s ", item.getDescription().c_str());
                    terminal_printf(i, j + 11, "Heal: %d ", GetEntityManager().Get(item.getItemId())->Get<WorthComponent>()->getWorth());
                }

                if (item_entity->Contains<WeaponTagComponent>()) {
                    terminal_put(i + 23, j + 1, 0x1001);
                    terminal_printf(i, j + 10, "Description: %s ", item.getDescription().c_str());
                    terminal_printf(i, j + 11, "Damage: %d ", GetEntityManager().Get(item.getItemId())->Get<DamageComponent>()->getDamage());
                    
                    if (ec_p->getRightHand() == item.getItemId()) {
                        terminal_printf(i*2, j + 12, "[color=dark green]Equipped[/color]");
                    }
                }

                if (item_entity->Contains<ArmorTagComponent>()) {
                    terminal_put(i + 23, j + 1, 0x1003);
                    terminal_printf(i, j + 10, "Description: %s ", item.getDescription().c_str());
                    terminal_printf(i, j + 11, "Protection: %d ", GetEntityManager().Get(item.getItemId())->Get<ProtectionComponent>()->getProtection());
                    if (ec_p->getChest() == item.getItemId()) {
                        terminal_printf(i*2, j + 12, "[color=dark green]Equipped[/color]");
                    }
                }

            } else {
                terminal_print(i, j + 10, "For moving in inventory");
                terminal_print(i, j + 11, " press DOWN or UP keys.");
                terminal_print(i, j + 12, "For use a item press R.");
                terminal_print(i, j + 13, "For drop a item press Q.");
            }
        }
        break;
    }
}

void InventoryRenderingSystem::OnPostUpdate() {
    terminal_refresh();
}
