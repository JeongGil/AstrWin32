#pragma once

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }

struct FPoint
{
	float x = 0.f;
	float y = 0.f;
};