#include "SettingsScene.h"
#include "BearLibTerminal.h"
#include "SceneType.h"
#include "TxtReader.h"

SettingsScene::SettingsScene(Context* context, const Controls& controls):
 IScene(context), controls_(controls) {}

void SettingsScene::OnCreate() {}

void SettingsScene::OnRender() {
    terminal_clear();

    //terminal_set("font: ./assets/fonts/Prototype.ttf, size=12"); // Experiment

    TxtReader tr("assets/gui/low/settings.txt"); // TODO: ...

    std::string sup = tr.read();

    unsigned int x = context_->ui_settings->getPaddingWidth() * 6;
    unsigned int y = context_->ui_settings->getPaddingHeight() * 2;

    terminal_print(x, y, sup.c_str());

    y = y + tr.getLinesCount() + 1;

    terminal_print(x, y, "If you want change graphics, just press F to pay signal for high-quality switcher!");
    terminal_print(x, y+1, "For go back to menu, press ЕSC (ЕSCAPЕ)");
    terminal_print(x, y+2, "See, how change the graphics:");
    
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
