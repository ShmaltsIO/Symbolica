#include "Controls.h"

void Controls::Press(int btn_key) {
    is_pressed_[btn_key] = true;
  }

  bool Controls::IsPressed(int btn_key) const {
    if (is_pressed_.count(btn_key) == 0) {
      return false;
    }
    return is_pressed_.at(btn_key);
  }
  void Controls::Reset() {
    for (auto& btn : is_pressed_) {
      btn.second = false;
    }
  }

  void Controls::OnUpdate() {
    while (terminal_has_input()) {
      auto key = terminal_read();
      is_pressed_[key] = true;
    }
  }
