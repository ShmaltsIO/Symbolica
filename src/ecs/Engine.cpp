#include "Engine.h"

Engine::Engine()
      : entity_manager_(std::make_unique<EntityManager>()),
        system_manager_(std::make_unique<SystemManager>(entity_manager_.get())), 
        level_reader_(std::make_unique<LevelReader>()),
        level_writer_(std::make_unique<LevelWriter>()),
        path_to_file_("") {}

EntityManager* Engine::GetEntityManager() const {
    return entity_manager_.get();
}

SystemManager* Engine::GetSystemManager() const {
    return system_manager_.get();
}

LevelReader* Engine::getLevelReader() const {
    return level_reader_.get();
}

LevelWriter* Engine::getLevelWriter() const {
    return level_writer_.get();
}

std::string Engine::getPathToFile() const {
    return path_to_file_;
}

void Engine::setPathToFile(std::string path) {
    path_to_file_ = path;
}

void Engine::OnUpdate() const {
    system_manager_->OnUpdate();
}
