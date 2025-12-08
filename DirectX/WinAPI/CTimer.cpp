#include "CTimer.h"

void CTimer::Init()
{
	// 시간 간격 측정에 사용할 수 있는 고해상도(<1us) 타임스탬프를 나타내는 성능 카운터의 현재 값을 검색합니다.
	QueryPerformanceFrequency(&mFrequency);

	// 성능 카운터의 빈도를 검색합니다. 성능 카운터의 빈도는 시스템 부팅 시 고정되며 모든 프로세서에서 일관됩니다.
	// 따라서 빈도는 애플리케이션 초기화 시 쿼리해야 하며 결과를 캐시할 수 있습니다.
	QueryPerformanceCounter(&mPrevCount);
}

float CTimer::Update()
{
	LARGE_INTEGER Count;

	// 현재 프레임의 카운트를 구한다.
	QueryPerformanceCounter(&Count);

	// 현재 프레임의 카우늩와 이전 프레임의 카운트의 차이를 구하고
	// 이 차이를 초당 카운트로 나누어 흐를 시간을 구한다.
	mDeltaTime = static_cast<float>(Count.QuadPart - mPrevCount.QuadPart) / static_cast<float>(mFrequency.QuadPart);

	// 현재 프레임의 카운트를 이전 프레임의 카운트에 저장하여 다음 프레임에서 시간을 구할 수 있게 한다.
	mPrevCount = Count;

	return mDeltaTime;
}
