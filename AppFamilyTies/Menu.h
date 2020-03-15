#ifndef MENU_H
#define MENU_H

#include "general.h"

class Menu {
public:
  explicit Menu(bool startup);
  ~Menu();

  HMENU GetContextMenu(void) const { return _contextMenu; }
  HMENU GetUpdateMenu(void) const { return _updateMenu; }
private:
  HMENU _contextMenu, _updateMenu;
};

#endif  // !MENU_H