/*A. (float) × == (float) dx
 * True, (float)x = (float)((double)x)
 * Converting to float could cause rounding, but both x and dx will be rounded in
 * the same way
 *
 *B. dx - dy == (double) (x-y)
 * false, x = 1e9+1, y = 1e9, (1e9+1) - 1e9 = 0.0, (double)(1e9+1)-1e9 = 1.0
 * when y = INT_MIN, ans x > 0, x - y cause oveflow, and cause unsuspect result,
 * dx - dy can result in overflow, set to special value instead like interge overflow
 *
 *C. (dx + dy) + dz == dx + (dy + dz)
 * True, Since ach value ranges between TMin ans TMax, their sum can be represented exactly
 *
 *D. (dx * dy) * dz == dx * (dy * dz)
 * False, let dx = TMax, dy = TMax - 1, dz = TMax - 2
 *
 *E. dx/dx == dy/dy
 * Fasle, when x = 0 and y != 0
 *
 */
