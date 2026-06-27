#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include <string>

#include "ISystem.h"
#include "SystemManager.h"
#include "EntityManager.h"
#include "GameState.h"

class Entity;
/**
 * @brief Rendering system displays entities on window.
 * 
 * Some entities rendering on different layers:
 * 
 * 0) Is obstacles layer
 * 
 * 1) Is items layer
 * 
 * 2) Is player and enemies layer
 * 
 * 3) Is stats layer
 */
class RenderingSystem : public ISystem {
private:
    GameState* game_state_;

    // Вспомогательные методы
    std::string getEntityString(const Entity& entity) const;
    void renderLayer0();
    void renderLayer1();
    void renderLayer2();
    void renderStats();

    std::string getModifiedString(const Entity&);
    std::string addColor(const Entity&);

protected:
    void OnPreUpdate() override;
    void OnUpdate() override;
    void OnPostUpdate() override;

public:
    RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, GameState* game_state):
        ISystem(entity_manager, system_manager), game_state_(game_state) { }
};

#endif  // RENDERING_SYSTEM_H
