#ifndef _MACRO_H
#define _MACRO_H

#include <cmath>
#include <algorithm>
#include "vector.h"

#define SETUP_FPS()             \
float fixed_delta = 0.16f;      \
float from_last_fixed = 0.0f;   \
int frame_since_last_fixed = 0

#define UPDATE_FPS() do {                                               \
t.update();                                                             \
from_last_fixed += t.deltaTime();                                       \
++frame_since_last_fixed;                                               \
if (from_last_fixed > fixed_delta) {                                    \
    int fps = std::round(frame_since_last_fixed / from_last_fixed);     \
    std::string title = "Bricks @ LuGL FPS: " + std::to_string(fps);    \
    setWindowTitle(window, title.c_str());                              \
    from_last_fixed = 0.0f;                                             \
    frame_since_last_fixed = 0;                                         \
}                                                                       \
} while(0) 

// Generate random float from 0 to 1.
#define rnd() (static_cast<float>(rand())/static_cast<float>(RAND_MAX))

// Convert float value in scene to integer value in image space.
inline int ftoi(float x) {
    // Difference of (int)std::floor(x) and static_cast<int>(x):
    // - (int)std::floor(x) cast x toward -INFINITY
    // - static_cast<int>(x) cast x toward 0
    // Although we ignore negative value in image space, -0.5 will still be cast to 0
    // which is not correct theoretically.
    return std::floor(x);
}

// Convert integer value in image space to float value in scene.
inline float itof(int x) {
    return x + 0.5f;
}

template<typename T, typename U, typename V>
inline T clamp(T x, U min, V max) {
    x = x < min ? min : x;
    x = x > max ? max : x;
    return x;
}

constexpr float PI              = 3.14159265;
constexpr float PI_div_two      = PI / 2;
constexpr float PI_div_three    = PI / 3;
constexpr float PI_div_four     = PI / 4;
constexpr float PI_mul_two      = PI * 2;

#endif
