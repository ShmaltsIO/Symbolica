#include "InventoryControlSystem.h"
#include "EntityManager.h"
#include "PlayerTagComponent.h"
#include "InventoryRenderingSystem.h"
#include "InventoryComponent.h"
#include "TransformComponent.h"
#include "OnPlaceComponent.h"
#include "FoodTagComponent.h"
#include "HealthComponent.h"
#include "WorthComponent.h"
#include "WeaponTagComponent.h"
#include "DamageComponent.h"
#include "EquipmentComponent.h"
#include "ArmorTagComponent.h"
#include "ProtectionComponent.h"

InventoryControlSystem::InventoryControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls):
 ISystem(entity_manager, system_manager), controls_(controls) {}

bool InventoryControlSystem::useItem(Entity& player, Entity& item) {
    bool is_consumables = false;
    
    if (item.Contains<FoodTagComponent>()) {
        auto hc_p = player.Get<HealthComponent>();
        auto wc_i = item.Get<WorthComponent>();

        hc_p->setHealth(hc_p->getHealth() + wc_i->getWorth());
        is_consumables = true;
    }

    if (item.Contains<WeaponTagComponent>()) {
        auto ec_p = player.Get<EquipmentComponent>();
        auto dc_p = player.Get<DamageComponent>();

        auto dc_i = item.Get<DamageComponent>();

        if (ec_p->getRightHand() == item.GetId()) {
            dc_p->setBonusDamage(0);
            ec_p->setRightHand(0);
        } else {
            dc_p->setBonusDamage(dc_i->getDamage());
            ec_p->setRightHand(item.GetId());
        }
    }

    if (item.Contains<ArmorTagComponent>()) {
        auto ec_p = player.Get<EquipmentComponent>();
        auto pc_p = player.Get<ProtectionComponent>();

        auto pc_i = item.Get<ProtectionComponent>();

        if (ec_p->getChest() == item.GetId()) {
            pc_p->setProtection(0);
            ec_p->setChest(0);
        } else {
            pc_p->setProtection(pc_i->getProtection());
            ec_p->setChest(item.GetId());
        }
    }

    // For future
    // if (item.Contains<>()) {
        
    // }
    return is_consumables;
}

void InventoryControlSystem::OnPreUpdate() {}

void InventoryControlSystem::OnUpdate() {
    for (auto& player : GetEntityManager()) {
        if (player.Contains<PlayerTagComponent>()) {
            auto ic_p = player.Get<InventoryComponent>();
        
            if (controls_.IsPressed(TK_DOWN) || controls_.IsPressed(TK_S)) {
                ic_p->decSelectedItemNumber();
            }

            if (controls_.IsPressed(TK_UP) || controls_.IsPressed(TK_W)) {
                ic_p->incSelectedItemNumber();
            }

            //if (controls_.IsPressed(TK_R)) {
            //    // use
            //    size_t id = ic_p->getItem().getItemId();
            //    if (!(id == 0)) {
            //        auto item = GetEntityManager().Get(id);

            //        if (useItem(player, *item)) {
            //            ic_p->deleteItem(ic_p->getSelectedItemNumber());
            //            GetEntityManager().DeleteEntity(id);
            //        }
            //    }

            //    // Create special utilits function in this system, that's will be
            //    // analyses the tag of item and use it in right way
            //}

            //if (controls_.IsPressed(TK_Q)) {
            //    auto tc_p = player.Get<TransformComponent>();
            //    size_t id = ic_p->getItem().getItemId();
            //    if (!(id == 0)) {
            //        auto item = GetEntityManager().Get(id);
            //        auto ec_p = player.Get<EquipmentComponent>();

            //        if (item->Contains<WeaponTagComponent>()) {
            //            auto dc_p = player.Get<DamageComponent>();
            //            dc_p->setBonusDamage(0);
            //            ec_p->setRightHand(0);
            //        }

            //        if (item->Contains<ArmorTagComponent>()) {
            //            auto pc_p = player.Get<ProtectionComponent>();
            //            pc_p->setProtection(0);
            //            ec_p->setChest(0);
            //        }

            //        item->Add<TransformComponent>(Vector2D(tc_p->position_));
            //        item->Get<OnPlaceComponent>()->enable();

            //        ic_p->deleteItem(ic_p->getSelectedItemNumber());
            //    }
            //    // create bool field it_was_dropped in food entity in itemTag or same
            //    // and if we click on Q, this field change and player, while stay on place, save this 
            //    // bool state it_was_dropped = true, when he walking, is_was_dropped = false
            //}

            if (ic_p->getSelectedItemNumber() > ic_p->getCurrentSize()) {
                ic_p->setSelectedItemNumber(0);
            }
        }
        break;
    }
}

void InventoryControlSystem::OnPostUpdate() {}
