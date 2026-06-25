#ifndef NAME_COMPONENT_H
#define NAME_COMPONENT_H

#include <string>

#include "IComponent.h"

/**
 * @brief Name component for entities.
 */
class NameComponent : public IComponent {
private:
    std::string name = "";
    std::string title = "";

public:
    NameComponent() = default;
    NameComponent(std::string name, std::string title): name(name), title(title) {}

    std::string getName();
    std::string getTitle();
    std::string getName() const;
    std::string getTitle() const;
    std::string getFullName();
    std::string getFullName() const;

    void setName(std::string);
    void setTitle(std::string);
};

#endif // NAME_COMPONENT_H