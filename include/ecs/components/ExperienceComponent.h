#ifndef EXPERIENCE_COMPONENT_H
#define EXPERIENCE_COMPONENT_H

#include "IComponent.h"

/**
 * @brief Class for player's experience.
 * @param experience_ is current value of exp.
 * @param experience_limit_ is required number for achieve a next level.
 */
class ExperienceComponent: public IComponent {
private:
    unsigned int experience_ = 0;
    unsigned int experience_limit_ = 10;
public:
    ExperienceComponent();
    ExperienceComponent(unsigned int, unsigned int);

    void setExperience(unsigned int);
    unsigned int getExperience();
    unsigned int getExperience() const;

    void setExperienceLimit(unsigned int);
    unsigned int getExperienceLimit();
    unsigned int getExperienceLimit() const;
};

#endif // EXPERIENCE_COMPONENT_H