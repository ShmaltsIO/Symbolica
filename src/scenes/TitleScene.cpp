#include "TitleScene.h"

TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void TitleScene::OnCreate() {
  terminal_clear();
}

void TitleScene::OnRender() {
  terminal_clear();

  terminal_put(30, 30, 0x1000); // TEST SYMBOLS
  
  unsigned int x = context_->ui_settings->getPaddingWidth()*5;
  unsigned int y = context_->ui_settings->getPaddingHeight()*2;

  TxtReader tr("assets/gui/low/logo.txt"); // TODO: make abstract

  std::string sup = tr.read();

  // If is first game, play animation else no
  if (is_start) {
    unsigned int iter = 0;

    while(iter != y) {
      terminal_clear();
      terminal_print(x, iter, sup.c_str());
      terminal_refresh();
      terminal_delay(300);
      iter++;
    }

    is_start = !is_start;
  }

  terminal_print(x, y, sup.c_str());

  y = y + tr.getLinesCount();
  x *= 2;

  // Print menu's punkts
  terminal_print(x, y+5, "Start game");
  terminal_print(x, y+7, "Load game");
  terminal_print(x, y+9, "Setting");
  terminal_print(x, y+11, "Еxit");
  // Print selection thing
  terminal_print(x-3, y+offset, "->");
  
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
        context_->scene = SceneType::GameScene;
        break;
      case (7):
          /* code */
        break;
      case (9):
        context_->scene = SceneType::SettingsScene;
        break;
      case (11):
          /* code */
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
