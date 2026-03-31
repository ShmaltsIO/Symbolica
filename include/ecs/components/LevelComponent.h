#ifndef LEVEL_COMPONENT_H
#define LEVEL_COMPONENT_H

#include "IComponent.h"

/**
 * @brief Class for player's levels.
 * @param level_ is current level of player (or entity).
 */
class LevelComponent: public IComponent {
private:
    unsigned int level_;
public:
    LevelComponent();
    LevelComponent(unsigned int);

    unsigned int getLevel();
    void setLevel(unsigned int);

    unsigned int getLevel() const;
};

#endif // LEVEL_COMPONENT_H