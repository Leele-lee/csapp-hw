#include <stdlib.h>
#include <stdio.h>
/*
Rdi x 
esi y
rdx z

1	decode2:	
2	subq	%rdx, %rsi // y -= z
3	imulq	%rsi, %rdi // x *= y
4	movq	%rsi, %rax // s = y
5	salq	$63, %rax // s << 63
6	sarq	$63, %rax // s >> 63
7	xorq	%rdi, %rax // s = s ^x
8	ret // return s
*/

long decode2(long x, long y, long z) {
  y -= z;
  x *= y;
  int s = y;
  if (s < 0) {
    return ~x;
  } else {
    return x;
  }
}

