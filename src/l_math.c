#include "l_math.h"

i32 int_min(i32 a, i32 b)
{
    return (a < b) ? a : b;
}

i32 int_max(i32 a, i32 b)
{
    return (a > b) ? a : b;
}

i32 int_abs(i32 n)
{
    return (n > 0) ? n : -n;
}

f32 float_min(f32 a, f32 b)
{
    return (a < b) ? a : b;
}

f32 float_max(f32 a, f32 b)
{
    return (a > b) ? a : b;
}

f32 flaot_abs(f32 n)
{
    return (n > 0) ? n : -n;
}
