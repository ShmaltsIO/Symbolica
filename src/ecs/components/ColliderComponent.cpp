#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(): size_(zeroVector), offset_(zeroVector) {}

ColliderComponent::ColliderComponent(const Vector2D& size, const Vector2D& offset = Vector2D(0,0)):
 size_(size), offset_(offset) {}

const std::set<Entity*>& ColliderComponent::GetCollisions() const {
    return collisions_;
}

bool ColliderComponent::AnyCollisions() const {
    return !collisions_.empty();
}

void ColliderComponent::Collide(Entity* entity) {
    collisions_.insert(entity);
}

void ColliderComponent::Clear() {
    collisions_.clear();
}
