#pragma once

#include <Windows.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <chrono>

// 메모리 릭 검사용
#include <crtdbg.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "resource.h"

#define SAFE_DELETE(p)       { if(p) { delete (p); (p)=nullptr; } }