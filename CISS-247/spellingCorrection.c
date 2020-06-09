/*
Joshua Stuifbergen
11/14/18
CISS247
Assignment 2
Suggest spelling corrections to English words entered from the keyboard.  
Words entered by the user of the program will be compared to a list of 
over 105,000 words supplied in a data file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_WORD_LEN 40
#define MAX_WORDS 120000

char wordlist[MAX_WORDS][MAX_WORD_LEN];

//Loads the word file into the wordlist array
void load(FILE *input){
	int i = 0;	
	char word[MAX_WORD_LEN];
	while(fgets(word, MAX_WORD_LEN, input)){	
		word[strcspn(word, "\n")] = 0;		
		strcpy(wordlist[i], word);
	
		//printf("%s\n", wordlist[i]);	
	i++;
	}
	printf("\n\n");

}

//Returns the hamming length
int userInput(char *word, char *wordlist){
	int ham = 0;
	int tmp = 0;
	//printf("wordlist[a] in hamm function is %s", wordlist);			
	for(int x = 0; x < strlen(word); x++){
		ham = wordlist[x] - word[x];
		if(ham != 0){
			tmp++;	
		}
	}
	//printf("hamming value in userInput Function %d", tmp);
	//printf("ham val is: %i", ham);
	return tmp;	
}

int main (int argc, char *argv[]){
    	char wordlist[MAX_WORDS][MAX_WORD_LEN];
	int tru = 1;
	FILE *input = fopen(argv[1], "r");
	load(input);
	char WORDO[MAX_WORD_LEN];
	char WORDUP[MAX_WORD_LEN];
	char user[MAX_WORD_LEN];
  
	//Continue until user exits
	while(tru == 1){	
		
		//printf("Enter a word that you think may be a word, and if\n");
		//printf("nothing matches, a similar spelled word is returned.\n");
		//printf("The word must be less than 40 character. Hit enter to exit.\n");
		printf("Enter a word: ");	
		fgets(user, MAX_WORD_LEN, stdin);
		printf("\n");
		printf("Your word is: %s\n", user);
		
		//putting user into WORDO 
		strncpy(WORDO, user, strlen(user));
		//remove \n from word
		user[strcspn(user, "\n")] = 0;
		printf("Word BEFORE strcspn is: [%s]\n", WORDO);	
		printf("Word AFTER strcspn is: [%s]\n\n", user);	
		
		//User exits program if they hit Enter
		if(strlen(user) == 0){
			printf("Exiting\n");
			tru = 0;
			EXIT_SUCCESS;
		}
		printf("The user chose NOT to EXIT\n\n");

		//Returns to prompt if user enter 40+ characters
		/*if(MAX_WORD_LEN < strlen(user)){
			printf("Too many characters. Enter less than 40\n\n");
			break;	
		}*/
		
		strncpy(WORDUP, user, strlen(user));
		int w = 0;
		//Changes letter to lowercase
		while(w <= strlen(user)){
			user[w] = tolower(user[w]);
			printf("tolower, W = %d\n", w);
			w++;
		}
		printf("\n");
		printf("[%s] before and after toLower [%s]\n\n", WORDUP, user);
	
		//Looks through wordlist array to find a matching word
		printf("\n\n");
		
	}	
}
