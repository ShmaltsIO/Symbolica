#ifndef INVENTORY_CONTROL_SYSTEM_H
#define INVENTORY_CONTROL_SYSTEM_H

#include "ISystem.h"
#include "Controls.h"
#include "Entity.h"

class InventoryControlSystem: public ISystem {
private:
    const Controls& controls_;
    bool useItem(Entity&, Entity&);

protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

public:
    InventoryControlSystem(EntityManager*, SystemManager*, const Controls&);
};

#endif // INVENTORY_CONTROL_SYSTEM_H