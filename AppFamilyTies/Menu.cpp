#include "Menu.h"

const TCHAR *APP_NAME = "AppFamilyTies";

Menu::Menu(bool startup) {
  _contextMenu = CreatePopupMenu();
  _updateMenu = CreatePopupMenu();
  
  AppendMenu(_contextMenu, MF_STRING, UPDATE_PERIOD, TEXT("Update period"));
  if (startup) {
    AppendMenu(_contextMenu, MF_ENABLED | MF_CHECKED, START_UP, TEXT("Start with Windows"));
  } else {
    AppendMenu(_contextMenu, MF_ENABLED | MF_UNCHECKED, START_UP, TEXT("Start with Windows"));
  }
  AppendMenu(_contextMenu, MF_STRING, EXIT, TEXT("Exit"));

  AppendMenu(_updateMenu, MF_STRING, FIVE_SECONDS, TEXT("5 seconds")); 
  AppendMenu(_updateMenu, MF_STRING, TEN_SECONDS, TEXT("10 seconds")); 
  CheckMenuRadioItem(_updateMenu, FIVE_SECONDS, TEN_SECONDS, FIVE_SECONDS, MF_BYCOMMAND);
}

Menu::~Menu() {
  DeleteMenu(_updateMenu, FIVE_SECONDS, MF_BYCOMMAND);
  DeleteMenu(_updateMenu, TEN_SECONDS, MF_BYCOMMAND);
  DeleteMenu(_contextMenu, UPDATE_PERIOD, MF_BYCOMMAND);
  DeleteMenu(_contextMenu, START_UP, MF_BYCOMMAND);
  DeleteMenu(_contextMenu, EXIT, MF_BYCOMMAND);
}