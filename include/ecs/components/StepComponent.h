#ifndef STEP_COMPONENT_H
#define STEP_COMPONENT_H

#include "IComponent.h"

class StepComponent: public IComponent {
private:
    unsigned int steps_;
    //unsigned int steps_limit_;

public:
    StepComponent();
    StepComponent(unsigned int);

    void setSteps(unsigned int);
    unsigned int getSteps();
    unsigned int getSteps() const;

    // void setSteps(unsigned int);
    // unsigned int getSteps();
    // unsigned int getSteps() const;
};

#endif // STEP_COMPONENT_H