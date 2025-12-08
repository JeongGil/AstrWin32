#include "CGameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	if (!CGameManager::GetInst()->Init(hInstance))
	{
		return FALSE;
	}

	int Ret = CGameManager::GetInst()->Run();
	CGameManager::DestroyInst();

	return Ret;
}