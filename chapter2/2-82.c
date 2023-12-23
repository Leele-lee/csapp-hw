/*
 * A. false, when x = INT_MIN
 * B. ((x + y) << 4) + y - x == 17 * y + 15 * x
 *     True. x << 4 - x + y << 4 + y = 16 * x - x + 16 * y + y = 15 * x + 17 * y
 * C. ~x + ~y + 1 == ~(x + y)
 *    True. ~x + 1 + ~y + 1 - 1 = -x + -y - 1
 *          ~(x + y) = ~(x + y) + 1 - 1 = -(x + y) - 1 = -x -y -1
 * D. (ux - uy) == -(unsigned)(y - x)
 *    True. uy - ux == (unsigned)(y - x)
 * E. ((x >> 2) << 2) <= x
 *    True. x >> 2 => x/4(lower bracket) << 2 <= x/4 * 4 <= x
 */
