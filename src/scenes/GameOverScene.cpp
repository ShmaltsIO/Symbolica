#include "GameOverScene.h"
#include <BearLibTerminal.h>
#include "SceneType.h"
#include "TxtReader.h"

GameOverScene::GameOverScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void GameOverScene::OnCreate() {}

void GameOverScene::OnRender() {
  terminal_clear();

  TxtReader tr("assets/gui/low/lose.txt"); // TODO: make abstract

  std::string sup = tr.read();

  terminal_print(1, 1, sup.c_str());
  
  // Game Stats
  terminal_printf(1, 8, "Game statistics: name");
  terminal_printf(2, 9, "Steps complected: %d", context_->game_stats->getStepsCompleted());
  terminal_printf(2, 10, "Coins collected: %d", context_->game_stats->getMoneyCollected());

  terminal_print(10, 11, "Press Еnter to go to main menu");
  if (controls_.IsPressed(TK_ENTER)) {
    context_->scene = SceneType::TitleScene;
    //context_->is_game_over = true;
  }

  terminal_refresh();
}

void GameOverScene::OnExit() {}
