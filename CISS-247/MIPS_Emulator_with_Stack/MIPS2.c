/*
Joshua Stuifbergen
10/14/18
CISS 247
Lab5 Assignment
MIPS Emulator with Stack
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Max length of each row from MIPS file
#define MAXLINE 100

//if bne function is used, then it signals that pc (program counter) has changed
int pcBranch;
//int MAXSTACK = 750; //750 dec is bb8 hex. Stack can't pass hex 3e8 (250 dec)
//int top = -1;

//int PC = 512;

//Memory Struct with MIPS fields
//6 since $zero is the longest
struct memStruct{
	char addr[6];
	char doI[6];  //data or instruction
	char arg1[6];
	char arg2[6];
	char arg3[6];
}memArr[1000];   

struct tempMipStruct{
	char addr[6];
	char doI[6];  //data or instruction
	char arg1[6];
	char arg2[6];
	char arg3[6];
}tempMemArr[1000];  //had it at 2, but compile left an 'o' in arg2 in register 0...idk why

//Register Struct
struct reg{
	char *regi;
	int data;
}regArr[33];

//Registers hold the string identification and data
char mipsReg(){
	
	regArr[0].regi = "$zero";
        regArr[0].data = 0;
        regArr[1].regi = "$at";
        regArr[1].data = 0;
        regArr[2].regi = "$v0";
        regArr[2].data = 0;
        regArr[3].regi = "$v1";
        regArr[3].data = 0;
        regArr[4].regi = "$a0";
        regArr[4].data = 0;
        regArr[5].regi = "$a1";
        regArr[5].data = 0;
        regArr[6].regi = "$a2";
        regArr[6].data = 0;
        regArr[7].regi = "$a3";
        regArr[7].data = 0;
        regArr[8].regi = "$t0";
        regArr[8].data = 0;
        regArr[9].regi = "$t1";
        regArr[9].data = 0;	
	regArr[10].regi = "$t2";
        regArr[10].data = 0;
        regArr[11].regi = "$t3";
        regArr[11].data = 0;
        regArr[12].regi = "$t4";
        regArr[12].data = 0;
        regArr[13].regi = "$t5";
        regArr[13].data = 0;
        regArr[14].regi = "$t6";
        regArr[14].data = 0;
        regArr[15].regi = "$t7";
        regArr[15].data = 0;
        regArr[16].regi = "$s0";
        regArr[16].data = 0;
        regArr[17].regi = "$s1";
        regArr[17].data = 0;
        regArr[18].regi = "$s2";
        regArr[18].data = 0;
        regArr[19].regi = "$s3";
        regArr[19].data = 0;
	regArr[20].regi = "$s4";
        regArr[20].data = 0;
        regArr[21].regi = "$s5";
        regArr[21].data = 0;
        regArr[22].regi = "$s6";
        regArr[22].data = 0;
        regArr[23].regi = "$s7";
        regArr[23].data = 0;
        regArr[24].regi = "$t8";
        regArr[24].data = 0;
        regArr[25].regi = "$t9";
        regArr[25].data = 0;
        regArr[26].regi = "$k0";
        regArr[26].data = 0;
        regArr[27].regi = "$k1";
        regArr[27].data = 0;
        regArr[28].regi = "$gp";
        regArr[28].data = 0;
        regArr[29].regi = "$sp";
        regArr[29].data = 0;		//250 = FA   1000 = 3E8
	regArr[30].regi = "$fp";
        regArr[30].data = 0;
        regArr[31].regi = "$ra";
        regArr[31].data = 0;


	//printf("regArr[0].regi = %s\n", regArr[0].regi);
	//printf("regArr[0].data = %d\n", regArr[0].data);
	
	return 0;
}


//match string values of mem to reg, return pointer &Register of data value
int *memToReg(char *arg, struct reg regArr[]){
	if((strcmp(arg, "$zero")) == 0){		
		return &regArr[0].data;
	} else if((strcmp(arg, "$at")) == 0){           
                return &regArr[1].data;
        } else if((strcmp(arg, "$v0")) == 0){ 
                return &regArr[2].data;
        } else if((strcmp(arg, "$v1")) == 0){ 
                 return &regArr[3].data;
        } else if((strcmp(arg, "$a0")) == 0){ 
                 return &regArr[4].data;
        } else if((strcmp(arg, "$a1")) == 0){ 
                 return &regArr[5].data;
        } else if((strcmp(arg, "$a2")) == 0){ 
                 return &regArr[6].data;
        } else if((strcmp(arg, "$a3")) == 0){
                 return &regArr[7].data;
        } else if((strcmp(arg, "$t0")) == 0){        
                  return &regArr[8].data;
        } else if((strcmp(arg, "$t1")) == 0){        
                 return &regArr[9].data;
        } else if((strcmp(arg, "$t2")) == 0){           
                return &regArr[10].data;
        } else if((strcmp(arg, "$t3")) == 0){ 
                return &regArr[11].data;
        } else if((strcmp(arg, "$t4")) == 0){ 
                 return &regArr[12].data;
        } else if((strcmp(arg, "$t5")) == 0){ 
                 return &regArr[13].data;
        } else if((strcmp(arg, "$t6")) == 0){ 
                 return &regArr[14].data;
        } else if((strcmp(arg, "$t7")) == 0){ 
                 return &regArr[15].data;
        } else if((strcmp(arg, "$s0")) == 0){
                 return &regArr[16].data;
        } else if((strcmp(arg, "$s1")) == 0){        
                  return &regArr[17].data;
        } else if((strcmp(arg, "$s2")) == 0){        
                 return &regArr[18].data;
        } else if((strcmp(arg, "$s3")) == 0){           
                return &regArr[19].data;
        } else if((strcmp(arg, "$s4")) == 0){ 
                return &regArr[20].data;
        } else if((strcmp(arg, "$s5")) == 0){ 
                 return &regArr[21].data;
        } else if((strcmp(arg, "$s6")) == 0){ 
                 return &regArr[22].data;
        } else if((strcmp(arg, "$s7")) == 0){ 
                 return &regArr[23].data;
        } else if((strcmp(arg, "$t8")) == 0){ 
                 return &regArr[24].data;
        } else if((strcmp(arg, "$t9")) == 0){
                 return &regArr[25].data;
        } else if((strcmp(arg, "$k0")) == 0){        
                  return &regArr[26].data;
        } else if((strcmp(arg, "$k1")) == 0){        
                 return &regArr[27].data;
        } else if((strcmp(arg, "$gp")) == 0){           
                return &regArr[28].data;
        } else if((strcmp(arg, "$sp")) == 0){  
                return &regArr[29].data;
        } else if((strcmp(arg, "$fp")) == 0){ 
                 return &regArr[30].data;
        } else if((strcmp(arg, "$ra")) == 0){ 
                 return &regArr[31].data;
        } else {
		printf("could not match mem string %s to reg\n", arg);
	}	
	return 0;
}


/*String compares the string of the memory struct address and the
 string derived from the int value of an arguement sent to memToReg.
 Returns the int value of the data field corresponding to the address*/
