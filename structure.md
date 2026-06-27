symbolica/
|
|- assets/      # Наборы картинок png
|  |- fonts     # Шрифты
|  |- items     # Текстуры игровых предметов
|  |- objects   # Текстуры объектов
|  |- gui       # Текстуры графического интерфейса
|
|- config/              # Конфигурация игры и проекта
|  |- terminal.ini     # Конфигурация проекта по умолчанию
|  |- tilemap.ini       # Конфигурация для графики
|  |- game.ini          # Конфигурация для текущих натсроек пользователя
|
|- include/                 # Заголовочные файлы
|  |
|  |- config/
|  |  |- IniParser.h   # Чтение INI файлов
|  |  |- TilemapConfig.h    # Настройка текстур тайлов
|  | 
|  |- core/             # Пока пусто
|  |  |-
|  |  
|  |- input/
|  |  |- Controls.h     # Обработчики нажатий на клавиши
|  |  
|  |- io/               # Интерфейсы для чтения файлов
|  |  |- IReader.h          # Чтение уровней
|  |  |- IWriter.h          # Запись уровней (сохранение)
|  |
|  |- ecs/              # entity-component-system
|  |  |- components/    # Компоненты
|  |  |  |- tags/       # Система тегов для сущностей для быстрого определения её типа
|  |  |  |  |- AbstractTag.h
|  |  |  |  |- ArmorTagComponent.h
|  |  |  |  |- DoorTagComponent.h
|  |  |  |  |- EnemyTagComponent.h
|  |  |  |  |- FoodTagComponent.h
|  |  |  |  |- GroundTagComponent.h
|  |  |  |  |- ItemTagComponent.h
|  |  |  |  |- MoneyTagComponent.h
|  |  |  |  |- NPCTagComponent.h
|  |  |  |  |- ObserverTagComponent.h
|  |  |  |  |- ObstacleTagComponent.h
|  |  |  |  |- PlayerTagComponent.h
|  |  |  |  |- WeaponTagComponent.h
|  |  |  |
|  |  |  |- AIcontrolsComponent.h
|  |  |  |- CollectorComponent.h
|  |  |  |- ColliderComponent.h
|  |  |  |- ColorComponent.h
|  |  |  |- DamageComponent.h
|  |  |  |- EquipmentComponent.h
|  |  |  |- ExperienceComponent.h
|  |  |  |- HealthComponent.h
|  |  |  |- InventoryComponent.h
|  |  |  |- ItemComponent.h
|  |  |  |- LevelComponent.h
|  |  |  |- LocationComponent.h
|  |  |  |- MovementComponent.h
|  |  |  |- OnPlaceComponent.h
|  |  |  |- OpenableComponent.h
|  |  |  |- PathToTargetComponent.h
|  |  |  |- PlayerControlComponent.h
|  |  |  |- ProtectionComponent.h
|  |  |  |- RadiusComponent.h
|  |  |  |- StateComponent.h
|  |  |  |- StepComponent.h
|  |  |  |- StepLimitComponent.h
|  |  |  |- TextureComponent.h
|  |  |  |- TransformComponent.h
|  |  |  |- WorthComponent.h
|  |  |
|  |  |- entities/  # Сущности, содержит один файл
|  |  |  |- Entity.h
|  |  |
|  |  |- systems/   # Системы
|  |  |  |- AIcontrolsSystem.h
|  |  |  |- BattleSystem.h
|  |  |  |- CollisionSystem.h
|  |  |  |- GameControlSystem.h
|  |  |  |- GameOverSystem.h
|  |  |  |- GameWinSystem.h
|  |  |  |- InventoryControlSystem.h
|  |  |  |- InventoryRenderingSystem.h
|  |  |  |- LevelMapUpdateSystem.h
|  |  |  |- LevelSystem.h
|  |  |  |- MovementSystem.h
|  |  |  |- ObstaclesControlSystem.h
|  |  |  |- PlayerControlSystem.h
|  |  |  |- RadiusUpdateSystem.h
|  |  |  |- RenderingSystem.h
|  |  |  |- RoomsSwitchSystem.h
|  |  |
|  |  |- Context.h
|  |  |- Engine.h
|  |  |- EntityManager.h
|  |  |- IComponent.h
|  |  |- IScene.h
|  |  |- ISystem.h
|  |  |- SceneManager.h
|  |  |- SystemManager.h
|  |
|  |- enums/    # Перечисления
|  |  |- EntitiesTagsEnum.h
|  |  |- GameObjectsEnum.h
|  |  |- GameStateTypesEnum.h
|  |  |- SceneTypesEnum.h
|  |
|  |- scenes/   # Сцены
|  |  |- GameOverScene.h
|  |  |- GameScene.h
|  |  |- GameWinScene.h
|  |  |- LoadingScene.h
|  |  |- SettingsScene.h
|  |  |- TitleScene.h
|  |
|  |- utils/    # Утилиты
|  |  |- ecs/
|  |  |  |- Filter.h
|  |  |
|  |  |- game/  # Игровые утилиты
|  |  |  |- LevelReader.h
|  |  |  |- LevelWriter.h
|  |  |
|  |  |- math/  # Математические формулы и алгоритмы
|  |  |  |- aStar.h
|  |  |  |- Grid.h
|  |  |  |- Node.h
|  |  |  |- NodeComparator.h
|  |  |  |- PRNG.h
|  |  |  |- Vector2D.h
|  |  |  |- Vector2DComparator.h
|  |  |  |- Vector2DHash.h
|  |  |
|  |  |- service/   # Пусто
|  |  |  |-
|
|- levels/  # Уровни
|  |- level1.txt
|  |- room0.txt
|
|- lib/                 # Библиотеки проекта
|  |- BearLibTerminal/  # Основная библиотека для работы с терминалом
|  |- nlohmann/         # Библиотека для работы с json файлами
|  |- inih/             # Библиотека для парсинга INI файлов
|
|- saves/   # Сохранения игровые
|  |- levelN.txt
|
|- src/ # Исходники, структура полностью повторяет структуру include/, там же лежит main.cpp
|
|- .gitattributes
|- .gitignore
|- CMakeLists.txt
|- CMakePresets.json
|- README.md