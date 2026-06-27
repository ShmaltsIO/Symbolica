#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>

#include "BearLibTerminal.h"
#include "Controls.h"
#include "Context.h"
#include "Engine.h"
#include "SceneManager.h"
#include "IniParser.h"
#include "DungeonGenerator.h"
#include "Map.h"
#include "UISettings.h"
#include "GameState.h"
#include "GameStatistics.h"
#include "LevelGenerator.h"
#include "RoomFiller.h"
#include "SpawnConfig.h"
#include "EntityFabric.h"
#include "LoadingScene.h"
#include "SettingsScene.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "GameWinScene.h"
#include "TilemapConfig.h"
#include "SceneType.h"

namespace fs = std::filesystem;
using namespace std;
#include "JsonSerialization.h"

bool loadSpawnConfig(const std::string& path, SpawnConfig& config) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open spawn config: " << path << std::endl;
        return false;
    }
    nlohmann::json j;
    file >> j;
    try {
        from_json(j, config);
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void initScenes(SceneManager& sm, Context& ctx, const Controls& controls) {
    sm.Put(SceneType::TitleScene, new TitleScene(&ctx, controls));
    sm.Put(SceneType::SettingsScene, new SettingsScene(&ctx, controls));
    sm.Put(SceneType::LoadingScene, new LoadingScene(&ctx));
    sm.Put(SceneType::GameScene, new GameScene(&ctx, controls));
    sm.Put(SceneType::GameOverScene, new GameOverScene(&ctx, controls));
    sm.Put(SceneType::GameWinScene, new GameWinScene(&ctx, controls));
}

string getTerminalConfig(const string& path = "config/terminal.ini") {
    IniParser parser;
    std::string configStr;

    if (parser.load(path)) {
        std::string title = parser.getString("window", "title", "Symbolica");
        bool resizeable = parser.getBool("window", "resizeable", true);
        std::string size = parser.getString("window", "size", "150x50");

        configStr = "window.title='" + title + "'; window.resizeable=" + (resizeable ? "true" : "false") + "; window.size=" + size;
    }
    else {
        configStr = "window.title='Symbolica'; window.resizeable=true; window.size=150x50";
    }

    return configStr;
}

void checkTerminalParams() {
    const char* version = terminal_get("version");
    std::cout << "BearLibTerminal version: " << version << std::endl;
    int width = terminal_state(TK_WIDTH);   // ширина в ячейках
    int height = terminal_state(TK_HEIGHT); // высота в ячейках
    std::cout << "Actual terminal size: " << width << "x" << height << std::endl;
}

int main() {
  // --- TERMINAL settings ---
  std::cout << "Current working dir: " << fs::current_path() << std::endl;

  terminal_open();
  terminal_set(getTerminalConfig().c_str());
  
  checkTerminalParams();

  // --- GRAPHICS settings ---
  TilemapConfig tilemap;
  int width = terminal_state(TK_WIDTH);   // ширина в ячейках
  int height = terminal_state(TK_HEIGHT); // высота в ячейках
  
  if (!tilemap.load("config/tilemap.ini")) {
    terminal_print(width-1, height-1, "ERROR: cannot load tilemap.ini");
    std::cout << "ERROR: cannot load tilemap.ini" << std::endl;
  }

  // При старте применяешь настройки графики (например, высокое качество)
  // tilemap.applyToTerminal("graphics_high");
  // tilemap.applyToTerminal("gui"); // если нужно для интерфейса


  // --- CONTEXT INITIALIZATION ---
  terminal_refresh();

  Controls controls;
  auto engine = std::make_unique<Engine>();
  EntityFabric entityFabric(engine->GetEntityManager());
  SpawnConfig spawnConfig;
  if (!loadSpawnConfig("config/GameConfig.json", spawnConfig)) {
      std::cerr << "Failed to load spawn config. Using defaults." << std::endl;
      // Можно установить значения по умолчанию
  }
  // loadSpawnConfig("config/spawn.json", spawnConfig);
  LevelGenerator levelGenerator(&spawnConfig, &entityFabric, 42);

  Context ctx{};
  ctx.engine = std::move(engine);
  ctx.level_generator = &levelGenerator;
  ctx.spawnConfig = &spawnConfig;
  ctx.tilemapConfig = &tilemap;
  ctx.ui_settings = std::make_unique<UISettings>(5, width, height);
  ctx.game_state = std::make_unique<GameState>(1);
  ctx.game_stats = std::make_unique<GameStatistics>();
  ctx.scene = SceneType::TitleScene;

  SceneManager sm(ctx);
  initScenes(sm, ctx, controls);

  // --- GAME START ---
  while (true) {
    controls.OnUpdate();
    if (controls.IsPressed(TK_CLOSE)) {
      break;
    }

    sm.OnRender();

    controls.Reset();
  }
  sm.OnExit();

  terminal_close();
  return 0;
}
