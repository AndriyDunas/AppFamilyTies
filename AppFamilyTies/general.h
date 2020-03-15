#ifndef GENERAL_H
#define GENERAL_H

#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <string>
#pragma comment(lib, "psapi.lib")

#define APP_TRAY_ICON       5000
#define EXIT                5001
#define UPDATE_PERIOD       5002
#define START_UP            5003 
#define TIMER_ID            5004
#define FIVE_SECONDS        5005
#define TEN_SECONDS         5006

#define WM_TRAYICON         (WM_USER + 1)

#define SUB_KEY             "Software\\Microsoft\\Windows\\CurrentVersion\\Run"

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // !GENERAL_H