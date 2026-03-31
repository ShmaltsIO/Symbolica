#ifndef WORTH_COMPONENT_H
#define WORTH_COMPONENT_H

#include "IComponent.h"
/**
 * @brief The worth component for any entites.
 * @param worth_ private unsigned int;
 */
class WorthComponent: public IComponent {
private:
    unsigned int worth_;

public:
    WorthComponent();
    WorthComponent(unsigned int);

    void setWorth(unsigned int);
    unsigned int getWorth();
    unsigned int getWorth() const;

};

#endif // WORTH_COMPONENT_H