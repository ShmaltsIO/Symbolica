#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "IScene.h"
#include "Controls.h"
#include "Context.h"

/**
 * @brief Game scene is main part of the game.
 * @param engine is TODO
 * @param controls is input's handle.
 * @param player_ is copy of player entity, used in transition between levels.
 * @param previous_level_ is code of previous level.
 */
class GameScene : public IScene {
private:
    const Controls& controls_;
    int currentLevelId_ = 1;
    bool levelLoaded_ = false;

    void loadLevel(int levelNumber);
    void clearLevel();

public:
    GameScene(Context* context, const Controls& controls);
    ~GameScene() override = default;

    void OnCreate() override;
    void OnRender() override;
    void OnExit() override;
};

#endif  // GAME_SCENE_H
