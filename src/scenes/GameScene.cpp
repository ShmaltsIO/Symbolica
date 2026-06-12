#include "GameScene.h"
#include "ColliderComponent.h"
#include "PlayerControlComponent.h"
#include "CollisionSystem.h"
#include "GameOverSystem.h"
#include "Vector2D.h"
#include "MovementComponent.h"
#include "ObstacleTagComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "MovementSystem.h"
#include "ObstaclesControlSystem.h"
#include "RenderingSystem.h"
#include "PlayerControlSystem.h"
#include "PlayerTagComponent.h"
#include "MoneyTagComponent.h"
#include "WorthComponent.h"
#include "FoodTagComponent.h"
#include "HealthComponent.h"
#include "ObstacleTagComponent.h"
#include "StepComponent.h"
#include "LevelComponent.h"
#include "ExperienceComponent.h"
#include "LevelSystem.h"
#include "LevelReader.h"
#include "GroundTagComponent.h"
#include "GameControlSystem.h"
#include "ObserverTagComponent.h"
#include "StepLimitComponent.h"
#include "GameObjectsEnum.h"
#include "GameWinSystem.h"
#include "DoorTagComponent.h"
#include "OpenableComponent.h"
#include "EnemyTagComponent.h"
#include "DamageComponent.h"
#include "AIcontrolsSystem.h"
#include "PathToTargetComponent.h"
#include "ColorComponent.h"
#include "LevelMapUpdateSystem.h"
#include "LevelGenerator.h"
#include "LocationComponent.h"
#include "RadiusComponent.h"
#include "RadiusUpdateSystem.h"
#include "BattleSystem.h"
#include "InventoryComponent.h"
#include "InventoryRenderingSystem.h"
#include "InventoryControlSystem.h"
#include "OnPlaceComponent.h"
#include "ItemTagComponent.h"
#include "ArmorTagComponent.h"
#include "WeaponTagComponent.h"
#include "ProtectionComponent.h"
#include "StateComponent.h"
#include "NPCTagComponent.h"
#include "EquipmentComponent.h"
#include "RoomsSwitchSystem.h"
#include <fstream>
//#include "Filter.h"

#include "RoomGenerator.h"
#include "aStar.h"

GameScene::GameScene(Context* const ctx, const Controls& controls):
 IScene(ctx), controls(controls) {}

