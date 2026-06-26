#ifndef SAVE_CONVERTER_H
#define SAVE_CONVERTER_H

#include "PlayerSaveData.h"
#include "EntityManager.h"
#include "Context.h"

#include "PlayerTagComponent.h"
#include "HealthComponent.h"
#include "DamageComponent.h"
#include "ProtectionComponent.h"
#include "LevelComponent.h"
#include "ExperienceComponent.h"
#include "WorthComponent.h"
#include "TransformComponent.h"
#include "InventoryComponent.h"
#include "GameState.h"

class SaveConverter {
public:
    static PlayerSaveData toSaveData(const EntityManager& em, const Context& ctx);
    static void fromSaveData(const PlayerSaveData& data, EntityManager& em, Context& ctx);
};

#endif // SAVE_CONVERTER_H