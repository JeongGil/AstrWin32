#pragma once
#include "Info.h"

class CTimer
{
private:
	inline static LARGE_INTEGER mFrequency = LARGE_INTEGER();	// 초당 카운트 수
	inline static LARGE_INTEGER mPrevCount = LARGE_INTEGER();	// 이전 프레임의 초당 카운트 수
	inline static float mDeltaTime = 0.f;						// 이전 프레임 시작에서 이전 프레임 끝까지의 시간.

public:
	static void Init();
	static float Update();
};

