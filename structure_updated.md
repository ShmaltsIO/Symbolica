# Структура проекта

```
Symbolica/
├── .vs/
│   ├── Symbolica/
│   │   ├── config/
│   │   │   └── applicationhost.config
│   │   ├── FileContentIndex/
│   │   │   ├── 059f8530-891a-438e-91c6-7d94fcd3e760.vsidx
│   │   │   ├── 4b819550-8938-4f90-8a79-80cee1d2781b.vsidx
│   │   │   ├── 664b3455-4b83-4328-a616-d70043cf7a77.vsidx
│   │   │   ├── d3ab2aec-7a7b-4503-b83f-60405dd4dcc0.vsidx
│   │   │   └── db62d977-2cfc-4e94-ab7f-10738bf82fe1.vsidx
│   │   └── v17/
│   │       ├── ipch/
│   │       │   └── AutoPCH/
│   │       │       ├── 1231c3dc8934dda8/
│   │       │       │   └── ITEMCOMPONENT.ipch
│   │       │       ├── 1b60282b6ec02bb5/
│   │       │       │   └── SAVEPLAYERWRITER.ipch
│   │       │       ├── 1b976940b6b8e7d1/
│   │       │       ├── 2f8cb36549ec309d/
│   │       │       │   └── GAMESTATE.ipch
│   │       │       ├── 3b97c4769fbdaaad/
│   │       │       ├── 446ade3189002177/
│   │       │       │   └── COLLISIONSYSTEM.ipch
│   │       │       ├── 6c8aeb160de25ad2/
│   │       │       ├── 79293f88ac98d167/
│   │       │       │   └── ROOMFILLER.ipch
│   │       │       ├── 8921aa4928dca546/
│   │       │       ├── 8c91aee0766b8147/
│   │       │       │   └── SAVECONVERTER.ipch
│   │       │       ├── 8d6f97e579c24665/
│   │       │       ├── 8ea1f247d3745b7a/
│   │       │       ├── 8f91274de4eb99a8/
│   │       │       │   └── INVENTORYCONTROLSYSTEM.ipch
│   │       │       ├── 8ffe06e9179d69a3/
│   │       │       ├── ac8fd0c2b44e0da5/
│   │       │       ├── b2c8c83a31f7f980/
│   │       │       │   └── LEVELWRITER.ipch
│   │       │       ├── b33235b27d03903e/
│   │       │       │   └── ENTITYFABRIC.ipch
│   │       │       ├── b4588bfe7ecb812/
│   │       │       ├── b48f99bbb4aa715a/
│   │       │       ├── b7d61ec25522d7cc/
│   │       │       │   └── MAIN.ipch
│   │       │       ├── c4e48d26fb5b26ec/
│   │       │       ├── cc379081902d475f/
│   │       │       ├── dbaae5ab096edc89/
│   │       │       │   └── SAVEPLAYERREADER.ipch
│   │       │       ├── e224ea78f16b4c86/
│   │       │       │   └── GAMESCENE.ipch
│   │       │       ├── ecaa053ded13f797/
│   │       │       │   └── INVENTORYCOMPONENT.ipch
│   │       │       ├── eeaa1d054e0c7876/
│   │       │       │   └── SAVECONVERTER.ipch
│   │       │       ├── f42ff28b97b4162a/
│   │       │       │   └── ENTITYMANAGER.ipch
│   │       │       ├── f4f34126c58dd1ad/
│   │       │       │   └── INVENTORYRENDERINGSYSTEM.ipch
│   │       │       └── ffb1ce6d089259a4/
│   │       ├── .wsuo
│   │       ├── Browse.VC.db
│   │       ├── Browse.VC.db-shm
│   │       ├── Browse.VC.db-wal
│   │       ├── Browse.VC.opendb
│   │       ├── DocumentLayout.backup.json
│   │       ├── DocumentLayout.json
│   │       └── Solution.VC.db
│   ├── CMake Overview
│   ├── cmake.db
│   ├── launch.vs.json
│   ├── ProjectSettings.json
│   ├── slnx.sqlite
│   └── VSWorkspaceState.json
├── assets/
│   ├── fonts/
│   │   └── Prototype.ttf
│   ├── gui/
│   │   ├── high/
│   │   └── low/
│   │       ├── inventory.txt
│   │       ├── logo.txt
│   │       ├── lose.txt
│   │       ├── menu.txt
│   │       ├── settings.txt
│   │       └── win.txt
│   └── images/
│       ├── tileBronzeSword.png
│       ├── tileChest.png
│       ├── tileCoin.png
│       ├── tileDiamondArmor.png
│       ├── tileDiamondSword.png
│       ├── tileDoorNext.png
│       ├── tileDoorPrev.png
│       ├── tileEnemy.png
│       ├── tileFood.png
│       ├── tileGround.png
│       ├── tileIronArmor.png
│       ├── tileKey.png
│       ├── tileNPC.png
│       ├── tilePlayer.png
│       └── tileWall.png
├── CMake/
│   ├── CppLint.cmake
│   ├── FindBearLibTerminal.cmake
│   └── README.md
├── config/
│   ├── GameConfig.json
│   ├── ItemsPrefabs.json
│   ├── Symbolica.ini
│   ├── terminal.ini
│   └── tilemap.ini
├── include/
│   ├── config/
│   │   ├── IniParser.h
│   │   ├── SpawnConfig.h
│   │   ├── TilemapConfig.h
│   │   └── UISettings.h
│   ├── core/
│   │   ├── EntityFabric.h
│   │   ├── GameState.h
│   │   ├── GameStatistics.h
│   │   ├── ItemData.h
│   │   ├── LevelState.h
│   │   └── Map.h
│   ├── ecs/
│   │   ├── components/
│   │   │   ├── tags/
│   │   │   │   ├── AbstractTag.h
│   │   │   │   ├── ArmorTagComponent.h
│   │   │   │   ├── DoorTagComponent.h
│   │   │   │   ├── EnemyTagComponent.h
│   │   │   │   ├── FoodTagComponent.h
│   │   │   │   ├── GroundTagComponent.h
│   │   │   │   ├── ItemTagComponent.h
│   │   │   │   ├── MoneyTagComponent.h
│   │   │   │   ├── NPCTagComponent.h
│   │   │   │   ├── ObserverTagComponent.h
│   │   │   │   ├── ObstacleTagComponent.h
│   │   │   │   ├── PlayerTagComponent.h
│   │   │   │   └── WeaponTagComponent.h
│   │   │   ├── AIcontrolsComponent.h
│   │   │   ├── CollectorComponent.h
│   │   │   ├── ColliderComponent.h
│   │   │   ├── ColorComponent.h
│   │   │   ├── DamageComponent.h
│   │   │   ├── EquipmentComponent.h
│   │   │   ├── ExperienceComponent.h
│   │   │   ├── HealthComponent.h
│   │   │   ├── InventoryComponent.h
│   │   │   ├── ItemComponent.h
│   │   │   ├── LevelComponent.h
│   │   │   ├── LocationComponent.h
│   │   │   ├── MovementComponent.h
│   │   │   ├── NameComponent.h
│   │   │   ├── OnPlaceComponent.h
│   │   │   ├── OpenableComponent.h
│   │   │   ├── PathToTargetComponent.h
│   │   │   ├── PlayerControlComponent.h
│   │   │   ├── ProtectionComponent.h
│   │   │   ├── RadiusComponent.h
│   │   │   ├── StateComponent.h
│   │   │   ├── StepComponent.h
│   │   │   ├── StepLimitComponent.h
│   │   │   ├── TextureComponent.h
│   │   │   ├── TransformComponent.h
│   │   │   └── WorthComponent.h
│   │   ├── entities/
│   │   │   └── Entity.h
│   │   ├── systems/
│   │   │   ├── AIcontrolsSystem.h
│   │   │   ├── BattleSystem.h
│   │   │   ├── CollisionSystem.h
│   │   │   ├── GameControlSystem.h
│   │   │   ├── GameOverSystem.h
│   │   │   ├── GameWinSystem.h
│   │   │   ├── InventoryControlSystem.h
│   │   │   ├── InventoryRenderingSystem.h
│   │   │   ├── LevelMapUpdateSystem.h
│   │   │   ├── LevelSystem.h
│   │   │   ├── MovementSystem.h
│   │   │   ├── ObstaclesControlSystem.h
│   │   │   ├── PlayerControlSystem.h
│   │   │   ├── RadiusUpdateSystem.h
│   │   │   ├── RenderingSystem.h
│   │   │   └── RoomsSwitchSystem.h
│   │   ├── Context.h
│   │   ├── Engine.h
│   │   ├── EntityManager.h
│   │   ├── IComponent.h
│   │   ├── IScene.h
│   │   ├── ISystem.h
│   │   ├── SceneManager.h
│   │   └── SystemManager.h
│   ├── enums/
│   │   ├── EntitiesTagsEnum.h
│   │   ├── EntityColor.h
│   │   ├── EntityParams.h
│   │   ├── EntityType.h
│   │   ├── GameObjectsEnum.h
│   │   ├── GameObjectsTexture.h
│   │   ├── GameStateTypesEnum.h
│   │   ├── ItemPrefab.h
│   │   ├── ItemStats.h
│   │   ├── PlayerSaveData.h
│   │   ├── SceneType.h
│   │   └── TileType.h
│   ├── input/
│   │   └── Controls.h
│   ├── io/
│   │   ├── IReader.h
│   │   ├── IWriter.h
│   │   ├── LevelReader.h
│   │   ├── LevelWriter.h
│   │   ├── SavePlayerReader.h
│   │   ├── SavePlayerWriter.h
│   │   └── TxtReader.h
│   ├── scenes/
│   │   ├── GameOverScene.h
│   │   ├── GameScene.h
│   │   ├── GameWinScene.h
│   │   ├── LoadingScene.h
│   │   ├── SettingsScene.h
│   │   └── TitleScene.h
│   └── utils/
│       ├── ecs/
│       │   └── Filter.h
│       ├── game/
│       │   ├── BSPNode.h
│       │   ├── DungeonGenerator.h
│       │   ├── LevelReaderTxt.h
│       │   ├── LevelWriterTxt.h
│       │   ├── RoomFiller.h
│       │   └── SaveConverter.h
│       └── math/
│           ├── aStar.h
│           ├── Grid.h
│           ├── Node.h
│           ├── NodeComparator.h
│           ├── PRNG.h
│           ├── Vector2D.h
│           ├── Vector2DComparator.h
│           └── Vector2DHash.h
├── levels/
│   ├── level1.txt
│   ├── level11.txt
│   ├── level2.txt
│   ├── room0.txt
│   ├── room1.txt
│   ├── room2.txt
│   └── room3.txt
├── lib/
│   ├── BearLibTerminal/
│   │   ├── include/
│   │   │   └── BearLibTerminal.h
│   │   ├── Linux32/
│   │   │   └── libBearLibTerminal.so
│   │   ├── Linux64/
│   │   │   └── libBearLibTerminal.so
│   │   ├── OSX/
│   │   │   └── libBearLibTerminal.dylib
│   │   ├── Windows32/
│   │   │   ├── BearLibTerminal.dll
│   │   │   └── BearLibTerminal.lib
│   │   ├── Windows64/
│   │   │   ├── BearLibTerminal.dll
│   │   │   └── BearLibTerminal.lib
│   │   └── README.md
│   ├── inih/
│   │   ├── ini.c
│   │   └── ini.h
│   ├── nlohmann/
│   │   └── json.hpp
│   └── .gitignore
├── out/
├── saves/
│   └── levelN.txt
├── src/
│   ├── config/
│   │   ├── IniParser.cpp
│   │   ├── SpawnConfig.cpp
│   │   ├── TilemapConfig.cpp
│   │   └── UISettings.cpp
│   ├── core/
│   │   ├── EntityFabric.cpp
│   │   ├── GameState.cpp
│   │   ├── GameStatistics.cpp
│   │   └── Map.cpp
│   ├── ecs/
│   │   ├── components/
│   │   │   ├── tags/
│   │   │   │   ├── AbstractTag.cpp
│   │   │   │   ├── ArmorTagComponent.cpp
│   │   │   │   ├── DoorTagComponent.cpp
│   │   │   │   ├── EnemyTagComponent.cpp
│   │   │   │   ├── FoodTagComponent.cpp
│   │   │   │   ├── ItemTagComponent.cpp
│   │   │   │   ├── MoneyComponent.cpp
│   │   │   │   ├── ObserverTagComponent.cpp
│   │   │   │   ├── ObstacleComponent.cpp
│   │   │   │   ├── PlayerComponent.cpp
│   │   │   │   └── WeaponTagComponent.cpp
│   │   │   ├── ColliderComponent.cpp
│   │   │   ├── ColorComponent.cpp
│   │   │   ├── DamageComponent.cpp
│   │   │   ├── EquipmentComponent.cpp
│   │   │   ├── ExperienceComponent.cpp
│   │   │   ├── HealthComponent.cpp
│   │   │   ├── InventoryComponent.cpp
│   │   │   ├── ItemComponent.cpp
│   │   │   ├── LevelComponent.cpp
│   │   │   ├── LocationComponent.cpp
│   │   │   ├── MovementComponent.cpp
│   │   │   ├── NameComponent.cpp
│   │   │   ├── OnPlaceComponent.cpp
│   │   │   ├── OpenableComponent.cpp
│   │   │   ├── PathToTargetComponent.cpp
│   │   │   ├── PlayerControlComponent.cpp
│   │   │   ├── ProtectionComponent.cpp
│   │   │   ├── RadiusComponent.cpp
│   │   │   ├── StateComponent.cpp
│   │   │   ├── StepComponent.cpp
│   │   │   ├── StepLimitComponent.cpp
│   │   │   ├── TextureComponent.cpp
│   │   │   ├── TransformComponent.cpp
│   │   │   └── WorthComponent.cpp
│   │   ├── systems/
│   │   │   ├── AIcontrolsSystem.cpp
│   │   │   ├── BattleSystem.cpp
│   │   │   ├── CollisionSystem.cpp
│   │   │   ├── GameControlSystem.cpp
│   │   │   ├── GameOverSystem.cpp
│   │   │   ├── GameWinSystem.cpp
│   │   │   ├── InventoryControlSystem.cpp
│   │   │   ├── InventoryRenderingSystem.cpp
│   │   │   ├── LevelMapUpdateSystem.cpp
│   │   │   ├── LevelSystem.cpp
│   │   │   ├── MovementSystem.cpp
│   │   │   ├── ObstaclesControlSystem.cpp
│   │   │   ├── PlayerControlSystem.cpp
│   │   │   ├── RadiusUpdateSystem.cpp
│   │   │   ├── RenderingSystem.cpp
│   │   │   └── RoomsSwitchSystem.cpp
│   │   ├── Engine.cpp
│   │   ├── EntityManager.cpp
│   │   ├── IComponent.cpp
│   │   ├── IScene.cpp
│   │   ├── ISystem.cpp
│   │   └── SceneManager.cpp
│   ├── input/
│   │   └── Controls.cpp
│   ├── io/
│   │   ├── IReader.cpp
│   │   ├── IWriter.cpp
│   │   ├── LevelReader.cpp
│   │   ├── LevelWriter.cpp
│   │   ├── SavePlayerReader.cpp
│   │   ├── SavePlayerWriter.cpp
│   │   └── TxtReader.cpp
│   ├── scenes/
│   │   ├── GameOverScene.cpp
│   │   ├── GameScene.cpp
│   │   ├── GameWinScene.cpp
│   │   ├── LoadingScene.cpp
│   │   ├── SettingsScene.cpp
│   │   └── TitleScene.cpp
│   ├── utils/
│   │   ├── ecs/
│   │   │   └── Filter.cpp
│   │   ├── game/
│   │   │   ├── DungeonGenerator.cpp
│   │   │   ├── LevelGenerator.cpp
│   │   │   ├── LevelReaderTxt.cpp
│   │   │   ├── LevelWriterTxt.cpp
│   │   │   ├── RoomFiller.cpp
│   │   │   └── SaveConverter.cpp
│   │   └── math/
│   │       ├── Vector2D.cpp
│   │       └── Vector2DComparator.cpp
│   └── main.cpp
├── .gitattributes
├── .gitignore
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
├── structure.md
└── tree_to_md.py
```
