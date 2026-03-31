#ifndef STEP_LIMIT_COMPONENT_H
#define STEP_LIMIT_COMPONENT_H

#include "IComponent.h"

class StepLimitComponent: public IComponent {
private:
    unsigned int steps_limit_;

public:
    StepLimitComponent();
    StepLimitComponent(unsigned int);

    void setStepsLimit(unsigned int);
    unsigned int getStepLimit();
    unsigned int getStepLimit() const;

};


#endif // STEP_LIMIT_COMPONENT_H