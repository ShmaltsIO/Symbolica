#ifndef GAME_WIN_SYSTEM_H
#define GAME_WIN_SYSTEM_H

#include "ISystem.h"
#include "Context.h"

class GameWinSystem: public ISystem {
private:
  Context* ctx_;

protected:
  void OnUpdate() override;

public:
  GameWinSystem(EntityManager* const, SystemManager* const, Context*);
};

#endif // GAME_WIN_SYSTEM_H