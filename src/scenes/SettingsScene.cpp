#include "SettingsScene.h"
#include "BearLibTerminal.h"

SettingsScene::SettingsScene(Context* context, const Controls& controls):
 IScene(context), controls_(controls) {}

void SettingsScene::OnCreate() {}

void SettingsScene::OnRender() {
    terminal_clear();
    //terminal_set("font: /home/lesnoy-elf/Документы/cProjects/shmalts.edgar-game/src/symbolica/fonts/Prototype.ttf, size=12");
    terminal_print(1, 1, "If you want change graphics, just press F to pay signal for high-quality switcher!");
    terminal_print(3, 3, "For go back to menu, press ЕSC (ЕSCAPЕ)");
    terminal_print(4, 4, "See, how change the graphics:");
    terminal_put(5, 5, 0x0023);
    // terminal_print(7, 7, "WARNING: some symbols can be incorrect");
    terminal_refresh();

    if (controls_.IsPressed(TK_F)) {
        if (graphic_on) {
            terminal_set("0x0023: none");
            terminal_set("0x0024: none");
            terminal_set("0x0025: none");
            terminal_set("0x0040: none");
            terminal_set("0x0045: none");
            terminal_set("0x0058: none");
            terminal_set("0x004B: none");
            terminal_set("0x002E: none");
            terminal_set("0x003E: none");
            terminal_set("0x003C: none");
            terminal_set("0x003F: none");
            terminal_set("0x007C: none");
            terminal_set("0x007D: none");
            
            graphic_on = false;
        } else {    
            terminal_set("0x0023: B:/cProjects/shmalts.edgar-game/GamePictures/tileWall.png");
            terminal_set("0x0024: B:/cProjects/shmalts.edgar-game/GamePictures/tileCoin.png");
            terminal_set("0x0025: B:/cProjects/shmalts.edgar-game/GamePictures/tileFood.png");
            terminal_set("0x0040: B:/cProjects/shmalts.edgar-game/GamePictures/tilePlayer.png");
            terminal_set("0x0045: B:/cProjects/shmalts.edgar-game/GamePictures/tileEnemy.png");
            terminal_set("0x0058: B:/cProjects/shmalts.edgar-game/GamePictures/tileChest.png");
            terminal_set("0x004B: B:/cProjects/shmalts.edgar-game/GamePictures/tileKey.png");
            terminal_set("0x002E: B:/cProjects/shmalts.edgar-game/GamePictures/tileGround.png");
            terminal_set("0x003E: B:/cProjects/shmalts.edgar-game/GamePictures/tileDoorNext.png");
            terminal_set("0x003C: B:/cProjects/shmalts.edgar-game/GamePictures/tileDoorPrev.png");
            terminal_set("0x003F: B:/cProjects/shmalts.edgar-game/GamePictures/tileNPC.png");
            terminal_set("0x007C: B:/cProjects/shmalts.edgar-game/GamePictures/tileBronzeSword.png");
            terminal_set("0x007D: B:/cProjects/shmalts.edgar-game/GamePictures/tileIronArmor.png");
            graphic_on = true;
        }
    }
    // Go back to main menu (title)
    if (controls_.IsPressed(TK_ESCAPE)) {
        context_->scene_ = "title";
    }
}

void SettingsScene::OnExit() {
    terminal_clear();
}
