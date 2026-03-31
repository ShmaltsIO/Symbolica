#ifndef RADIUS_COMPONENT_H
#define RADIUS_COMPONENT_H

#include "IComponent.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Vector2DComparator.h"
#include "Vector2DHash.h"
#include <vector>

/**
 * @brief This component contains a Von Neumann neighborhood.
 * @param neighborhood_ is vector of ID's of entites.
 */
class RadiusComponent: public IComponent {
private:
    std::vector<size_t> neighborhood_{};

public:
    RadiusComponent();

    void setNeighborhood(std::vector<size_t>);
    std::vector<size_t> getNeighborhood();
    std::vector<size_t> getNeighborhood() const;
    
};

#endif // RADIUS_COMPONENT_H