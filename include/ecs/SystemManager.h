#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <map>
#include <memory>
#include <typeindex>
#include "EntityManager.h"
#include "ISystem.h"

/**
 * @brief System manager is a storage of system, but manager have functions of enabling/disabling the system.
 */
class SystemManager {
 private:
  std::map<std::type_index, std::unique_ptr<ISystem>> systems;
  EntityManager *const entity_manager;

 public:
  explicit SystemManager(EntityManager *entity_manager) : entity_manager(entity_manager) {}

  template<typename System, typename... Args>
  SystemManager *AddSystem(Args &&... args) {
    systems.emplace(typeid(System), std::make_unique<System>(entity_manager, this, std::forward<Args>(args)...));
    return this;
  }

  template<typename System>
  SystemManager *Delete() {
    systems.erase(typeid(System));
    return this;
  }

  SystemManager *DeleteAll() {
    systems.clear();
    return this;
  }

  template<typename System>
  void Disable() const {
    systems.at(typeid(System))->is_enabled_ = false;
  }

  void DisableAll() const {
      for (auto& pair : systems) {
          pair.second.get()->is_enabled_ = false;
      }
  }

  template<typename System>
  void Enable() const {
    systems.at(typeid(System))->is_enabled_ = true;
  }

  void OnUpdate() {
    for (auto &p : systems) {
      if (p.second->is_enabled_) {
        p.second->OnPreUpdate();
      }
    }
    for (auto &p : systems) {
      if (p.second->is_enabled_) {
        p.second->OnUpdate();
      }
    }
    for (auto &p : systems) {
      if (p.second->is_enabled_) {
        p.second->OnPostUpdate();
      }
    }
  }
};
#endif  // SYSTEM_MANAGER_H
