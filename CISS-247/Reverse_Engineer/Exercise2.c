/*
Joshua Stuifbergen
12/5/18
CISS247
Lab 8 Exercise 2
*/

#include <stdio.h>

int main (){

	int x, y, z, w;
	
	x = 19; 
	y = 34; 
	z = 12;
	
	x = x + x + x;	// x = 38 -> x = 57

	x += y <<= 2; // y = 136 -> x = 193

	z += z; // z = 24
	z = x + z; // z = 193 + 24 = 217
	
	w = z;
	
}

/*
00000000004004d6 <main>:
  4004d6:	55                   	push   %rbp
  4004d7:	48 89 e5             	mov    %rsp,%rbp
  4004da:	c7 45 f0 13 00 00 00 	movl   $0x13,-0x10(%rbp)   x = 19
  4004e1:	c7 45 f4 22 00 00 00 	movl   $0x22,-0xc(%rbp)    y = 34
  4004e8:	c7 45 f8 0c 00 00 00 	movl   $0xc,-0x8(%rbp)	   z = 12
  4004ef:	8b 55 f0             	mov    -0x10(%rbp),%edx    edx = x
  4004f2:	89 d0                	mov    %edx,%eax		eax = x
  4004f4:	01 c0                	add    %eax,%eax		x = x + x (2x)
  4004f6:	01 c2                	add    %eax,%edx		x = x + 2x
  4004f8:	8b 45 f4             	mov    -0xc(%rbp),%eax		eax = y
  4004fb:	c1 e0 02             	shl    $0x2,%eax		y = y<<2 shift left 2
  4004fe:	01 c2                	add    %eax,%edx		x = x + y;
  400500:	8b 45 f8             	mov    -0x8(%rbp),%eax		eax = z
  400503:	01 c0                	add    %eax,%eax		z = z + z;
  400505:	01 d0                	add    %edx,%eax		z = x + z;
  400507:	89 45 fc             	mov    %eax,-0x4(%rbp)		int w = z;
  40050a:	8b 45 fc             	mov    -0x4(%rbp),%eax
  40050d:	5d                   	pop    %rbp
  40050e:	c3                   	retq   
  40050f:	90                   	nop
*/
