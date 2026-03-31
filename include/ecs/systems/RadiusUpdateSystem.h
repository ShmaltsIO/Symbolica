#ifndef RADIUS_UPDATE_SYSTEM_H
#define RADIUS_UPDATE_SYSTEM_H

#include "ISystem.h"

class RadiusUpdateSystem: public ISystem {
protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RadiusUpdateSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif // RADIUS_UPDATE_SYSTEM_H