int lwAddr(char *arg, struct memStruct memArr[]){
	int b;
	for(b = 0; b < 1000; b++){	
		if((strcmp(arg, memArr[b].addr)) == 0){			
			return atoi(memArr[b].doI);
		} 
	}	
	return 0;
}


//ADDI Function
void addi(int *arg1, int *arg2, int arg3){
	*arg1 = *arg2 + arg3;
}

//ADDIU Function
void addiu(int *arg1, int *arg2, int arg3){
	*arg1 = *arg2 + arg3;
}

//ADD Function
void add(int *arg1, int *arg2, int *arg3){
	*arg1 = *arg2 + *arg3;
}

//LI Function
void li(int *arg1, int arg2){
	*arg1 = arg2;
}

//Load Word Function
void lw(int *arg1, int arg2){
	*arg1 = arg2;
}

//Store Word Function
void sw(int *arg1, int *arg2){
	*arg2 = *arg1;
}

//SUB Function
void sub(int *arg1, int *arg2, int *arg3){
            *arg1 = *arg2 - *arg3;
}

//SUBU Function
void subu(int*arg1, int *arg2, int arg3){
		*arg1 = *arg2 - arg3;
			
}

//BNE Function
int bne(int *arg1, int *arg2, int arg3, int z, int *pc){
	
	if(*arg1 != *arg2){
		pcBranch = 1;	
		int v;
		int tmpZ = z;
		//int four = 4;
		for(v = 1; v < 1000; v++){	
			if(strcmp(memArr[z].arg3, memArr[v].addr) == 0){				
				z = (v - z);
				z += tmpZ; 
				return z;
			 }
		 }	
	} 		
	return 0;
}

