#include "GameWinScene.h"
#include "SceneType.h"
#include "TxtReader.h"

GameWinScene::GameWinScene(Context* context, const Controls& controls):
 IScene(context), controls_(controls) {}

void GameWinScene::OnCreate() {}

void GameWinScene::OnRender() {
    terminal_clear();

    TxtReader tr("assets/gui/low/win.txt"); // TODO: ...

    std::string sup = tr.read();

    terminal_print(1, 1, sup.c_str());
    
    // Game Stats
    terminal_printf(1, 8, "Game statistics: name");
    terminal_printf(2, 9, "Steps complected: %d", context_->game_stats->getStepsCompleted());
    terminal_printf(2, 10, "Coins collected: %d", context_->game_stats->getMoneyCollected());

    terminal_print(10, 11, "Press Еnter to go to main menu");
    if (controls_.IsPressed(TK_ENTER)) {
        context_->scene = SceneType::TitleScene;
    }

    terminal_refresh();
}

void GameWinScene::OnExit() {}
