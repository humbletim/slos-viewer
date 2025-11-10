#include "isolated_noise.cpp.inl"
#include <iostream>
#include <iomanip>
#include <vector>

int main()
{
    // Ensure we trigger init() by making one call first
    F32 warmup_vec[2] = { 0.0f, 0.0f };
    noise2(warmup_vec);

    // Test vectors similar to terrain generation grid
    std::vector<std::pair<float, float>> test_points = {
        { 10.5f, 20.1f },
        { 100.1f, 5.5f },
        { 255.9f, 255.9f },
        { 0.0f, 0.0f },
        { 128.0f, 128.0f },
    };

    std::cout << std::fixed << std::setprecision(6);
    for (const auto& p : test_points)
    {
        F32 vec[2] = { p.first, p.second };
        float n = noise2(vec);
        std::cout << "Pos(" << p.first << ", " << p.second << ") -> " << n << std::endl;
    }

    // Dump standard internal state for deep verification
    // (Accessing globals from noise.h)
    std::cout << "\n--- Internal State Check ---" << std::endl;
    std::cout << "p[0]: " << p[0] << std::endl;
    std::cout << "g1[0]: " << g1[0] << std::endl;
    std::cout << "g2[0][0]: " << g2[0][0] << std::endl;

    return 0;
}
