#include "Filter.h"
#include "PlayerTagComponent.h"
// template<typename... IComponent>
// bool Filter::apply(const Entity& entity, const IComponent&... components) {
//     bool flag = true;
    
//     for (auto&& component : components) {
//         if (entity.Contains<component>()) {
//             flag = false;
//             break;
//         }
//     }
//     return flag;
// }

bool Filter::isPlayer(const Entity* entity) {
    return entity->Contains<PlayerTagComponent>();
}
