#include "Window.h"
#include "Process.h"
#include "TrayIcon.h"
#include "Timer.h"
#include "Menu.h"
#include <memory>

Process process;
Timer timer;
std::shared_ptr<Window> window;
std::shared_ptr<Menu> menu;

static LRESULT CALLBACK MouseHook(int nCode, WPARAM wParam, LPARAM lParam) {
  bool isLeftCtrlPressed = GetKeyState(VK_LCONTROL) & 0x80;
  bool isNumOnePressed = GetKeyState('1') & 0x80;
  bool isLeftMouseKeyPressed = (wParam == WM_LBUTTONUP);

  bool isHotKey = isLeftCtrlPressed && isNumOnePressed && isLeftMouseKeyPressed;
  if (isHotKey) {  
    // if 'LeftCtrl + 1 + LeftMouseButton' clicked
    window->SetForeground();
    if(!window->GetForeground()) {
      FatalAppExit(0, TEXT("Couldn't get foreground window!"));
    }
    process.GetInfo(window->GetForeground());
    process.DisplayInfo(window->GetOurWindow());
    timer.Set(window->GetOurWindow());
  }
  return CallNextHookEx(0, nCode, wParam, lParam);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int iCmdShow ) {

  window = std::make_shared<Window>(hInstance);
  if(!window->GetOurWindow()) {
    FatalAppExit(0, TEXT("Couldn't create window!"));
  }

  std::unique_ptr<TrayIcon> trayIcon(new TrayIcon(window->GetOurWindow()));
  trayIcon->AddToTray();
  window->Show();

  HHOOK hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHook, GetModuleHandle(NULL), 0);

  MSG msg;
  while (GetMessage (&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hHook);
  return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  UINT uClicked;
  switch (message) 
  {
  case WM_CREATE:
    menu = std::make_shared<Menu>(process.StartsAtStartup());
    if (!menu->GetContextMenu() || !menu->GetUpdateMenu()) {
      FatalAppExit(0, TEXT("Couldn't create popup menu!"));
    }
    break;

  case WM_TRAYICON:   // if tray icon of AppFamilyTies is pressed
    if (lParam == WM_RBUTTONUP) // if right mouse button pressed, show context menu
    {  
      POINT curPoint;
      GetCursorPos(&curPoint);
      UINT cClicked = TrackPopupMenu(menu->GetContextMenu(), TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);
      switch (cClicked) 
      {
      case UPDATE_PERIOD:
        GetCursorPos(&curPoint);
        uClicked = TrackPopupMenu(menu->GetUpdateMenu(), TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);
        menu->CheckUpdateMenuRadioOption(FIVE_SECONDS, TEN_SECONDS, uClicked, MF_BYCOMMAND);
        if (uClicked == FIVE_SECONDS) {
          timer.SetUpdatePeriod(5);
        } else if (uClicked == TEN_SECONDS) {
          timer.SetUpdatePeriod(10); 
        }
        if (timer.GetUpdateTimer()) {
          timer.Kill(window->GetOurWindow());
          timer.Set(window->GetOurWindow());
        }
        break;
      case START_UP:
        process.ToggleStartup();
        if (process.StartsAtStartup()) {
          menu->CheckContextMenuOption(START_UP, MF_CHECKED);
        } else {
          menu->CheckContextMenuOption(START_UP, MF_UNCHECKED);
        }
        break;
      case EXIT:
        PostQuitMessage(0);
        break;
      default:
        break;
      }
    }
    break;

  case WM_TIMER:
    process.GetInfo(window->GetForeground());
    process.DisplayInfo(window->GetOurWindow());
    break;

  case WM_SYSCOMMAND:  
    if((wParam & 0xfff0) == SC_CLOSE) {  // if close window button is pressed
      timer.Kill(window->GetOurWindow());
      window->Show();
      return 0;
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    break;
  }
  return DefWindowProc(hwnd, message, wParam, lParam);
}