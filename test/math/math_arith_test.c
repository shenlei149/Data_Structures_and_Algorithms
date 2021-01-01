#include <criterion/criterion.h>

#include "../../src/math/math_arith.h"

TestSuite(math_arith);

Test(math_arith, max_min)
{
    cr_assert_eq(100, MathArith_Max(20, 100));
    cr_assert_eq(20, MathArith_Max(20, -100));

    cr_assert_eq(20, MathArith_Min(20, 100));
    cr_assert_eq(-100, MathArith_Min(20, -100));
}

Test(math_arith, div_mod)
{
    cr_assert_eq(2, MathArith_Div(13, 5));
    cr_assert_eq(-3, MathArith_Div(-13, 5));
    cr_assert_eq(-3, MathArith_Div(13, -5));
    cr_assert_eq(2, MathArith_Div(-13, -5));
    cr_assert_eq(3, MathArith_Div(15, 5));
    cr_assert_eq(-3, MathArith_Div(-15, 5));
    cr_assert_eq(-3, MathArith_Div(15, -5));
    cr_assert_eq(3, MathArith_Div(-15, -5));

    cr_assert_eq(3, MathArith_Mod(13, 5));
    cr_assert_eq(2, MathArith_Mod(-13, 5));
    cr_assert_eq(-2, MathArith_Mod(13, -5));
    cr_assert_eq(-3, MathArith_Mod(-13, -5));
    cr_assert_eq(0, MathArith_Mod(15, 5));
    cr_assert_eq(0, MathArith_Mod(-15, 5));
    cr_assert_eq(0, MathArith_Mod(15, -5));
    cr_assert_eq(0, MathArith_Mod(-15, -5));
}

Test(math_arith, ceiling_floor)
{
    cr_assert_eq(3, MathArith_Ceiling(13, 5));
    cr_assert_eq(-2, MathArith_Ceiling(-13, 5));
    cr_assert_eq(-2, MathArith_Ceiling(13, -5));
    cr_assert_eq(3, MathArith_Ceiling(-13, -5));
    cr_assert_eq(3, MathArith_Ceiling(15, 5));
    cr_assert_eq(-3, MathArith_Ceiling(-15, 5));
    cr_assert_eq(-3, MathArith_Ceiling(15, -5));
    cr_assert_eq(3, MathArith_Ceiling(-15, -5));

    cr_assert_eq(2, MathArith_Floor(13, 5));
    cr_assert_eq(-3, MathArith_Floor(-13, 5));
    cr_assert_eq(-3, MathArith_Floor(13, -5));
    cr_assert_eq(2, MathArith_Floor(-13, -5));
    cr_assert_eq(3, MathArith_Floor(15, 5));
    cr_assert_eq(-3, MathArith_Floor(-15, 5));
    cr_assert_eq(-3, MathArith_Floor(15, -5));
    cr_assert_eq(3, MathArith_Floor(-15, -5));
}
