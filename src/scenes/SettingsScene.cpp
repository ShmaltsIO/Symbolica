#include "SettingsScene.h"
#include "BearLibTerminal.h"
#include "SceneType.h"

SettingsScene::SettingsScene(Context* context, const Controls& controls):
 IScene(context), controls_(controls) {}

void SettingsScene::OnCreate() {}

void SettingsScene::OnRender() {
    terminal_clear();
    //terminal_set("font: ./assets/fonts/Prototype.ttf, size=12");
    terminal_print(1, 1, "If you want change graphics, just press F to pay signal for high-quality switcher!");
    terminal_print(3, 3, "For go back to menu, press ЕSC (ЕSCAPЕ)");
    terminal_print(4, 4, "See, how change the graphics:");
    terminal_put(5, 5, 0x0023);
    // terminal_print(7, 7, "WARNING: some symbols can be incorrect");
    terminal_refresh();

    if (controls_.IsPressed(TK_F)) {
        graphic_on = !graphic_on;
        const char* qualitySection = graphic_on ? "graphics_high" : "graphics_low";
        // Переустанавливаем все тайлы заново
        // context_->tilemapConfig->applyToTerminal(qualitySection);
        // Также, возможно, нужно переприменить gui, если он тоже меняется
        //tilemap.applyToTerminal("gui");
    }
    // Go back to main menu (title)
    if (controls_.IsPressed(TK_ESCAPE)) {
        context_->scene = SceneType::TitleScene;
    }
}

void SettingsScene::OnExit() {
    terminal_clear();
}
