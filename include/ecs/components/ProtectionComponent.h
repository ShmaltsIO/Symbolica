#ifndef PROTECTION_COMPONENT_H
#define PROTECTION_COMPONENT_H

#include "IComponent.h"

class ProtectionComponent: public IComponent {
private:
    unsigned int protection_;

public:
    ProtectionComponent();
    ProtectionComponent(unsigned int);

    void setProtection(unsigned int);
    unsigned int getProtection();
    unsigned int getProtection() const;
};

#endif // PROTECTION_COMPONENT_H