#include "Random.h"

Random::Random()
{
    uint32 seed = static_cast<uint32>(time(nullptr));
    Initialize(seed);
}

// Seed를 지정하여 초기화하는 생성자
Random::Random(uint32 seed)
{
    Initialize(seed);
}

// 새로운 Seed로 난수 생성기를 초기화합니다.
void Random::Initialize(uint32 InSeed)
{
    m_randomEngine.seed(InSeed);
}

// 지정된 범위 내의 정수 난수를 생성합니다.
int32 Random::Rand(int32 min, int32 max)
{
    // std::uniform_int_distribution는 [min, max] 범위를 포함합니다.
    uniform_int_distribution<int32> dist(min, max);
    return dist(m_randomEngine); // RandomEngine을 사용하여 난수 생성
}

// 0.0f와 1.0f 사이의 부동 소수점 난수를 생성합니다.
float Random::Rand()
{
    // std::uniform_real_distribution는 [min, max) 범위를 가집니다.
    // 즉, min은 포함하고 max는 포함하지 않습니다. 0.0f는 포함, 1.0f는 포함하지 않음.
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(m_randomEngine);
}

// 지정된 범위 내의 부동 소수점 난수를 생성합니다.
float Random::Rand(float min, float max)
{
    // std::uniform_real_distribution는 [min, max) 범위를 가집니다.
    // 즉, min은 포함하고 max는 포함하지 않습니다.
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_randomEngine);
}