void GameScene::OnCreate() {
  // Initialization variables
  // grid is level_map, start and end nodes for paths generation
  std::cout << "Rabota 1" << std::endl;
  auto lr_e = engine.getLevelReader();
  std::cout << "Rabota 2" << std::endl;
  std::string level_path = "";
  Vector2D start(3, 3);
  Vector2D end(level_map.width_ - 3, level_map.height_ - 3);
  Node one(start);
  Node two(end);
  std::cout << "Rabota 3" << std::endl;

  // If we came from Title Scene, clicked on START GAME, init. empty hero, else load from copy
  if (context_->is_start) {
    {
      auto player = engine.GetEntityManager()->CreateEntity();
      player->Add<TransformComponent>(Vector2D(0, 0));
      player->Add<TextureComponent>('@');
      player->Add<MovementComponent>(Vector2D(0,0), Vector2D(0,0));
      player->Add<ColliderComponent>();
      player->Add<PlayerTagComponent>();
      player->Add<WorthComponent>(0);
      player->Add<HealthComponent>(2000, 2000);
      player->Add<DamageComponent>(2, 0);
      player->Add<StepComponent>(0);
      player->Add<LevelComponent>();
      player->Add<ExperienceComponent>();
      player->Add<ColorComponent>();
      player->Add<RadiusComponent>();
      player->Add<LocationComponent>();
      player->Add<InventoryComponent>();
      player->Add<ProtectionComponent>();
      player->Add<EquipmentComponent>();
    }
  } else {
    {
      std::cout << "Rabota 4" << std::endl;
      auto player = engine.GetEntityManager()->CreateEntity();
      player->Add<TransformComponent>(player_copy.Get<TransformComponent>()->position_);
      player->Add<TextureComponent>('@');
      player->Add<MovementComponent>(Vector2D(0,0), Vector2D(0,0));
      player->Add<ColliderComponent>();
      player->Add<PlayerTagComponent>();
      player->Add<WorthComponent>(player_copy.Get<WorthComponent>()->getWorth());
      player->Add<HealthComponent>(player_copy.Get<HealthComponent>()->getHealth(), player_copy.Get<HealthComponent>()->getHealthLimit());
      player->Add<DamageComponent>(player_copy.Get<DamageComponent>()->getDamage(), player_copy.Get<DamageComponent>()->getBonusDamage());
      player->Add<StepComponent>(player_copy.Get<StepComponent>()->getSteps());
      player->Add<LevelComponent>(player_copy.Get<LevelComponent>()->getLevel());
      player->Add<ExperienceComponent>(player_copy.Get<ExperienceComponent>()->getExperience(), player_copy.Get<ExperienceComponent>()->getExperienceLimit());
      player->Add<ColorComponent>();
      player->Add<RadiusComponent>();
      player->Add<LocationComponent>(player_copy.Get<LocationComponent>()->current_location_);
      std::cout << "Rabota 5" << std::endl;
      // player->Add<InventoryComponent>(player_copy.Get<InventoryComponent>()->getInventory(),
      //  player_copy.Get<InventoryComponent>()->getCurrentSize(),
      //   player_copy.Get<InventoryComponent>()->getMaxSize());
      player->Add<InventoryComponent>();
      std::cout << "Rabota 55" << std::endl;
      player->Add<ProtectionComponent>(player_copy.Get<ProtectionComponent>()->getProtection());
      std::cout << "Rabota 555" << std::endl;
      player->Add<EquipmentComponent>();
      
      std::cout << "Rabota 6" << std::endl;
    }
    one = Node(player_copy.Get<TransformComponent>()->position_);
  }  

  // Load first level if new game, else continue (also includes switches between rooms)
  std::cout << "Rabota 67" << std::endl;
  if (context_->is_start) {
    context_->is_start = false;
    level_map.level_number_ = 1;
    level_path = "levels/level1.txt";
    std::vector<Vector2D> path;
    // while (path.empty()) {
    //   std::cout << "ITERATION" << std::endl;
    //   path = generateLevel(one, two, level_map);
    // }
    // level_map = generateLevelMOD(20, 20, level_map.level_number_);
    lr_e->setPathToFile(level_path);
    level_map = lr_e->read();
  } else {
    level_path = "levels/room" + std::to_string(level_map.level_number_) + ".txt";
    lr_e->setPathToFile(level_path);
    if (context_->is_load && lr_e->checkFileExist()) {
      level_map = lr_e->read();
      context_->is_load = false;
    } else {
      std::cout << "ELSE" << std::endl;
      std::vector<Vector2D> path;
      while (path.empty()) {
        std::cout << "ITERATION" << std::endl;
        path = generateLevel(one, two, level_map);
      }
      //level_map = generateLevelMOD(20, 20, level_map.level_number_);
      level_map = lr_e->read();
      context_->is_load = false;
    }
  }

  // FOR TESTS 0 level
  // level_path = "/home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/levels/room0.txt";
  // lr_e->setPathToFile(level_path);
  // level_map = lr_e->read();
  // FOR TESTS

  // Observer is special entity, which check conditions of game continues (or ame over/win)
  // His ID = 3
  {
    auto observer = engine.GetEntityManager()->CreateEntity();
    observer->Add<ObserverTagComponent>();
    observer->Add<TransformComponent>(Vector2D(0,0));
    observer->Add<StepLimitComponent>(101);
  }
  // TODO: maybe pattern 'Factory' can make this more easy?
  // Adding entities
  Vector2D current_pos(0, 0);
  unsigned int doors_level = context_->room_;
  std::cout << "DOORS LEVEL: " << doors_level << std::endl;
  // level_map = generateLevelMOD(20, 20, 1);
  
  for (auto& pair : level_map.map_) {
    std::cout << "FIRST: " << pair.first << std::endl;
    current_pos = pair.first;
    // current_pos += onesVector;
    switch (pair.second)
    {
    case (GameObjectsEnum::WALL):
      {
        auto wall = engine.GetEntityManager()->CreateEntity();
        wall->Add<ObstacleTagComponent>();
        wall->Add<TransformComponent>(current_pos);
        wall->Add<TextureComponent>('#');
        wall->Add<ColorComponent>("grey");
      }
      break;
    case (GameObjectsEnum::PLAYER):
      engine.GetEntityManager()->Get(2)->Get<TransformComponent>()->position_ = current_pos;
      {
        auto ground = engine.GetEntityManager()->CreateEntity();
        ground->Add<GroundTagComponent>();
        ground->Add<TransformComponent>(current_pos);
        ground->Add<TextureComponent>('.');
        ground->Add<ColorComponent>("dark green");
      }
      break;
    case (GameObjectsEnum::FOOD):
      {
        auto food = engine.GetEntityManager()->CreateEntity();
        food->Add<FoodTagComponent>();
        food->Add<ItemTagComponent>();
        food->Add<WorthComponent>(30);
        food->Add<TransformComponent>(current_pos);
        food->Add<TextureComponent>('%');
        food->Add<ColorComponent>("amber");
        food->Add<OnPlaceComponent>();
      }
      {
        auto ground = engine.GetEntityManager()->CreateEntity();
        ground->Add<GroundTagComponent>();
        ground->Add<TransformComponent>(current_pos);
        ground->Add<TextureComponent>('.');
        ground->Add<ColorComponent>("dark green");
      }
      break;
    case (GameObjectsEnum::COIN):
      {
        auto coin = engine.GetEntityManager()->CreateEntity();
        coin->Add<MoneyTagComponent>();
        coin->Add<WorthComponent>(1);
        coin->Add<TransformComponent>(current_pos);
        coin->Add<TextureComponent>('$');
        coin->Add<ColorComponent>("dark yellow");
      }
      {
        auto ground = engine.GetEntityManager()->CreateEntity();
        ground->Add<GroundTagComponent>();
        ground->Add<TransformComponent>(current_pos);
        ground->Add<TextureComponent>('.');
        ground->Add<ColorComponent>("dark green");
      }
      break;

    case (GameObjectsEnum::DOOR_TO):
      {
        auto door = engine.GetEntityManager()->CreateEntity();
        door->Add<DoorTagComponent>();
        door->Add<OpenableComponent>();
        door->Add<TransformComponent>(current_pos);
        door->Add<TextureComponent>('>');
        door->Add<ColorComponent>("light #905025");
        door->Add<LevelComponent>(doors_level+1);
        door->Add<WorthComponent>(doors_level*2);
      }
      std::cout << "DOORS LEVEL: " << doors_level << std::endl;
      break;
    
    case (GameObjectsEnum::DOOR_FROM):
      {
        auto door = engine.GetEntityManager()->CreateEntity();
        door->Add<DoorTagComponent>();
        door->Add<OpenableComponent>();
        door->Add<TransformComponent>(current_pos);
        door->Add<TextureComponent>('<');
        door->Add<ColorComponent>("light #905025");
        door->Add<LevelComponent>(doors_level-1);
        door->Add<WorthComponent>(doors_level*2);
      }
      std::cout << "DOORS LEVEL: " << doors_level << std::endl;
      break;
    
    case (GameObjectsEnum::ENEMY):
      {
        auto enemy = engine.GetEntityManager()->CreateEntity();
        enemy->Add<EnemyTagComponent>();
        // enemy->Add<MovementComponent>();
        enemy->Add<ColliderComponent>();
        enemy->Add<HealthComponent>(5, 5);
        enemy->Add<TransformComponent>(current_pos);
        enemy->Add<TextureComponent>('E');
        enemy->Add<DamageComponent>();
        enemy->Add<ColorComponent>("red");
        enemy->Add<PathToTargetComponent>();
      }
      {
        auto ground = engine.GetEntityManager()->CreateEntity();
        ground->Add<GroundTagComponent>();
        ground->Add<TransformComponent>(current_pos);
        ground->Add<TextureComponent>('.');
        ground->Add<ColorComponent>("dark green");
      }
      break;
    
    case (GameObjectsEnum::WEAPON):
      {
        auto weapon = engine.GetEntityManager()->CreateEntity();
        weapon->Add<ItemTagComponent>();
        weapon->Add<WeaponTagComponent>();
        weapon->Add<DamageComponent>(3, 0);
        weapon->Add<TransformComponent>(current_pos);
        weapon->Add<TextureComponent>('|');
        weapon->Add<ColorComponent>("blue");
        //weapon->Add<LevelComponent>(1);
        weapon->Add<OnPlaceComponent>();
      }
      {
        auto ground = engine.GetEntityManager()->CreateEntity();
        ground->Add<GroundTagComponent>();
        ground->Add<TransformComponent>(current_pos);
        ground->Add<TextureComponent>('.');
        ground->Add<ColorComponent>("dark green");
      }
      break;
    
    // case (GameObjectsEnum::NPC):
    //   {
    //     auto npc = engine.GetEntityManager()->CreateEntity();
    //     npc->Add<NPCTagComponent>();
    //     npc->Add<TransformComponent>(current_pos);
    //     npc->Add<TextureComponent>('N');
    //     npc->Add<ColorComponent>("purple");
    //     npc->Add<StateComponent>(GameStateTypesEnum::DICE);
    //   }
    //   {
    //     auto ground = engine.GetEntityManager()->CreateEntity();
    //     ground->Add<GroundTagComponent>();
    //     ground->Add<TransformComponent>(current_pos);
    //     ground->Add<TextureComponent>('.');
    //     ground->Add<ColorComponent>("dark green");
    //   }
    //   break;

    case (GameObjectsEnum::ARMOR):
      {
        auto armor = engine.GetEntityManager()->CreateEntity();
        armor->Add<ItemTagComponent>();
        armor->Add<ArmorTagComponent>();
        armor->Add<TransformComponent>(current_pos);
        armor->Add<TextureComponent>('}');
        armor->Add<ColorComponent>("cyan");
        armor->Add<LevelComponent>(1);
        armor->Add<ProtectionComponent>(2);
        armor->Add<OnPlaceComponent>();
      }
      {
        auto ground = engine.GetEntityManager()->CreateEntity();
        ground->Add<GroundTagComponent>();
        ground->Add<TransformComponent>(current_pos);
        ground->Add<TextureComponent>('.');
        ground->Add<ColorComponent>("dark green");
      }
      break;

    // case(GameObjectsEnum::NPC):
    //   {
    //     auto enemy = engine.GetEntityManager()->CreateEntity();
    //     enemy->Add<EnemyTagComponent>();
    //   }
    //   {
    //     auto ground = engine.GetEntityManager()->CreateEntity();
    //     ground->Add<GroundTagComponent>();
    //     ground->Add<TransformComponent>(current_pos);
    //     ground->Add<TextureComponent>('.');
    //     ground->Add<ColorComponent>("dark green");
    //   }
    //   break;

    case ('t'):
      break;
    
    default:
      {
        auto ground = engine.GetEntityManager()->CreateEntity();
        ground->Add<GroundTagComponent>();
        ground->Add<TransformComponent>(current_pos);
        ground->Add<TextureComponent>('.');
        ground->Add<ColorComponent>("dark green");
      }
      break;
    }
  }

  // Adding systems
  auto sys = engine.GetSystemManager();
  
  sys->AddSystem<RenderingSystem>();
  sys->AddSystem<PlayerControlSystem>(controls);
  sys->AddSystem<MovementSystem>();
  sys->AddSystem<CollisionSystem>();
  sys->AddSystem<LevelSystem>();
  sys->AddSystem<GameOverSystem>(context_);
  sys->AddSystem<GameControlSystem>(controls);
  sys->AddSystem<GameWinSystem>(context_);
  std::cout << "BEFORE " << std::endl;
  sys->AddSystem<AIcontrolsSystem>(level_map);
  sys->AddSystem<LevelMapUpdateSystem>(level_map);
  std::cout << "After " << std::endl;
  sys->AddSystem<RadiusUpdateSystem>();
  sys->AddSystem<RoomsSwitchSystem>(context_);
  sys->AddSystem<BattleSystem>();
  sys->AddSystem<InventoryRenderingSystem>();
  sys->AddSystem<InventoryControlSystem>(controls);

  //sys->Disable<RoomsSwitchSystem>();
  sys->Disable<GameWinSystem>();
  sys->Disable<InventoryRenderingSystem>();
  // auto lr_e = engine.getLevelReader();
  // lr_e->setPathToFile("/home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/levels/level0.txt");
  // auto stt = lr_e->getPathToFile();
  // auto newstr = lr_e->read();
  // std::cout << "Wow: " << newstr << std::endl;
    std::cout << "END" << std::endl;
}
void GameScene::OnRender() {
  engine.OnUpdate();
}

