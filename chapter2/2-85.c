/* A. 7.0
 *   E\M\f\V bit representation
 *   V = 2^E * M
 *   0111
 *   f = 0b0.11
 *   M = 0b1.11
 *   E = 2 = e - bias = e - 2^(k-1) + 1
 *   e = 2^(k-1) + 1
 *   V = 7.0
 *   bits representation
 *   0 100000001 110...
 * B.The largest odd integer that can be represented exactly
 *   interge convert to floating point
 *   the largest odd number must have n+1 1s
 *   E = n, f = 0b0.111..., M = 0b1.111..., V = 2^(n+1) - 1
 *   E = e - bias, e = bias + n = 2^(k-1) - 1 + n
 *   bit representation: 0 bias+n 111...
 * C.The reciprocal of the smallest positive normalized value
 *   E = bias - e = bias - 1 = e - bias, e = 2bias - 1 = 2^k - 1 - 2 = 0b1111...01
 *   f = 0b0.000..., M = 0b1.000..., V = 2^(bias - 1)
 *   bit representation: 0 111...10  0000...
 * 
 */
