#include "Process.h"
#include <tchar.h>
#include <memory>

extern const TCHAR *APP_NAME;

void Process::SaveInfo(DWORD pid) {
  HANDLE procHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
  std::string spid = std::to_string( (static_cast<unsigned long long>(pid)) );
  _procInfo += spid;

  if (procHandle) {
	std::shared_ptr<TCHAR> fileName(new TCHAR[MAX_PATH], std::default_delete<TCHAR[]>());
	if (GetModuleFileNameEx(static_cast<HMODULE>(procHandle), 0, (LPSTR)fileName.get(), MAX_PATH)) {
      _procInfo += "\nName: ";
	  _procInfo += fileName.get();
    }
    CloseHandle(procHandle);
  }
}

void Process::GetInfo(HWND fhwnd) {
  DWORD pid = 0;
  _procInfo = "Current Process:\nPID: ";
  GetWindowThreadProcessId(fhwnd, &pid);
  SaveInfo(pid);

  HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (!snap) {
    FatalAppExit(0, TEXT("Couldn't create snapshot!"));
  }
  PROCESSENTRY32 pe = {0};
  pe.dwSize = sizeof(PROCESSENTRY32);
  if (Process32First(snap, &pe)) {
    do {
      if (pe.th32ProcessID == pid) {
        _procInfo += "\nParent process:\nPID: ";
        SaveInfo(pe.th32ParentProcessID);
      }
      if (pid == pe.th32ParentProcessID) {
        _procInfo += "\nChild process:\nPID: ";
        SaveInfo(pe.th32ProcessID);
      }
    } while( Process32Next(snap, &pe));
  }
  CloseHandle(snap);
}

void Process::DisplayInfo(HWND hwnd) const { 
  CreateWindow(TEXT("static"), (LPCSTR)_procInfo.c_str(), 
    WS_CHILD | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 400, hwnd, NULL, 0, NULL);
  SetForegroundWindow(hwnd);
  ShowWindow(hwnd, SW_NORMAL);
}

bool Process::StartsAtStartup() const {
  std::unique_ptr<TCHAR[]> us(new TCHAR[MAX_PATH](), std::default_delete<TCHAR[]>());
  std::unique_ptr<TCHAR[]> them(new TCHAR[MAX_PATH](), std::default_delete<TCHAR[]>());
  DWORD len = MAX_PATH;
  HKEY run;
  GetModuleFileName(NULL, (LPSTR)us.get(), MAX_PATH);
  RegOpenKey(HKEY_CURRENT_USER, SUB_KEY, &run);
  RegQueryValueEx(run, APP_NAME, NULL, NULL, (LPBYTE)them.get(), &len);
  RegCloseKey(run);
  return !_tcscmp(us.get(), them.get());
}

void Process::ToggleStartup() const {
  HKEY run;
  RegOpenKey(HKEY_CURRENT_USER, SUB_KEY, &run);
  if (StartsAtStartup()) {
    RegDeleteValue(run, APP_NAME);
  } else {
    TCHAR us[MAX_PATH]; // аррей на стеку
    RegCreateKey(HKEY_CURRENT_USER, SUB_KEY, &run);
    GetModuleFileName(NULL, us, MAX_PATH);
    RegSetValueEx(run, APP_NAME, 0, REG_SZ, reinterpret_cast<LPBYTE>(us), MAX_PATH);
  }
  RegCloseKey(run);
}