#include <iostream>
#include "BearLibTerminal.h"
#include "Controls.h"
#include "Context.h"
#include "Engine.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "GameWinScene.h"
#include "Vector2D.h"
#include "Grid.h"
#include "LevelGenerator.h"
#include "LoadingScene.h"
#include "SettingsScene.h"
#include <fstream>
#include <filesystem>
#include "IniParser.h"
#include "DungeonGenerator.h"
#include "Map.h"
namespace fs = std::filesystem;

#include "RoomGenerator.h"
#include <TilemapConfig.h>
using namespace std;

int main() {
  // --- НАСТРОЙКА ТЕРМИНАЛА ---
  std::cout << "Current working dir: " << fs::current_path() << std::endl;
  IniParser parser;
  std::string configStr;

  TilemapConfig tilemap;
    
  if (parser.load("config/terminal.ini")) {
    // Читаем секцию [window]
    std::string title = parser.getString("window", "title", "Symbolica");
    bool resizeable = parser.getBool("window", "resizeable", true);
    std::string size = parser.getString("window", "size", "150x50");
        
    configStr = "window.title='" + title + "'; window.resizeable=" + (resizeable ? "true" : "false") + "; window.size=" + size;
      
    // Можно добавить и другие секции, например, [font], но для BearLibTerminal все параметры плоские.
    std::cout << "Terminal config: " << configStr << std::endl;
  } else {
    // fallback
    configStr = "window.title='Symbolica'; window.resizeable=true; window.size=150x50";
  }
  
  terminal_open();
  terminal_set(configStr.c_str());
  
  const char* version = terminal_get("version");
  std::cout << "BearLibTerminal version: " << version << std::endl;      
  int width = terminal_state(TK_WIDTH);   // ширина в ячейках
  int height = terminal_state(TK_HEIGHT); // высота в ячейках
  std::cout << "Actual terminal size: " << width << "x" << height << std::endl;

  
  // if (!tilemap.load("config/tilemap.ini")) {
  //     // Обработка ошибки, возможно, используются встроенные значения по умолчанию
  //     terminal_print(1, 1, "ERROR: cannot load tilemap.ini");
  // }

  // При старте применяешь настройки графики (например, высокое качество)
  // tilemap.applyToTerminal("graphics_high");
  // tilemap.applyToTerminal("gui"); // если нужно для интерфейса

  std::cout << "Dungeon Generation..." << std::endl;
  DungeonGenerator dg = DungeonGenerator();
  Map mmm = dg.generate(20, 20);
  LevelWriter lw = LevelWriter();
  lw.setPathToFile("TestDungeon.json");
  lw.write(mmm);
  std::cout << "End of test generation!"<< std::endl;
  for (size_t y = 0; y < mmm.getHeight(); ++y) {
    for (size_t x = 0; x < mmm.getWidth(); ++x) {
        char ch = static_cast<char>(mmm.getTile(x, y));
        std::cout << ch;
    }
    std::cout << '\n';
  }
  
  LevelReader lr;
  std::string path_to_file_ = ("levels/level1.txt");
  int left_bound = path_to_file_.find("room");
  int right_bound = path_to_file_.find(".txt");
  std::string level = path_to_file_.substr(left_bound+4, right_bound-left_bound-4);
  
  std::cout << "LEVEL READER:" << level << std::endl;

  cout << "START MAIN" << endl;
  
  terminal_refresh();

  Controls controls;

  Context ctx{};
  SceneManager sm(ctx);

  sm.Put("title", new TitleScene(&ctx, controls));
  sm.Put("settings", new SettingsScene(&ctx, controls));
  sm.Put("loading", new LoadingScene(&ctx));
  sm.Put("game", new GameScene(&ctx, controls));
  sm.Put("game_over", new GameOverScene(&ctx, controls));
  sm.Put("game_win", new GameWinScene(&ctx, controls));

  // Start scene
  ctx.scene_ = "title";
  ctx.tilemapConfig = &tilemap;

  // Simple game loop
  while (true) {
    controls.OnUpdate();
    if (controls.IsPressed(TK_CLOSE) || ctx.scene_ == "exit") {
      break;
    }

    sm.OnRender();

    controls.Reset();
  }
  sm.OnExit();

  terminal_close();
  return 0;
}
