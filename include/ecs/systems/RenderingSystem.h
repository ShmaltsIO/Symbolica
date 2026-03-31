#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include "ISystem.h"
#include <string>

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
  std::string getModifiedString(const Entity&);
  std::string addColor(const Entity&);

protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

public:
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // RENDERING_SYSTEM_H
