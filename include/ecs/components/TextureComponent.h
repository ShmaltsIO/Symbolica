#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H
#include "IComponent.h"

class TextureComponent : public IComponent {
 public:
  char symbol_;

  explicit TextureComponent(char);
};
#endif  // TEXTURE_COMPONENT_H
