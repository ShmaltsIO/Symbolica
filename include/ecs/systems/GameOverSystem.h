#ifndef GAME_OVER_SYSTEM_H
#define GAME_OVER_SYSTEM_H

#include "ISystem.h"
#include "Context.h"

class GameOverSystem : public ISystem {
 private:
  Context* ctx_;

 protected:
  void OnUpdate() override;

 public:
  GameOverSystem(EntityManager* const, SystemManager* const, Context*);
};

#endif  // GAME_OVER_SYSTEM_H
