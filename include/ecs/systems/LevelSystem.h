#ifndef LEVEL_SYSTEM_H
#define LEVEL_SYSTEM_H

#include "ISystem.h"

/**
 * @brief System of levels of entities.
 * @attention Each level calculates in OnUpdate if current exp >= max exp by formula: 10*n + p
 * 
 * Where n is current level, p is previous exp max.
 */
class LevelSystem: public ISystem {
protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

public:
    LevelSystem(EntityManager*, SystemManager*);

};

#endif // LEVEL_SYSTEM_H