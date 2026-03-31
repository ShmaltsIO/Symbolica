#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "IComponent.h"
#include "Vector2D.h"
#include <set>

class Entity;

class ColliderComponent : public IComponent {
private:
  std::set<Entity*> collisions_{};

public:
  Vector2D size_;
  Vector2D offset_;
  explicit ColliderComponent();

  explicit ColliderComponent(const Vector2D&, const Vector2D&);

  const std::set<Entity*>& GetCollisions() const;

  bool AnyCollisions() const;

  void Collide(Entity* entity);

  void Clear();
};

#endif  // COLLIDER_COMPONENT_H