//BGTZ Function
int bgtz(int *arg1, int arg2, int z, int *pc){

	if(*arg1 > 0){
		pcBranch = 1;	
		int v;
		int tmpZ = z;
		//int four = 4;
		for(v = 1; v < 1000; v++){	
			if(strcmp(memArr[z].arg2, memArr[v].addr) == 0){				
				z = (v - z);
				z += tmpZ; 
				return z;
			 }
		 }	
	
	} 
		
	return 0;
}


//JUMP Function
int jump(int arg1, int z, int *pc){

		int v;
		int tmpZ = z;
		//int four = 4;
		for(v = 1; v < 1000; v++){	
			if(strcmp(memArr[z].arg1, memArr[v].addr) == 0){				
				z = (v - z);
				z += tmpZ; 
				return z;
			 }
		 }	
	return 0;		
}


/*void stackCounter(struct reg regArr[], arg){
	int tmpPC = 0;
	sprintf(tmpPC, "%d", *arg2P);
}*/

//prints the regArr[#].data values of the registry array after 
//every instruction completion
void printFunct(struct reg regArr[]){
	
	//printf("Program Counter: [%d]\n", PC);
        printf("Register: $zero = [%d] \n", regArr[0].data);
      	printf("Register: $at = [%d] \n", regArr[1].data);
        printf("Register: $v0 = [%d] \n", regArr[2].data);
        printf("Register: $v1 = [%d] \n", regArr[3].data);
        printf("Register: $a0 = [%d] \n", regArr[4].data);
        printf("Register: $a1 = [%d] \n", regArr[5].data);
        printf("Register: $a2 = [%d] \n", regArr[6].data);
        printf("Register: $a3 = [%d] \n", regArr[7].data);
        printf("Register: $t0 = [%d] \n", regArr[8].data);
        printf("Register: $t1 = [%d] \n", regArr[9].data);
	printf("Register: $t2 = [%d] \n", regArr[10].data);
        printf("Register: $t3 = [%d] \n", regArr[11].data);
        printf("Register: $t4 = [%d] \n", regArr[12].data);
        printf("Register: $t5 = [%d] \n", regArr[13].data);
        printf("Register: $t6 = [%d] \n", regArr[14].data);
        printf("Register: $t7 = [%d] \n", regArr[15].data);
        printf("Register: $s0 = [%d] \n", regArr[16].data);
        printf("Register: $s1 = [%d] \n", regArr[17].data);
        printf("Register: $s2 = [%d] \n", regArr[18].data);
	printf("Register: $s3 = [%d] \n", regArr[19].data);
        printf("Register: $s4 = [%d] \n", regArr[20].data);
        printf("Register: $s5 = [%d] \n", regArr[21].data);
        printf("Register: $s6 = [%d] \n", regArr[22].data);
        printf("Register: $s7 = [%d] \n", regArr[23].data);
        printf("Register: $t8 = [%d] \n", regArr[24].data);
        printf("Register: $t9 = [%d] \n", regArr[25].data);
        printf("Register: $k0 = [%d] \n", regArr[26].data);
        printf("Register: $k1 = [%d] \n", regArr[27].data);
	printf("Register: $gp = [%d] \n", regArr[28].data);
        printf("Register: $sp = [%d] \n", regArr[29].data);
        printf("Register: $fp = [%d] \n", regArr[30].data);
        printf("Register: $ra = [%d] \n\n", regArr[31].data);
   	
}


