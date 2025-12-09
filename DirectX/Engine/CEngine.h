#pragma once

#include "EngineInfo.h"

class CEngine
{
private:
	static constexpr WCHAR WINDOW_CLASS_NAME[] = TEXT("WinAPI2");
	static constexpr WCHAR WINDOW_TITLE[] = TEXT("WinAPI2");

public:
	bool Init(HINSTANCE hInstance, const TCHAR* WindowName, int IconID, int SmallIconID, int Width, int Height, bool WindowMode);
	int Run();

private:
	void GameLoop(float DeltaTime);

private:
	void InitRegisterClass(const TCHAR* WindowName, int IconID, int SmallIconID) const;
	bool InitCreateWindow(const TCHAR* WindowName);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInst = nullptr;
	HWND hWnd = nullptr;

	inline static bool bLoop = true;

public:
	static CEngine* GetInst()
	{
		if (inst == nullptr)
		{
			inst = new CEngine;
		}

		return inst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(inst)
	}

private:
	CEngine();
	~CEngine();

	inline static CEngine* inst = nullptr;
};

