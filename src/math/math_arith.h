#ifndef MATH_ARITH_INCLUDED
#define MATH_ARITH_INCLUDED

extern long MathArith_Max(long x, long y);
extern long MathArith_Min(long x, long y);

// always  truncate  toward  the left on the number line
// (x / y) * y + x % y = x
extern long MathArith_Div(long x, long y);
extern long MathArith_Mod(long x, long y);

extern long MathArith_Ceiling(long x, long y);
extern long MathArith_Floor(long x, long y);

#endif
