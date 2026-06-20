#include "RoomsSwitchSystem.h"
#include "SystemManager.h"
#include "PlayerTagComponent.h"
#include "DoorTagComponent.h"
#include "LevelComponent.h"
#include "LocationComponent.h"
#include "TransformComponent.h"
#include "SceneType.h"

RoomsSwitchSystem::RoomsSwitchSystem(EntityManager* const entity_manager, SystemManager* const system_manager, Context* context):
 ISystem(entity_manager, system_manager), context_(context) {}

void RoomsSwitchSystem::OnUpdate() {
    for (auto& player : GetEntityManager()) {
        if (player.Contains<PlayerTagComponent>()) {
            for (auto& door : GetEntityManager()) {
                if (door.Contains<DoorTagComponent>()) {
                    auto transform_player = player.Get<TransformComponent>();
                    auto current_room = player.Get<LocationComponent>();

                    auto transform_door = door.Get<TransformComponent>();
                    auto room_number = door.Get<LevelComponent>();
                    // or distance <= 1
                    if (transform_player->position_ == transform_door->position_) {
                        //std::cout << "DOOR LEVEL and ECHO: " << current_room->current_location_ << " " << room_number->getLevel();
                        current_room->current_location_ = room_number->getLevel();

                        context_->game_state->setRoomNumber(room_number->getLevel());
                        context_->scene = SceneType::LoadingScene;
                    }
                }
            }
        }
        break;
    }

    GetSystemManager().Disable<RoomsSwitchSystem>();
}
