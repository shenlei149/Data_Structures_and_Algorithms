#ifndef MATH_ARITH_INCLUDED
#define MATH_ARITH_INCLUDED

extern long Arith_Max(long x, long y);
extern long Arith_Min(long x, long y);

// always  truncate  toward  the left on the number line
// (x / y) * y + x % y = x
extern long Arith_Div(long x, long y);
extern long Arith_Mod(long x, long y);

extern long Arith_Ceiling(long x, long y);
extern long Arith_Floor(long x, long y);

#endif
