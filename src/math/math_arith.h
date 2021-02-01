#ifndef MATH_ARITH_INCLUDED
#define MATH_ARITH_INCLUDED

extern long Max(long x, long y);
extern long Min(long x, long y);

// always  truncate  toward  the left on the number line
// (x / y) * y + x % y = x
extern long Div(long x, long y);
extern long Mod(long x, long y);

extern long Ceiling(long x, long y);
extern long Floor(long x, long y);

#endif
