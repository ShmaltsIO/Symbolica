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
    size_t last_entity_id = 1;

public:
    Entity* CreateEntity();
    EntityManager* DeleteEntity(size_t);
    EntityManager* DeleteAll();
    Entity* Get(size_t) const;

    // ---- Итераторы ----
    class Iterator {
        std::map<size_t, std::unique_ptr<Entity>>::iterator it_;
    public:
        explicit Iterator(const std::map<size_t, std::unique_ptr<Entity>>::iterator& it) : it_(it) {}
        Iterator& operator++() { ++it_; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++it_; return tmp; }
        Entity& operator*() { return *it_->second; }
        Entity* operator->() { return it_->second.get(); }
        bool operator==(const Iterator& other) const { return it_ == other.it_; }
        bool operator!=(const Iterator& other) const { return it_ != other.it_; }
    };

    class ConstIterator {
        std::map<size_t, std::unique_ptr<Entity>>::const_iterator it_;
    public:
        explicit ConstIterator(const std::map<size_t, std::unique_ptr<Entity>>::const_iterator& it) : it_(it) {}
        ConstIterator& operator++() { ++it_; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++it_; return tmp; }
        const Entity& operator*() const { return *it_->second; }
        const Entity* operator->() const { return it_->second.get(); }
        bool operator==(const ConstIterator& other) const { return it_ == other.it_; }
        bool operator!=(const ConstIterator& other) const { return it_ != other.it_; }
    };

    Iterator begin() { return Iterator(entities_.begin()); }
    Iterator end() { return Iterator(entities_.end()); }

    ConstIterator begin() const { return ConstIterator(entities_.cbegin()); }
    ConstIterator end()   const { return ConstIterator(entities_.cend()); }
};

#endif