#ifndef INVENTORY_RENDERING_SYSTEM_H
#define INVENTORY_RENDERING_SYSTEM_H

#include "ISystem.h"
#include "Controls.h"

class InventoryRenderingSystem: public ISystem {
protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

public:
  InventoryRenderingSystem(EntityManager*, SystemManager*);
};

#endif // INVENTORY_RENDERING_SYSTEM_H