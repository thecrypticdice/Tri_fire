#ifndef UTILITY_H
#define UTILITY_H
#include <cmath>
# include <math.h>
#include "raylib.h"
#include "rlgl.h"
#include <stddef.h>     // Required for: NULL
#include <math.h>       // Required for: sinf()

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
#define LETTER_BOUNDRY_SIZE     0.25f
#define TEXT_MAX_LAYERS         32
#define LETTER_BOUNDRY_COLOR    VIOLET

bool SHOW_LETTER_BOUNDRY = false;
bool SHOW_TEXT_BOUNDRY = false;

//--------------------------------------------------------------------------------------
// Types and Structures Definition
//--------------------------------------------------------------------------------------
// Configuration structure for waving the text
typedef struct WaveTextConfig {
    Vector3 waveRange;
    Vector3 waveSpeed;
    Vector3 waveOffset;
} WaveTextConfig;

int rand_range(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}
float dist_v2(float a_x, float a_y, float b_x, float b_y)
{
    return sqrt(pow(b_x-a_x,2)+pow(b_y-a_y,2));
}
const char* bool_to_string(bool b) {
    return b ? "true" : "false";
}

#endif
