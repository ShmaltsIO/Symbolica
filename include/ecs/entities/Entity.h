#ifndef ENTITY_H
#define ENTITY_H
// TODO: Creat .h and .cpp, learn templates!!!!
#include <map>
#include <memory>
#include <typeindex>
#include "IComponent.h"

/**
 * @brief Entity class is a storage for entities components, it haven't logical handles.
 */
class Entity {
  friend class EntityManager;

 private:
  std::map<std::type_index, std::unique_ptr<IComponent>> components;
  size_t id = 0;

 public:
  explicit Entity(size_t id) : id(id) {}

  template<typename Component, typename... Args>
  Entity* Add(Args&&... args) {
    components[typeid(Component)] = std::make_unique<Component>(std::forward<Args>(args)...);
    return this;
  }

  size_t GetId() const {
    return id;
  }

  template<typename Component>
  Component* Get() const {
    auto c = components.at(typeid(Component)).get();
    return dynamic_cast<Component*>(c);
  }

  template<typename Component>
  bool Contains() const {
    return components.count(typeid(Component)) != 0;
  }

  template<typename Component>
  void Delete() {
    components.erase(typeid(Component));
  }
};

#endif  // ENTITY_H
