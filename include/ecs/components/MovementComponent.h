#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "IComponent.h"
#include "Vector2D.h"

class MovementComponent : public IComponent {
 public:
  Vector2D speed_;
  Vector2D direction_;
  explicit MovementComponent(Vector2D, Vector2D);
};
#endif  // MOVEMENT_COMPONENT_H
