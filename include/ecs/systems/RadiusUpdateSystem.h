#ifndef RADIUS_UPDATE_SYSTEM_H
#define RADIUS_UPDATE_SYSTEM_H

#include <vector>

#include "ISystem.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "GameState.h"
#include "RadiusComponent.h"
#include "TransformComponent.h"
#include "GroundTagComponent.h"

class RadiusUpdateSystem: public ISystem {
private:
	const GameState& game_state_;

protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RadiusUpdateSystem(EntityManager* entity_manager, SystemManager* system_manager, const GameState& game_state):
	  ISystem(entity_manager, system_manager), game_state_(game_state) { }
};

#endif // RADIUS_UPDATE_SYSTEM_H