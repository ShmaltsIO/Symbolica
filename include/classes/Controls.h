#ifndef CONTROLS_H
#define CONTROLS_H

#include <BearLibTerminal.h>
#include <map>
#include <vector>

class Controls {
private:
  std::map<int, bool> is_pressed_{};

public:
  void Press(int);

  bool IsPressed(int) const;

  void Reset();

  void OnUpdate();
};

#endif  // CONTROLS_H
