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

EntityManager::Iterator::Iterator(const std::map<size_t, std::unique_ptr<Entity>>::iterator& iterator) : iterator_(iterator) {}

EntityManager::Iterator EntityManager::Iterator::operator++() {
      iterator_.operator++();
      return *this;
}

EntityManager::Iterator EntityManager::Iterator::operator++(int step) {
      iterator_.operator++(step);
      return *this;
}

Entity& EntityManager::Iterator::operator*() {
      return *iterator_.operator*().second;
}

Entity* EntityManager::Iterator::operator->() {
      return iterator_.operator*().second.get();
}

bool EntityManager::Iterator::operator==(const Iterator& rhs) {
      return iterator_ == rhs.iterator_;
}

bool EntityManager::Iterator::operator!=(const Iterator& rhs) {
      return iterator_ != rhs.iterator_;
}

EntityManager::Iterator EntityManager::begin() {
    return Iterator{entities_.begin()};
}

EntityManager::Iterator EntityManager::end() {
    return Iterator{entities_.end()};
}