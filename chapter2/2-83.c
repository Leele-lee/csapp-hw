/* A. x = 0.yyyyyy...
 * x << k = y.yyyyyy... = Y + 0.yyyyyyy... = Y + x
 * x << k = Y + x => x << k - x = Y => x * 2^k - x = Y => x * (2^k - 1) = Y
 * x = Y / (2^k - 1)
 *
 * B. a.101 x = 5 / (2 ^ 3 - 1) = 5/7
 * b. 0110 = 6/(2^4 - 1) = = 6/15 = 2/5 
 * c. 010011 = 19/(2^6 - 1) = 19/63
 */