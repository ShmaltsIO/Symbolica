#include "TitleScene.h"
#include <BearLibTerminal.h>
//#include "SceneTypesEnum.h"
#include <iostream>
TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void TitleScene::OnCreate() {
  terminal_clear();
}

void TitleScene::OnRender() {
  // TODO: How control the size of window?
  terminal_clear();
  int x = 10;
  int y = 0;
  // If is first game, play animation else no
  if (!is_start) {
    y = 12;
  }
  // Play animation
  // while(y != 12) {
  //   std::cout << "Y: " << y << std::endl;
  //   terminal_clear();
  //   terminal_print(x, y-8, "╔═════════════════════════════════════════════════════════════════════════════╗");
  //   terminal_print(x, y-7, "║                                                                             ║");
  //   terminal_print(x, y-6, "║    SSSSS  YY   YY MM    MM BBBBB    OOOOO  LL      IIIII  CCCCC    AAA      ║");
  //   terminal_print(x, y-5, "║   SS      YY   YY MMM  MMM BB   B  OO   OO LL       III  CC    C  AAAAA     ║");
  //   terminal_print(x, y-4, "║    SSSSS   YYYYY  MM MM MM BBBBBB  OO   OO LL       III  CC      AA   AA    ║");
  //   terminal_print(x, y-3, "║        SS   YYY   MM    MM BB   BB OO   OO LL       III  CC    C AAAAAAA    ║");
  //   terminal_print(x, y-2, "║    SSSSS    YYY   MM    MM BBBBBB   OOOOO  LLLLLLL IIIII  CCCCC  AA   AA    ║");
  //   terminal_print(x, y-1, "║                                                                             ║");
  //   terminal_print(x, y,   "╚═════════════════════════════════════════════════════════════════════════════╝");
  //   terminal_refresh();
  //   terminal_delay(200);
  //   y++;
  // }
  // Stop menu appear
  is_start = false;
  terminal_print(x, y-8, "╔═════════════════════════════════════════════════════════════════════════════╗");
  terminal_print(x, y-7, "║                                                                             ║");
  terminal_print(x, y-6, "║    SSSSS  YY   YY MM    MM BBBBB    OOOOO  LL      IIIII  CCCCC    AAA      ║");
  terminal_print(x, y-5, "║   SS      YY   YY MMM  MMM BB   B  OO   OO LL       III  CC    C  AAAAA     ║");
  terminal_print(x, y-4, "║    SSSSS   YYYYY  MM MM MM BBBBBB  OO   OO LL       III  CC      AA   AA    ║");
  terminal_print(x, y-3, "║        SS   YYY   MM    MM BB   BB OO   OO LL       III  CC    C AAAAAAA    ║");
  terminal_print(x, y-2, "║    SSSSS    YYY   MM    MM BBBBBB   OOOOO  LLLLLLL IIIII  CCCCC  AA   AA    ║");
  terminal_print(x, y-1, "║                                                                             ║");
  terminal_print(x, y,   "╚═════════════════════════════════════════════════════════════════════════════╝");
  // Print menu's punkts
  terminal_print(x*4, y+5, "Start game");
  terminal_print(x*4, y+7, "Load game");
  terminal_print(x*4, y+9, "Setting");
  terminal_print(x*4, y+11, "Еxit");
  // Print selection thing
  terminal_print(x*4-3, y+offset, "@");
  terminal_put(30, 30, 0x1000);
  terminal_refresh();
  
  // Change offset
  if (controls_.IsPressed(TK_DOWN) || controls_.IsPressed(TK_S)) {
    offset += 2;
  }
  if (controls_.IsPressed(TK_UP) || controls_.IsPressed(TK_W)) {
    offset -= 2;
  }
  // check bounds of offset
  if (offset > 11) {
    offset = 5;
  }
  if (offset < 5) {
    offset = 11;
  }
  // switch menu's punkt
  if (controls_.IsPressed(TK_ENTER)) {
    switch (offset)
    {
      case (5):
        context_->scene_ = "game";
        context_->is_start = true;
        break;
      case (7):
        /* code */
        // is_load = true;
        break;
      case (9):
        context_->scene_ = "settings";
        break;
      case (11):
        context_->scene_ = "exit";
        break;
      
      default:
        break;
    }
  }
  
}
void TitleScene::OnExit() {
  is_start = false;
  terminal_clear();
}
