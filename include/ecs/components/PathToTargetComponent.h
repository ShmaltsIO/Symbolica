#ifndef PATH_TO_TARGET_H
#define PATH_TO_TARGET_H

#include "IComponent.h"
#include "Vector2D.h"
#include <vector>

class PathToTargetComponent: public IComponent {
private:
    std::vector<Vector2D> path_to_target_;

public:
    PathToTargetComponent();

    void setPathToTarget(std::vector<Vector2D>);
    std::vector<Vector2D>& getPathToTarget();
    const std::vector<Vector2D>& getPathToTarget() const;
};

#endif // PATH_TO_TARGET_H