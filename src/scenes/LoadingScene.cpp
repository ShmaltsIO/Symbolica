#include "LoadingScene.h"
#include "BearLibTerminal.h"

LoadingScene::LoadingScene(Context* ctx): IScene(ctx) {}

void LoadingScene::OnCreate() {
    terminal_clear();
    terminal_color("black");
    terminal_print(1, 1, "LOADING @ @ @");
    terminal_refresh();
    terminal_delay(500);
    terminal_clear();
    terminal_color("darkest white");
    terminal_print(1, 1, "LOADING @ @ @");
    terminal_refresh();
    terminal_delay(500);
    terminal_clear();
    terminal_color("darker white");
    terminal_print(1, 1, "LOADING @ @ @");
    terminal_refresh();
    terminal_delay(500);
    terminal_clear();
    terminal_color("dark white");
    terminal_print(1, 1, "LOADING @ @ @");
    terminal_refresh();
    terminal_delay(500);
    terminal_clear();
    terminal_color("white");
    terminal_print(1, 1, "LOADING @ @ @");
    terminal_printf(3, 3, "Level: %d", context_->room_);
    terminal_refresh();
    terminal_delay(2000);
    terminal_clear();

    context_->is_load = true;
    context_->scene_ = "game";
}

void LoadingScene::OnRender() {

}

void LoadingScene::OnExit() {

}
