#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include "IScene.h"
#include "Controls.h"

class SettingsScene: public IScene {
private:
    const Controls& controls_;
    bool graphic_on = false;

public:
    SettingsScene(Context* ctx, const Controls& controls);

    void OnCreate() override;
    void OnRender() override;
    void OnExit() override;
};

#endif // SETTINGS_SCENE_H