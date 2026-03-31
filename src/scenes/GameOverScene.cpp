#include "GameOverScene.h"
#include <BearLibTerminal.h>

GameOverScene::GameOverScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void GameOverScene::OnCreate() {}

void GameOverScene::OnRender() {
  terminal_clear();
  // TODO: one backslash is \\ because compiler think, that's backslash is escape sequence like \n
  terminal_print(1, 1, "╔══════════════════════════════════════════════════════════╗");
  terminal_print(1, 2, "║   ___   ___  ___  ___  ____      ___   __ __  ____ ____  ║");
  terminal_print(1, 3, "║  // \\\\ // \\\\ ||\\\\//|| ||        // \\\\  || || ||    || \\\\ ║");
  terminal_print(1, 4, "║ (( ___ ||=|| || \\\\/|| ||==     ((   )) \\\\ // ||==  ||_// ║");
  terminal_print(1, 5, "║  \\\\_|| || || ||    || ||___     \\\\_//  \\\\V/  ||___ || \\\\ ║");
  terminal_print(1, 6, "║                                                          ║");
  terminal_print(1, 7, "╚══════════════════════════════════════════════════════════╝");                     
  
  // Game Stats
  terminal_printf(1, 8, "Game statistics: name");
  terminal_printf(2, 9, "Steps complected: %d", context_->steps_completed);
  terminal_printf(2, 10, "Coins collected: %d", context_->money_collected_);

  terminal_print(10, 11, "Press Еnter to go to main menu");
  if (controls_.IsPressed(TK_ENTER)) {
    context_->scene_ = "title";
    context_->is_game_over = true;
  }

  terminal_refresh();
}

void GameOverScene::OnExit() {}
