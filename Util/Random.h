#pragma once

#include "Common.h"

#include <random>

class Random final
{
public:
    Random();
    explicit Random(uint32 seed);

    void Initialize(uint32 seed);
    int32 Rand(int32 min, int32 max);
    float Rand();
    float Rand(float min, float max);
private:
    mt19937 m_randomEngine;
};