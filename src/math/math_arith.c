#include "math_arith.h"

long MathArith_Max(long x, long y)
{
    return x > y ? x : y;
}

long MathArith_Min(long x, long y)
{
    return x > y ? y : x;
}

long MathArith_Div(long x, long y)
{
    if (-13 / 5 == -2 &&      // truncates towards 0
        (x < 0) != (y < 0) && // different signs
        x % y != 0)
    {
        return x / y - 1;
    }
    else
    {
        return x / y;
    }
}

// (x / y) * y + x % y = x
long MathArith_Mod(long x, long y)
{
    if (-13 / 5 == -2 &&      // truncates towards 0
        (x < 0) != (y < 0) && // different signs
        x % y != 0)
    {
        return x % y + y;
    }
    else
    {
        return x % y;
    }
}

long MathArith_Ceiling(long x, long y)
{
    return MathArith_Div(x, y) + (x % y != 0);
}

long MathArith_Floor(long x, long y)
{
    return MathArith_Div(x, y);
}
