/*
Joshua Stuifbergen
10/24/18
CISS 247
MIPS Assignment
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Max length of each row from MIPS file
#define MAXLINE 100

//if bne function is used, then it signals that pc (program counter) has changed
int pcBranch;


//Memory Struct with MIPS fields
//6 since $zero is the longest
struct mipStruct{
	char addr[6];
	char doI[6];  //data or instruction
	char arg1[6];
	char arg2[6];
	char arg3[6];
}memArr[14];

//Register Struct
struct memReg{
	char *regi;
	int data;
}regArr[11];

//Registers hold the string identication and data
char mipsReg(){
	
	regArr[0].regi = "$zero";
        regArr[0].data = 0;
        regArr[1].regi = "$s0";
        regArr[1].data = 0;
        regArr[2].regi = "$s1";
        regArr[2].data = 0;
        regArr[3].regi = "$s2";
        regArr[3].data = 0;
        regArr[4].regi = "$s3";
        regArr[4].data = 0;
        regArr[5].regi = "$t0";
        regArr[5].data = 0;
        regArr[6].regi = "$t1";
        regArr[6].data = 0;
        regArr[7].regi = "$t2";
        regArr[7].data = 0;
        regArr[8].regi = "$t3";
        regArr[8].data = 0;
        regArr[9].regi = "$t4";
        regArr[9].data = 0;	


	//printf("regArr[0].regi = %s\n", regArr[0].regi);
	//printf("regArr[0].data = %d\n", regArr[0].data);
	
	return 0;
}

//match string values of mem to reg, return pointer &Register of data value
int *memToReg(char *arg, struct memReg regArr[]){
	if((strcmp(arg, "$zero")) == 0){		
		return &regArr[0].data;
	} else if((strcmp(arg, "$s0")) == 0){           
                return &regArr[1].data;
        } else if((strcmp(arg, "$s1")) == 0){ 
                return &regArr[2].data;
        } else if((strcmp(arg, "$s2")) == 0){ 
                 return &regArr[3].data;
        } else if((strcmp(arg, "$s3")) == 0){ 
                 return &regArr[4].data;
        } else if((strcmp(arg, "$t0")) == 0){ 
                 return &regArr[5].data;
        } else if((strcmp(arg, "$t1")) == 0){ 
                 return &regArr[6].data;
        } else if((strcmp(arg, "$t2")) == 0){
                 return &regArr[7].data;
        } else if((strcmp(arg, "$t3")) == 0){        
                  return &regArr[8].data;
        } else if((strcmp(arg, "$t4")) == 0){        
                 return &regArr[9].data;
        } else {

		printf("could not match mem string %s to reg\n", arg);
	}	
	return 0;
}

//String compares the string of the memory struct address and the
//string derived from the int value of an arguement sent to memToReg
// Returns the int value of the data field corresponding to the address
int lwAddr(char *arg, struct mipStruct memArr[]){
	int b;
	for(b = 0; b < 20; b++){	
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

//ADD Function
void add(int *arg1, int *arg2, int *arg3){
	*arg1 = *arg2 + *arg3;
}

//Load Word Function
void lw(int *arg1, int arg2){
	*arg1 = arg2;
}

//SUB Function
void sub(int *arg1, int *arg2, int *arg3){
            *arg1 = *arg2 - *arg3;
}

//BNE Function
int bne(int *arg1, int *arg2, int arg3, int *pc){
	pcBranch = 0;	
	if(*arg1 != *arg2){		
		pcBranch = 1;
	}
	return 0;
}

//prints the regArr[#].data values of the registry array after 
//every instruction completion
void printFunct(struct memReg RegArr[]){

	//printf("Program Counter: [%d]\n", PC);
        printf("Register: $zero = [%d] \n", regArr[0].data);
      	printf("Register: $s0 = [%d] \n", regArr[1].data);
        printf("Register: $s1 = [%d] \n", regArr[2].data);
        printf("Register: $s2 = [%d] \n", regArr[3].data);
        printf("Register: $s3 = [%d] \n", regArr[4].data);
        printf("Register: $t0 = [%d] \n", regArr[5].data);
        printf("Register: $t1 = [%d] \n", regArr[6].data);
        printf("Register: $t2 = [%d] \n", regArr[7].data);
        printf("Register: $t3 = [%d] \n", regArr[8].data);
        printf("Register: $t4 = [%d] \n\n", regArr[9].data);
}

int main (int argc, char *argv[]){
    	char line[MAXLINE];  
   	const char *delim = " ,\n";
	//struct mipStruct memArr[7];
        //FILE *fp;
        //fp = fopen("MYPS_FYLE", "r");
 
	int i = 0;
	
	//strtok will put the token prior to the delimiter into
	//the memory struct fields using strncpy
	memset(memArr, 0, sizeof(memArr));
	while(fgets(line, MAXLINE, stdin)){
		char *nextField;
               	nextField = strtok(line, delim);
		strncpy(memArr[i].addr, nextField, strlen(nextField));
                nextField = strtok(NULL, delim);
		strncpy(memArr[i].doI, nextField, strlen(nextField));
               	nextField = strtok(NULL, delim);
   		strncpy(memArr[i].arg1, nextField, strlen(nextField));
                nextField = strtok(NULL, delim);
   		strncpy(memArr[i].arg2, nextField, strlen(nextField));
               	nextField = strtok(NULL, delim);
  		strncpy(memArr[i].arg3, nextField, strlen(nextField));
			
		//print Memory Struct string values
		/*printf("	      addr doI arg1 arg2 arg3\n");
		printf("memArr[%d] = [%s]", i,  memArr[i].addr);
		printf(" [%s]", memArr[i].doI);
		printf(" [%s]", memArr[i].arg1);
		printf(" [%s]", memArr[i].arg2);
		printf(" [%s]\n", memArr[i].arg3);
		
		//Print Memory Stuct memory location
		printf("  [%d]=[%p]\n", i,(void*) &memArr[i].addr);
                printf("      [%p]\n", (void*) &memArr[i].doI);
                printf("      [%p]\n", (void*) &memArr[i].arg1);
                printf("      [%p]\n", (void*) &memArr[i].arg2);
                printf("      [%p]\n\n", (void*) &memArr[i].arg3);
		
		printf("  [0].regi =[%p]\n",(void*) &regArr[0].regi);
        	printf("  [0].data =[%p]\n\n", (void*) &regArr[0].data);
		*/
		i++;		      
	}
	//sets terminator to "STOP", placed in last struct +1 
	strncpy(memArr[i].addr, "STOP", 4);	
	printf("terminator at memArr[%d].addr: [%s]\n", i, memArr[i].addr);
	printf("      [%p]\n\n", (void*) &memArr[i].addr);			

 	int j = 0;
	//int 512 = 200 hex, increase int by 4 to match hex
	int PC = 512;
	printf("BEFORE\n");
	printf("Program Counter BEFORE: [%x]\n", PC);	
	printf("Registers BEFORE instructions.\n");
	printf("Register: $zero = [%d] \n", regArr[0].data);
        printf("Register: $s0 = [%d] \n", regArr[1].data);
        printf("Register: $s1 = [%d] \n", regArr[2].data);
        printf("Register: $s2 = [%d] \n", regArr[3].data);
        printf("Register: $s3 = [%d] \n", regArr[4].data);
        printf("Register: $t0 = [%d] \n", regArr[5].data);
        printf("Register: $t1 = [%d] \n", regArr[6].data);
        printf("Register: $t2 = [%d] \n", regArr[7].data);
        printf("Register: $t3 = [%d] \n", regArr[8].data);
        printf("Register: $t4 = [%d] \n\n", regArr[9].data);

	
	//while .addr is not "STOP", continue
	while(strcmp(memArr[j].addr, "STOP")){
		
		//I had arg1P, arg2P, and arg3P as char *, didn't work....
		int *arg1P;
		int *arg2P;
		int *arg3P;	
		//int *arg1PMem;
		//int *arg2PMem;
		//int arg1V;
		int arg2V;
		int arg3V;
		//int tmpPC;
		//int jump;
		char tmpA[6];
		//memset(tmpA, 0, sizeof(tmpA));
		
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
			printFunct(regArr);
			//j++;
		
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
			printFunct(regArr);
			//j++;
			
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
			printFunct(regArr);
			//j++;
			
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
			printFunct(regArr);
			//j++;
			
		//BNE Function
		} else if (strcmp(memArr[j].doI, "bne") == 0) {	
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                                 j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                 memArr[j].arg3);
 			//tmpPC = PC;
			//printf("Program Counter: [%x]\n", PC);
                        arg1P = memToReg(memArr[j].arg1, regArr);
                        arg2P = memToReg(memArr[j].arg2, regArr);
			arg3V = atoi(memArr[j].arg3);
		
                        bne(arg1P, arg2P, arg3V, &PC);
		

			if(pcBranch != 1){
				break;
			}

			/*if(pcBranch == 1){
				int v;
				for(v = 1; v < 20; v++){	
					if((strcmp(memArr[j].arg3, memArr[v].addr)) == 0){			
						return j = (v - (j + 1));
						PC += j * 4;
						printf("j is : %d\n", j);
						printf("Program Counter: [%x]\n", PC);
						printFunct(regArr);
					 }
				}	
				return 0;
			} else {
				j++;
				PC += PC + 4;
			}*/

			printf("Program Counter: [%x]\n", PC);
			printFunct(regArr);
			
		//If the data/instruction field does not match, then load the data
		} else {
			//If memArr[j].addr field is data				
			printf("Instruction [%d] executed: [%s][%s][%s][%s]\n\n",
                           	 j, memArr[j].doI, memArr[j].arg1, memArr[j].arg2,
                                 memArr[j].arg3);
		
			printf("Program Counter: [%x]\n", PC);
			printFunct(regArr);
		//j++;
		
		} 		
	j++;
	PC = PC + 4;
	}
}
