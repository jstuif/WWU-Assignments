/*
Joshua Stuifbergen
11/16/18
CISS247
Lab 6 Floating Point
*/

#include <stdio.h>

typedef unsigned float_bits;

/*
	can use ! ~ & ^ | + << >>
 	no global variables
	no if, do , while, for, switch
	no additional functions
	no &&, ||, -, ?:
	no casting
	no data type other than int. No arrays, stucts, unions
*/


//int float_class(float_bits f){
	
	

//}

//NaN 2147483647	     01111111111111111111111111111111
//Infinity 2139095040        01111111100000000000000000000000
// -Infinity  4286578688     11111111100000000000000000000000
//  2147483648		     10000000000000000000000000000000

//NEGATE
float_bits float_negate(float_bits f){
	printf("NEGATE\n");
	int mask = 128;
	//printf("Mask of 128: %u\n", mask);
	int tmp = mask << 24;
	//int naN = ~tmp;
	//printf("Mask shifted << 24: %u\n", tmp);
	int tmp2 = tmp ^ f;
	//printf("XOR produces: %u\n", tmp2);

	return tmp2;	
}


//Gets ASBSOLUTE value of floating point number
float_bits float_absval(float_bits f){
	printf("ABSOLUTE\n");	
	int mask = 128;
	//printf("Mask of 128: %u\n", mask);
	int tmp = mask << 24;
	//printf("Mask shifted << 24: %u\n", tmp);
	int tmp2 = tmp | f;
	//printf("OR produces: %u\n", tmp2);
	int tmp3 = tmp2 ^ tmp;
	//printf("XOR produces: %u\n", tmp3);
	return tmp3;
}

//TWICE
float_bits float_twice(float_bits f){
		
	printf("TWICE\n");
	//printf("f is: %u\n", f);   ///1061158912 is .75 from console
	int mask255 = 255; //Used for Exponent and Mantissa mask
	int mask1 = 1; //Used for sign mask
	int maskZero = 0; //To put the floating point number back together
	
	int mantisMask = mask255 << 8;
	//printf("mantis: %u\n", mantisMask);
	mantisMask |= mask255;
	//printf("mantis: %u\n", mantisMask);
	mantisMask <<= 7;
	//printf("mantis: %u\n", mantisMask);
	mantisMask |= mask255;
	//printf("mantis mask is: %u\n", mantisMask); 
	// mantis =  8388607       0 000  0000 0000 0111 1111 1111 1111 1111
	
	//int expMask = mask255 << 23;
	//printf("exp mask is: %u\n", expMask);
	// exponent =  213909504   0 111  1111 1000 0000 0000 0000 0000 0000

	int signMask = mask1 << 31;
	//printf("sign mask is: %u\n", signMask);
	//  sign = 2147483648 	  10000000000000000000000000000000
	
	int sign = f & signMask;
	//printf("Sign: %u\n", sign);
	
	int mantis = f & mantisMask;
	//printf("mantis is: %u\n", mantis);
	
	int exp = f & signMask;
	//printf("Sign: %u\n", exp);
	exp = f >> 23;
	//printf("exp shift >> 23 is: %u\n", exp);
	exp = exp + 1;	
	//printf("exp + 1: %u\n", exp);
	exp = exp << 23;
	//printf("exp shift << 23: %u\n", exp);
	
	int answer = sign | maskZero;
	answer |= exp;
	answer |= mantis;
	//printf("Outcome is: %u\n", answer);
	
	//Code prior to discovering values above 1.0 dont calculate
	/*
	int exp = f >> 23;
	printf("exp shift >> 23 is: %u\n", exp);
	exp = exp + 1;	
	printf("exp + 1: %u\n", exp);
	exp = exp << 23;

	int ans = exp | f; //EXPONENT 
	printf("exp shift << 23: %u\n", ans);
	*/

	return answer;
}

//HALF
float_bits float_half(float_bits f){
	printf("HALF\n");	
	//printf("f is: %u\n", f);   ///1061158912 is .75 from console
	int mask255 = 255; //Used for Exponent and Mantissa mask
	int mask1 = 1; //Used for sign mask
	int maskZero = 0; //To put the floating point number back together
	int negOne = -1; //To reduce the exponent by one
	
	int mantisMask = mask255 << 8;
	//printf("mantis: %u\n", mantisMask);
	mantisMask |= mask255;
	//printf("mantis: %u\n", mantisMask);
	mantisMask <<= 7;
	//printf("mantis: %u\n", mantisMask);
	mantisMask |= mask255;
	//printf("mantis mask is: %u\n", mantisMask); 
	// mantis =  8388607       0 000  0000 0000 0111 1111 1111 1111 1111
	
	//int expMask = mask255 << 23;
	//printf("exp mask is: %u\n", expMask);
	// exponent =  213909504   0 111  1111 1000 0000 0000 0000 0000 0000

	int signMask = mask1 << 31;
	//printf("sign mask is: %u\n", signMask);
	//  sign = 2147483648 	  10000000000000000000000000000000
	
	int sign = f & signMask;
	//printf("Sign: %u\n", sign);
	
	int mantis = f & mantisMask;
	//printf("mantis is: %u\n", mantis);
	
	int exp = f & signMask;
	//printf("Sign: %u\n", exp);
	exp = f >> 23;
	//printf("exp shift >> 23 is: %u\n", exp);
	exp = exp + negOne;
	//printf("exp + negOne: %u\n", exp);
	exp = exp << 23;
	//printf("exp shift << 23: %u\n", exp);
	
	int answer = sign | maskZero;
	answer |= exp;
	answer |= mantis;
	//printf("Outcome is: %u\n", answer);

	return answer;
}

//NaN 2147483647	     01111111111111111111111111111111
//Infinity 2139095040        01111111100000000000000000000000
// -Infinity  4286578688     11111111100000000000000000000000
//  2147483648		     10000000000000000000000000000000


int main (int argc, char *argv[]){
	float *f;
	float_bits fbits;
	float_bits tmpBits;	
	if (argc < 2) {
        	printf("Use: ./floatbits float_num\n");
        	return 0;
   	}
	
	sscanf(argv[1], "%f", (float *)&fbits);

	//tmpBits = float_class(fbits);
	//f = (float *)&tmpBits;
	//printf("%f\n\n", *f);
	
	tmpBits = float_negate(fbits);
	f = (float *)&tmpBits;
	printf("%f\n\n", *f);
	
	tmpBits = float_absval(fbits);
	f = (float *)&tmpBits;
	printf("%f\n\n", *f);
	
	tmpBits = float_twice(fbits);
	f = (float *)&tmpBits;
	printf("%f\n\n", *f);
	
	tmpBits = float_half(fbits);
	f = (float *)&tmpBits;
	printf("%f\n\n", *f);


}


// float *f = (float *)&fbits;
// printf("%f\n", *f);
