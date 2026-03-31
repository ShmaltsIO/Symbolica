#ifndef PLAYER_CONTROL_COMPONENT_H
#define PLAYER_CONTROL_COMPONENT_H

#include "IComponent.h"

class PlayerControlComponent : public IComponent {
 public:
  int up_button_;
  int right_button_;
  int down_button_;
  int left_button_;

  explicit PlayerControlComponent(int, int, int, int);
};

#endif  // PLAYER_CONTROL_COMPONENT_H
