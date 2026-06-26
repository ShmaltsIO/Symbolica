#include "EntityManager.h"

Entity* EntityManager::CreateEntity() {
    auto id = ++last_entity_id;
    entities_.emplace(id, std::make_unique<Entity>(id));
    return entities_.at(id).get();
}

EntityManager* EntityManager::DeleteEntity(size_t id) {
    entities_.erase(id);
    return this;
}

EntityManager* EntityManager::DeleteAll() {
    entities_.clear();
    last_entity_id = 1;
    return this;
}

Entity* EntityManager::Get(size_t id) const {
    if (entities_.count(id) == 0) {
      //std::cout << "[WARNING] there is no entity with id=" << id << std::endl;
      return entities_.at(last_entity_id).get();
    }
    return entities_.at(id).get();
}
