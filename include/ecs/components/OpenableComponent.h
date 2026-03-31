#ifndef OPENABLE_COMPONENT_H
#define OPENABLE_COMPONENT_H

#include "IComponent.h"

class OpenableComponent: public IComponent {
private:
    bool is_open_;
public:
    OpenableComponent();

    void setOpen();
    bool getStatus();
    bool getStatus() const;
};

#endif // OPENABLE_COMPONENT_H