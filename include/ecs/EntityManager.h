#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <iostream>
#include <map>
#include <memory>
#include "Entity.h"

/**
 * @brief Class for entities.
 * What's entity manager can do:
 * - Create and delete entities
 * - Can be a storage for entities
 * - Can get entities by them special ID
 */
class EntityManager {
 private:
 // TODO: make prioritet list
  std::map<size_t, std::unique_ptr<Entity>> entities_;
  // TODO: maybe add tag system?
  size_t last_entity_id = 1;  // start from 1 to use 0 as a special entity ID

 public:
  Entity* CreateEntity();
  EntityManager* DeleteEntity(size_t);
  EntityManager* DeleteAll();
  Entity* Get(size_t) const;

  class Iterator {
    std::map<size_t, std::unique_ptr<Entity>>::iterator iterator_;

   public:
    explicit Iterator(const std::map<size_t, std::unique_ptr<Entity>>::iterator&);

    Iterator operator++();
    Iterator operator++(int);

    Entity& operator*();

    Entity* operator->();

    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);
  };

  Iterator begin() ;

  Iterator end();
};

#endif  // ENTITY_MANAGER_H