int main (int argc, char *argv[]){
    	char *compare;
	int PC = 512;
	char line[MAXLINE];  
   	const char *delim = " ,\n";
	int value = 0;
	//struct mipStruct memArr[7];
        //FILE *fp;
        //fp = fopen("MYPS_FYLE", "r");
	
	/*int f = 4000; 	
	char *SP;
	SP = memArr[f].addr;
	printf("sp is: %s", SP);*/

	int p = 0;
	for (int y = 0; y <= 1000; y++){
				
		//printf("y as an int : %d\n", y);		
		sprintf(memArr[y].addr, "%x", value);
		//printf("y as an char : %d\n\n", y);
		value += 4;
		//printf("value as an int : %x\n", value);
	} 
		
	//strtok will put the token prior to the delimiter into
	//the memory struct fields using strncpy
	//memset(tempMemArr, 0, sizeof(tempMemArr));
	int i = 0;
	while(fgets(line, MAXLINE, stdin)){
		//printf("Temp instruction i is: %d\n", i);
		char *nextField;
		compare = tempMemArr[i].addr;
               	nextField = strtok(line, delim);
		strncpy(tempMemArr[i].addr, nextField, strlen(nextField));
		//printf("The address for temp: %s\n", tempMemArr[i].addr);
                nextField = strtok(NULL, delim);
		strncpy(tempMemArr[i].doI, nextField, strlen(nextField));
		//printf("The data for temp: %s\n", tempMemArr[i].doI);
               	nextField = strtok(NULL, delim);
   		strncpy(tempMemArr[i].arg1, nextField, strlen(nextField));
		//printf("arg1 for temp: %s\n", tempMemArr[i].arg1);
                nextField = strtok(NULL, delim);
   		strncpy(tempMemArr[i].arg2, nextField, strlen(nextField));
		//printf("arg2 for temp: %s\n", tempMemArr[i].arg2);
               	nextField = strtok(NULL, delim);
  		strncpy(tempMemArr[i].arg3, nextField, strlen(nextField));
		//printf("arg3 for temp: %s\n", tempMemArr[i].arg3);
		
		//printf("The compare: %s\n\n", compare);
		for (p = 0; p <= 1000; p++){
			//printf("This is p: %d\n", p);
			if(strcmp(compare, memArr[p].addr) == 0){
				//printf("in the if....\n");			
				strcpy(memArr[p].addr, tempMemArr[i].addr);
				//printf("Actual memory %s\n", memArr[p].addr);
           			strcpy(memArr[p].doI, tempMemArr[i].doI);
				//printf("Actual data %s\n", memArr[p].doI);
   				strcpy(memArr[p].arg1, tempMemArr[i].arg1);
				//printf("Actual memory arg1 %s\n", memArr[p].arg1);
   				strcpy(memArr[p].arg2, tempMemArr[i].arg2);
				//printf("Actual memory arg2 %s\n", memArr[p].arg2);
  				strcpy(memArr[p].arg3, tempMemArr[i].arg3);
				//printf("Actual memory arg3 %s\n", memArr[p].arg3);

				
				//memset is not necessary, but I'll use it for now
				memset(tempMemArr[0].addr, 0, 6);
   				memset(tempMemArr[0].doI, 0, 6);
				memset(tempMemArr[0].arg1, 0, 6);
				memset(tempMemArr[0].arg2, 0, 6);
				memset(tempMemArr[0].arg3, 0, 6);
				
				//printf("After resetting: %s\n\n", tempMemArr[0].doI);
			}	
		}
		i++;	     
	}
		
	
	//Prints the Memory Array
	for(int q = 0; q <= 1000; q++){
		if (memArr[q].doI != NULL){
		printf("            [addr] [data]   [arg1]  [arg2]    [arg3]\n");
		printf("Memory[%i] = %3s   %4s   %5s    %5s    %5s\n\n",
			 q, memArr[q].addr, memArr[q].doI, memArr[q].arg1, memArr[q].arg2,
				memArr[q].arg3);
		}
	
	} 
	
	//sets terminator to "STOP", placed in last struct +1 
	//strncpy(memArr[i].addr, "STOP", 4);	
	//printf("terminator at memArr[%d].addr: [%s]\n", i, memArr[i].addr);
	//printf("      [%p]\n\n", (void*) &memArr[i].addr);			


 	int j = 0;
	//int 512 = 200 hex, increase int by 4 to match hex
	//int PC = 512;
	printf("BEFORE\n");
	printf("Program Counter BEFORE: [%x]\n\n", PC);	

	//while .addr is not "STOP", continue
	
	while(strcmp(memArr[j].addr, "3e8")){	

		int *arg1P; int *arg2P; int *arg3P;
		//unsigned uarg1P; unsigned uarg2P; unsigned uarg3P;
		int *arg1Data; int *arg2Data; int *arg3Data;
		int arg1V; int arg2V; int arg3V;
		int tmp;
		char tmpA[6];			
		
		//ADDI function
		if(strcmp(memArr[j].doI, "addi") == 0){
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
				j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
				memArr[j].arg3);	
			arg1P = memToReg(memArr[j].arg1, regArr);
			arg2P = memToReg(memArr[j].arg2, regArr);
			arg3V = atoi(memArr[j].arg3);	
									
			addi(arg1P, arg2P, arg3V);	
			
		        printf("Program Counter: [%x]\n", PC);
			
			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg2, *arg2Data);
			//printf("Memory: %s = [%d]\n\n", memArr[j].addr, *arg2Data);

			//printFunct(regArr);
			j++;
			PC += 4;

		//ADDIU Function
		} else if(strcmp(memArr[j].doI, "addiu") == 0){
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
				j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
				memArr[j].arg3);	
			arg1P = memToReg(memArr[j].arg1, regArr);
			arg2P = memToReg(memArr[j].arg2, regArr);
			arg3V = atoi(memArr[j].arg3);	
									
			addiu(arg1P, arg2P, arg3V);	
			
		        printf("Program Counter: [%x]\n", PC);
			
			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg2, *arg2Data);

			//printFunct(regArr);
			j++;
			PC += 4;		
	
	
		//ADD Function
		} else if(strcmp(memArr[j].doI, "add") == 0) {
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                memArr[j].arg3);
			
			arg1P = memToReg(memArr[j].arg1, regArr);
                        arg2P = memToReg(memArr[j].arg2, regArr);
			arg3P = memToReg(memArr[j].arg3, regArr);	
			
			add(arg1P, arg2P, arg3P);			
			
			printf("Program Counter: [%x]\n", PC);

			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			arg3Data = memToReg(memArr[j].arg3, regArr);
			
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n", memArr[j].arg2, *arg2Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg3, *arg3Data);			
			
			//printFunct(regArr);
			j++;
			PC += 4;


		//LI Function
		} else if(strcmp(memArr[j].doI, "li") == 0) {
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                memArr[j].arg3);
			
			arg1P = memToReg(memArr[j].arg1, regArr);
                        arg2V = atoi(memArr[j].arg2);	
			
			li(arg1P, arg2V);			
			
			printf("Program Counter: [%x]\n", PC);

			arg1Data = memToReg(memArr[j].arg1, regArr);
			printf("Register: %s = [%d]\n\n", memArr[j].arg1, *arg1Data);			
			
			//printFunct(regArr);
			j++;
			PC += 4;


		//LW Function
		} else if(strcmp(memArr[j].doI, "lw") == 0){
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                memArr[j].arg3);

				//printf("tmpA before assignment = %s\n", tmpA);
			arg1P = memToReg(memArr[j].arg1, regArr);
				//printf("arg1P = %d\n", *arg1P);
                        arg2P = memToReg(memArr[j].arg2, regArr);
				//printf("arg2P = %d\n", *arg2P);	
			sprintf(tmpA, "%d", *arg2P);
				//printf("tmpA = %s\n", tmpA);
				//printf("arg2V before assignment = %d\n", arg2V);
			arg2V = lwAddr(tmpA, memArr);
				//printf("arg2V = %d\n\n", arg2V);			
			
			lw(arg1P, arg2V);	
			
			//printf("Data stored at Memory Address\n");
                        //printf("memArr[%d].addr stores the value: [%s]\n", j, memArr[j].doI);
			
			printf("Program Counter: [%x]\n", PC);
			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg2, *arg2Data);
					
			
			//printFunct(regArr);
			j++;
			PC += 4;


		//SW Function
		} else if(strcmp(memArr[j].doI, "sw") == 0){
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                memArr[j].arg3);

				//printf("tmpA before assignment = %s\n", tmpA);
			arg1P = memToReg(memArr[j].arg1, regArr);
				//printf("arg1P = %d\n", *arg1P);
                        arg2P = memToReg(memArr[j].arg2, regArr);
				//printf("arg2P = %d\n", *arg2P);	
			//sprintf(tmpA, "%d", *arg2P);
				//printf("tmpA = %s\n", tmpA);
				//printf("arg2V before assignment = %d\n", arg2V);
			//arg2V = lwAddr(tmpA, memArr);
				//printf("arg2V = %d\n\n", arg2V);			
			
			sw(arg1P, arg2P);	
			
			//printf("Data stored at Memory Address\n");
                        //printf("memArr[%d].addr stores the value: [%s]\n", j, memArr[j].doI);
			
			printf("Program Counter: [%x]\n", PC);
			//printf("Stack Pointer: [%x]\n", regArr[29].data);
			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg2, *arg2Data);
					
			
			printFunct(regArr);
			j++;
			PC += 4;
	
		//SUB Function
		} else if (strcmp(memArr[j].doI, "sub") == 0){	
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                memArr[j].arg3);
		
			arg1P = memToReg(memArr[j].arg1, regArr);
                        arg2P = memToReg(memArr[j].arg2, regArr);
                        arg3P = memToReg(memArr[j].arg3, regArr);
 
                        sub(arg1P, arg2P, arg3P);
			
			printf("Program Counter: [%x]\n", PC);
				
			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			arg3Data = memToReg(memArr[j].arg3, regArr);
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n", memArr[j].arg2, *arg2Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg3, *arg3Data);

			//printFunct(regArr);
			j++;
			PC += 4;


		//SUBU Function
		} else if (strcmp(memArr[j].doI, "subu") == 0){	
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                memArr[j].arg3);
			printf("Stack Pointer: [%d]\n", regArr[29].data);
			arg1P = memToReg(memArr[j].arg1, regArr);
			printf("Stack Pointer: [%d]\n", *arg1P);
                        arg2P = memToReg(memArr[j].arg2, regArr);
                        arg3V = atoi(memArr[j].arg3);
						
			
                        subu(arg1P, arg2P, arg3V);
			
			printf("Program Counter: [%x]\n", PC);
			printf("Stack Pointer: [%x]\n", regArr[29].data);
			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg2, *arg2Data);
						
									
			
			//printFunct(regArr);
			j++;
			PC += 4;
		
		//BNE Function
		} else if (strcmp(memArr[j].doI, "bne") == 0) {	
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                 j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                 memArr[j].arg3);
 			
			printf("Program Counter: [%x]\n", PC);
                        arg1P = memToReg(memArr[j].arg1, regArr);
                        arg2P = memToReg(memArr[j].arg2, regArr);
			arg3V = atoi(memArr[j].arg3);
			
			int z = j;
                        tmp = bne(arg1P, arg2P, arg3V, z, &PC);
			//printf("tmp is : %d\n", tmp);
			
			arg1Data = memToReg(memArr[j].arg1, regArr);
			arg2Data = memToReg(memArr[j].arg2, regArr);
			printf("Register: %s = [%d]\n", memArr[j].arg1, *arg1Data);
			printf("Register: %s = [%d]\n\n", memArr[j].arg2, *arg2Data);
			
			if(pcBranch == 1){			
				j = tmp;
				
				//printf("j is : %d\n", j);
				PC = j * 4;
			} else {
				j++;
				PC = PC + 4;
			}
			
			//printFunct(regArr);

		//BGTZ Function -- branch on greater than zero
		} else if (strcmp(memArr[j].doI, "bgtz") == 0) {	
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                 j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                 memArr[j].arg3);
 			
			printf("Program Counter: [%x]\n", PC);
                        arg1P = memToReg(memArr[j].arg1, regArr);
			arg2V = atoi(memArr[j].arg3);
			
			int z = j;
                        tmp = bgtz(arg1P, arg2V, z, &PC);
			//printf("tmp is : %d\n", tmp);
			
			arg1Data = memToReg(memArr[j].arg1, regArr);
			printf("Register: %s = [%d]\n\n", memArr[j].arg1, *arg1Data);
			
			if(pcBranch == 1){			
				j = tmp;
				
				//printf("j is : %d\n", j);
				PC = j * 4;
			} else {
				j++;
				PC = PC + 4;
			}
				
			//printFunct(regArr);
		
		//jump Function 
		} else if (strcmp(memArr[j].doI, "jump") == 0) {	
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                 j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                 memArr[j].arg3);
 			
			printf("Program Counter: [%x]\n\n", PC);
                   
			arg1V = (int)strtol(memArr[j].arg1, NULL, 16);
			//printf("arg1V is : %d\n", arg1V);
			int z = j;
                        tmp = jump(arg1V, z, &PC);
			//printf("tmp is : %d\n", tmp);
			
			//arg1Data = memToReg(memArr[j].arg1, regArr);
			//printf("Register: %s = [%d]\n\n", memArr[j].arg1, *arg1Data);
					
			j = tmp;
				
			//printf("j is : %d\n", j);
			PC = j * 4;
				
		//If the data/instruction field does not match, then load the data
		} else  {
			//If memArr[j].addr field is data	
			if (strcmp(memArr[j].arg1, "0") == 0){
			printf("Data [%s] added to registry [%d]\n\n",
                           	 memArr[j].doI, j);
			}
			//printf("Program Counter: [%x]\n", PC);
			//printFunct(regArr);

			j++;
		}
				
	}
}
