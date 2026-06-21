#include "GameWinScene.h"

GameWinScene::GameWinScene(Context* context, const Controls& controls):
 IScene(context), controls_(controls) {}

void GameWinScene::OnCreate() {}

void GameWinScene::OnRender() {
    terminal_clear();

    TxtReader tr("assets/gui/low/win.txt"); // TODO: ...

    std::string sup = tr.read();

    unsigned int x = context_->ui_settings->getPaddingWidth() * 5;
    unsigned int y = context_->ui_settings->getPaddingHeight() * 2;

    terminal_print(x, y, sup.c_str());

    y = y + tr.getLinesCount() + 1;
    
    // Game Stats
    terminal_printf(x, y, "Game statistics: PLAYER_NAME");
    terminal_printf(x + 2, y + 2, "Steps complected: %d", context_->game_stats->getStepsCompleted());
    terminal_printf(x + 2, y + 4, "Coins collected: %d", context_->game_stats->getMoneyCollected());

    terminal_print(x, y + 6, "Press Еnter to go to main menu");

    if (controls_.IsPressed(TK_ENTER)) {
        context_->scene = SceneType::TitleScene;
    }

    terminal_refresh();
}

void GameWinScene::OnExit() {}
