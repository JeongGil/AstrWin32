#pragma once

#include "Info.h"

class CGameManager
{
private:
    CGameManager();
    ~CGameManager();

private:
    HINSTANCE   mhInst;
    HWND        mhWnd;
    HDC         mhDC;
    static bool mLoop;

public:
    bool Init(HINSTANCE hInst);
    int Run();

private:
    void Logic();

private:
    // 윈도우 레지스터 클래스 등록
    void InitRegisterClass();
    // 윈도우 창 생성
    bool Create();

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    static CGameManager* mInst;

public:
    static CGameManager* GetInst()
    {
        if (!mInst)
            mInst = new CGameManager;
        return mInst;
    }

    static void DestroyInst()
    {
        SAFE_DELETE(mInst);
    }
};

