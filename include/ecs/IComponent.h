#ifndef ICOMPONENT_H
#define ICOMPONENT_H

/**
 * @brief Interface for components.
 * 
 * Component is some data, without methods of hadling his own fileds.
 */
class IComponent {
 public:
  virtual ~IComponent() = default;
};

#endif  // ICOMPONENT_H
