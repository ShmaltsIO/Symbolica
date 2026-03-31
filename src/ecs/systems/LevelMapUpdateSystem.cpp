#include "LevelMapUpdateSystem.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include <iostream>
LevelMapUpdateSystem::LevelMapUpdateSystem(EntityManager* entity_manager, SystemManager* system_manager, Grid& level_map):
 ISystem(entity_manager, system_manager), level_map_(level_map) {}

void LevelMapUpdateSystem::OnPreUpdate() {}

void LevelMapUpdateSystem::OnUpdate() {
    level_map_.map_.clear();
    
    for (auto& entity : GetEntityManager()) {
        if (entity.Contains<TransformComponent>() && entity.Contains<TextureComponent>()) { 
            auto transform = entity.Get<TransformComponent>();
            auto texture = entity.Get<TextureComponent>();
            // But this have problem, allow on position (2, 3) set ground and player... keys is not difference
            // TODO: Maye separate map to obstacle-item-entites layers?
            level_map_.map_.emplace(Vector2D(transform->position_), texture->symbol_);
        }
    }
    // Output the map
    // for (auto& pair : level_map_.map_) {
    //     std::cout << "FIRST: " << pair.first << "SECOND: " << (char) pair.second << std::endl;
    // }
}

void LevelMapUpdateSystem::OnPostUpdate() {}
