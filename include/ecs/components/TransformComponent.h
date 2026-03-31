#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "IComponent.h"
#include "Vector2D.h"

class TransformComponent : public IComponent {
 public:
  Vector2D position_;

  explicit TransformComponent(const Vector2D&);
};
#endif  // TRANSFORM_COMPONENT_H
