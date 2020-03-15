#ifndef MENU_H
#define MENU_H

#include "general.h"

class Menu {
public:
  explicit Menu(bool startup);
  ~Menu();

  HMENU GetContextMenu(void) const { return _contextMenu; }
  HMENU GetUpdateMenu(void) const { return _updateMenu; }
  bool CheckUpdateMenuRadioOption(UINT first, UINT last, UINT check, UINT flags);
  DWORD CheckContextMenuOption(UINT uIDCheckItem, UINT uCheck);

private:
  HMENU _contextMenu, _updateMenu;
};

#endif  // !MENU_H