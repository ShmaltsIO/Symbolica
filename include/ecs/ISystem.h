#ifndef ISYSTEM_H
#define ISYSTEM_H

class SystemManager;
class EntityManager;

/**
 * @brief Interface for systems.
 * 
 * System is handle of game events.
 */
class ISystem {
  friend class SystemManager;
  bool is_enabled_ = true;
  EntityManager *const entity_manager_;
  SystemManager *const system_manager_;

 protected:
  virtual void OnPreUpdate();
  virtual void OnUpdate();
  virtual void OnPostUpdate();

 public:
  ISystem(EntityManager *entity_manager, SystemManager *system_manager);
  virtual ~ISystem() = default;

  EntityManager* GetEntityManagerPtr() const;
  EntityManager& GetEntityManager() const;
  SystemManager* GetSystemManagerPtr() const;
  SystemManager& GetSystemManager() const;
};

#endif  // ISYSTEM_H
