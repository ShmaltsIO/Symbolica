#ifndef ENGINE_H
#define ENGINE_H

#include "EntityManager.h"
#include "SystemManager.h"
#include "LevelReader.h"
#include "LevelWriter.h"
#include "Grid.h"
#include <memory>
#include <string>

/**
 * @brief Engine is a storage for entity and system managers,
 * and also engine define path to level.
 */
class Engine {
 private:
  std::unique_ptr<EntityManager> entity_manager_;
  std::unique_ptr<SystemManager> system_manager_;
  std::unique_ptr<LevelReader> level_reader_;
  std::unique_ptr<LevelWriter> level_writer_;
  std::string path_to_file_;

 public:
  Engine();

  EntityManager* GetEntityManager() const;
  SystemManager* GetSystemManager() const;
  LevelReader* getLevelReader() const;
  LevelWriter* getLevelWriter() const;
  std::string getPathToFile() const;
  void setPathToFile(std::string);
  
  void OnUpdate() const;

};
#endif  // ENGINE_H
