/*
Joshua Stuifbergen
12/5/18
CISS247
Lab 8 Exercise 3
*/

#include <stdio.h>

int main (){
		
	int arr[14];
	
	//int arr[13] = {0, 0, 0, 0, 0, 0, 1, 3, 2, 0, 12, 19, 23, 0};
	
	arr[12] = 23; //a
	arr[11] = 19; //b
	arr[10] = 12; //c
	arr[8] = 2;   //d
	arr[7] = 3;   //e
	arr[6] = 1;   //f
	arr[13] = 0;  //g
	
	arr[8] = arr[12] *  arr[8]; 
	arr[13] = arr[8];
	
	
	arr[7] = arr[11] * arr[7];
	arr[13] = arr[7];
	
	arr[6] = arr[10] * arr[6];
	arr[13] = arr[6];
	
	/*
	int a, b, c, d, e, f, g;
	
	a = 23;
	b = 19;
	c = 12;
	d = 2;
	e = 3;
	f = 1;
	g = 0;
	

	d = d * a;
	g += d;
	
	e = e * b;
	g += e;

	f = f * c;
	g += f;
	*/
	
}

/*
 400546:	55                   	push   %rbp
  400547:	48 89 e5             	mov    %rsp,%rbp
  40054a:	48 83 ec 40          	sub    $0x40,%rsp
  40054e:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax		rax = mem location 0x28    
  400555:	00 00 
  400557:	48 89 45 f8          	mov    %rax,-0x8(%rbp)		-0x8 = mem 0x28
  40055b:	31 c0                	xor    %eax,%eax		makes eax = 0
  40055d:	c7 45 d0 17 00 00 00 	movl   $0x17,-0x30(%rbp)	a = 23     48
  400564:	c7 45 d4 13 00 00 00 	movl   $0x13,-0x2c(%rbp)	b = 19	    44
  40056b:	c7 45 d8 0c 00 00 00 	movl   $0xc,-0x28(%rbp)		c = 12      40
  400572:	c7 45 e0 02 00 00 00 	movl   $0x2,-0x20(%rbp)		d = 2        32
  400579:	c7 45 e4 03 00 00 00 	movl   $0x3,-0x1c(%rbp)		e = 3        28
  400580:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%rbp)		f = 1        24
  400587:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%rbp)		g = 0        52
  40058e:	8b 55 d0             	mov    -0x30(%rbp),%edx		edx = a(23)
  400591:	8b 45 e0             	mov    -0x20(%rbp),%eax		eax = d(2)
  400594:	0f af c2             	imul   %edx,%eax		eax(d) = 2 * 23 = 46
  400597:	01 45 cc             	add    %eax,-0x34(%rbp)		g(0) = 0 + 46(d) = 46
  40059a:	8b 55 d4             	mov    -0x2c(%rbp),%edx		edx = b(19)
  40059d:	8b 45 e4             	mov    -0x1c(%rbp),%eax		eax = e(3)
  4005a0:	0f af c2             	imul   %edx,%eax		eax = 3 * 19 = 57
  4005a3:	01 45 cc             	add    %eax,-0x34(%rbp)		g(0) = 0 + eax(57) = 57
  4005a6:	8b 55 d8             	mov    -0x28(%rbp),%edx		edx = c(12)
  4005a9:	8b 45 e8             	mov    -0x18(%rbp),%eax		eax = f(1)
  4005ac:	0f af c2             	imul   %edx,%eax		eax = 12 * 1 = 12
  4005af:	01 45 cc             	add    %eax,-0x34(%rbp)		g(0) = 0 + eax(12) = 12
  4005b2:	b8 00 00 00 00       	mov    $0x0,%eax		eax = 0
  4005b7:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx		rcx = mem 0x28  (0x59ebe7179c5d8600   64795265774)
  4005bb:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx		makes rcx = 0
  4005c2:	00 00             
  4005c4:	74 05                	je     4005cb <main+0x85>	jump over 
  4005c6:	e8 55 fe ff ff       	callq  400420 <__stack_chk_fail@plt>
  4005cb:	c9                   	leaveq 
  4005cc:	c3                   	retq   
  4005cd:	0f 1f 00             	nopl   (%rax)
*/
