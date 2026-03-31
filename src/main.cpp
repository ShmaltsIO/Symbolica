#include <iostream>
// #include </home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/lib/BearLibTerminal/include/BearLibTerminal.h>
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

#include "RoomGenerator.h"
using namespace std;

int main() {
  
  // Grid gridden(getRandomNumber(10, 80, 10), getRandomNumber(10, 80, 10));
  // Vector2D vecA(0,1);
  // Vector2D vecD(7,8);
  // Node node1(vecA);
  // Node node2(vecD);

  // for (auto& pair : gridden.map_) {
  //   cout << "GRIDDEN:" << pair.first << " : " << pair.second << endl;
  // }

  // generateLevel(node1, node2, gridden);
  

  char w = ' ';
  ofstream out;
  out.open("ghost/day.txt");
  out << "W" << endl;
  out.close();
  ifstream in;
  in.open("ghost/day.txt");
  in >> w;
  in.close();
  cout << w << endl;
  LevelReader lr;
  std::string path_to_file_ = ("/home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/levels/room18.txt");
  int left_bound = path_to_file_.find("room");
  int right_bound = path_to_file_.find(".txt");
  std::string level = path_to_file_.substr(left_bound+4, right_bound-left_bound-4);
  
  std::cout << "LEVEL READER:" << level << std::endl;
  // See your notes about this

  //generateLevelMOD(10, 10, 1);


  cout << "START MAIN" << endl;
  // TODO: maybe make not string? array[][]
  // Make inventory to player
  // Add level generator, see your notes
  terminal_open();
  // terminal_set("Symbolica.ini");
  // terminal_set("Symbolica.BearLibTerminal.window.title='Wowing'"); Not working

  //terminal_set("window.title='wow'; window.size=40x40;");
  terminal_set("window.resizeable=true; window.size=100x100");
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
