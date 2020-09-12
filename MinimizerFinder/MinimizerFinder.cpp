// MinimizerFinder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

HWINEVENTHOOK hEvent = NULL;

VOID CALLBACK WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);

int main()
{
	hEvent = SetWinEventHook(EVENT_SYSTEM_FOREGROUND,
		EVENT_SYSTEM_FOREGROUND, NULL,
		WinEventProcCallback, 0, 0,
		WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    return 0;
}

VOID CALLBACK WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	char buffer[MAX_PATH] = { 0 };
	DWORD dwProcId = 0;
	DWORD dwBufferSize = MAX_PATH;

	GetWindowThreadProcessId(hwnd, &dwProcId);

	HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcId);
	QueryFullProcessImageNameA(hProc, 0, buffer, &dwBufferSize);
	CloseHandle(hProc);

	std::cout << buffer << std::endl;
}
