#ifndef COLOR_COMPONENT_H
#define COLOR_COMPONENT_H

#include "IComponent.h"
#include <string>

class ColorComponent: public IComponent {
private:
    std::string color_;

public:
    ColorComponent();
    ColorComponent(std::string);

    void setColor(std::string);
    std::string getColor();
    std::string getColor() const;
};

#endif // COLOR_COMPONENT_H