/* A. Smallest positive denormalized
 *    0 000..0(15) 000...0(62)1
 *    2^(1 - bias) * 2^(-62) = 2^(-61 - bias) 
 *    bias = 2 ^ 14 - 1
 *
 *
 *
 * B. Smallest positive normalized
 *    0 000...0(14)1 000..0(63)
 *    bias = 2^14 - 1
 *    2^(1-bias) * 1 = 2^(1-bias)
 *
 * C. Largest normalized
 *    0 111...1(14)0 111...1(63)
 *    bias = 2^14 - 1
 *    E = e - bias = 2^15 - 2 - 2^14 + 1 = 2^14 - 1 = bias
 *    M = 1 + 1 - 2^(-n) = 2 - 2^(-n)
 *    2^E * M = 2^bias * (2 - 2^(-63))
 */
