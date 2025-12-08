#pragma once
#include <windows.h>

#include "../WinAPI/Info.h"

class CGameManager
{
private:
	static constexpr WCHAR WINDOW_CLASS_NAME[] = TEXT("WinAPI2");
	static constexpr WCHAR WINDOW_TITLE[] = TEXT("WinAPI2");

public:
	bool Init(HINSTANCE hInstance);
	int Run();

private:
	void GameLoop(float DeltaTime);

private:
	void InitRegisterClass() const;
	bool InitCreateWindow();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE hInst = nullptr;
	HWND hWnd = nullptr;
	HDC hDC = nullptr;
	inline static bool bLoop = true;

public:
	static CGameManager* GetInst()
	{
		if (inst == nullptr)
		{
			inst = new CGameManager;
		}

		return inst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(inst)
	}

private:
	CGameManager() = default;
	~CGameManager();

	inline static CGameManager* inst = nullptr;
};