void GameScene::OnExit() {
  // TODO: maybe create spcial system for stats? Because that's cringe :/
  context_->steps_completed = engine.GetEntityManager()->Get(2)->Get<StepComponent>()->getSteps();
  context_->money_collected_ = engine.GetEntityManager()->Get(2)->Get<WorthComponent>()->getWorth();
  // TODO: why this don't working? Because Engine contain unique_ptr...
  // for (auto& entity : engine.GetEntityManager()) {
  //   if (entity.second.Contains<PlayerTagComponent>()) {
  //     context_->steps_completed = entity.Get<StepComponent>().getSteps();
  //   }
  // }
  //player_ = engine.GetEntityManager()->Get(2);
  player_ = engine.GetEntityManager()->Get(2);

  player_copy.Add<TransformComponent>(player_->Get<TransformComponent>()->position_);
  player_copy.Add<TextureComponent>('@');
  player_copy.Add<MovementComponent>(Vector2D(0,0), Vector2D(0,0));
  player_copy.Add<ColliderComponent>();
  player_copy.Add<PlayerTagComponent>();
  player_copy.Add<WorthComponent>(player_->Get<WorthComponent>()->getWorth());
  player_copy.Add<HealthComponent>(player_->Get<HealthComponent>()->getHealth(), player_->Get<HealthComponent>()->getHealthLimit());
  player_copy.Add<DamageComponent>(player_->Get<DamageComponent>()->getDamage(), player_->Get<DamageComponent>()->getBonusDamage());
  player_copy.Add<StepComponent>(player_->Get<StepComponent>()->getSteps());
  player_copy.Add<LevelComponent>(player_->Get<LevelComponent>()->getLevel());
  player_copy.Add<ExperienceComponent>(player_->Get<ExperienceComponent>()->getExperience(), player_->Get<ExperienceComponent>()->getExperienceLimit());
  player_copy.Add<ColorComponent>();
  player_copy.Add<RadiusComponent>();
  player_copy.Add<LocationComponent>(player_->Get<LocationComponent>()->current_location_);

  player_copy.Add<InventoryComponent>();  
  // player_copy.Add<InventoryComponent>(player_->Get<InventoryComponent>()->getInventory(),
  //  player_->Get<InventoryComponent>()->getCurrentSize(),
  //   player_->Get<InventoryComponent>()->getMaxSize());
  player_copy.Add<ProtectionComponent>(player_->Get<ProtectionComponent>()->getProtection());
  player_copy.Add<EquipmentComponent>();

  level_map.level_number_ = player_->Get<LocationComponent>()->current_location_;
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
  std::cout << "DELETES" << std::endl;
  // if (player_->Contains<LocationComponent>()) {
  //   std::cout << "Exist" << std::endl;
  // } else {
  //   std::cout << "NOPe" << std::endl;
  // }
  
  //std::cout << "Player room" << player_->Get<LocationComponent>()->current_location_ << std::endl;
}

void GameScene::setPreviousLevel(std::string previous_level) {
  previous_level_ = previous_level;
}

std::string GameScene::getPreviousLevel() {
  return previous_level_;
}

std::string GameScene::getPreviousLevel() const {
  return previous_level_;
}

// Grid GameScene::getLevelMap() {
//   return level_map;
// }

// Grid GameScene::getLevelMap() const {
//   return level_map;
// }

// void GameScene::updateLevelMap(Grid grid) {
//   level_map = grid;
// }
