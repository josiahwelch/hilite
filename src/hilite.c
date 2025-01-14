#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char *setTextColor(char *text, int color) {

	//returns the concatenation of the ANSI escape codes with appropriate color codes and the text inputted into the function
	
	//initializes return buffer
	char buffer[strlen(text)];

	sprintf(buffer, "\033[%im%s\033[0m", color, text);

	return &buffer;
}

int isStringEqual(char *str1, char *str2) {

	//returns if two strings are identical... strcmp() is giving me segmentation faults and I'm too lazy to deal with it
	
	if(strlen(str1) != strlen(str2)) { return 0; } //handles the easiest subproblem... if the two strings are different sizes then the two strings obviously cannot be identical
	
	for(int i = 0; i < strlen(str1); i++) {

		if(str1[i] != str2[i]) { return 0; }
	
	}

	return 1;

}

int isDigit(char *str) {

	//returns if a string contains an integer value... isdigit is also giving me segmentation faults and I'm too lazy to deal with it
	
	char digits[] = "1234567890";

	int isCurrentCharDigit = 0;

	for(int i = 0; i < strlen(str); i++) {

		isCurrentCharDigit = 0;

		for(int indexOfDigits = 0; indexOfDigits < 10; indexOfDigits++) {

			if(str[i] == digits[indexOfDigits]) { isCurrentCharDigit = 1; }

		}

		if(!isCurrentCharDigit) { return 0; }

	}

	return 1;

}

int IntegerParse(char *charsToParse) {

	//returns a parsed integer from a char array with ASCII support
	
	int parsedInt = 0;

	int index;
	
	for(int i = strlen(charsToParse) - 1; i >= 0; i--) {

		index = strlen(charsToParse) - 1 - i; //sets the index of the char being parsed

		parsedInt += (charsToParse[index] - 48) * (int) pow(10.0, (double) i); //adds the char from the char array with ASCII conversion and decimal parsing

	}

	return parsedInt;

}

int main(int argc, char **argv) {
	
	//initializes variables and pointers
	int color;
	char *textToFind;
	char *text;
	
	//parses arguments
	if(argc == 5) {

		//handles background color
		if(isStringEqual(argv[1], "-b") || isStringEqual(argv[1], "--background")) {

			if(isStringEqual(argv[2], "black")) { color = 40; }

			if(isStringEqual(argv[2], "red")) { color = 41; }

			if(isStringEqual(argv[2], "green")) { color = 42; }

			if(isStringEqual(argv[2], "yellow")) { color = 43; }

			if(isStringEqual(argv[2], "blue")) { color = 44; }

			if(isStringEqual(argv[2], "white")) { color = 47; }

			if(isDigit(argv[2])) { color = IntegerParse(argv[2]); }

		}	

		//handles foreground color
		if(isStringEqual(argv[1], "-f") || isStringEqual(argv[1], "--foreground")) {

			if(isStringEqual(argv[2], "black")) { color = 30; }

			if(isStringEqual(argv[2], "red")) { color = 31; }

			if(isStringEqual(argv[2], "green")) { color = 32; }

			if(isStringEqual(argv[2], "yellow")) { color = 33; }

			if(isStringEqual(argv[2], "blue")) { color = 34; }

			if(isStringEqual(argv[2], "white")) { color = 37; }

			if(isDigit(argv[2])) { color = IntegerParse(argv[2]); }

		}	

		textToFind = argv[3];
		text = argv[4];

	}

	else if(argc == 3) {
		color = 103; //yellow background

		textToFind = argv[1];
		text = argv[2];

	}

	else if(argc == 2 && (isStringEqual(argv[1], "-h") || isStringEqual(argv[1], "--help"))) {

		printf("hilite [OPTIONS] TEXT_TO_HIGHLIGHT TEXT_TO_BE_HIGHLIGHTED\n\nOPTIONS:\n-h/--help\t\t\t\t\tProvides help with usage\n-b/--background {COLOR | COLOR_CODE}\t\tSets the background color to user specification\n-f/--foreground {COLOR | COLOR_CODE}\t\tSets the color of the highlighted text\n\nCOLORS:\nblack\nred\ngreen\nyellow\nblue\nwhite\n\nCOLOR_CODE: ANSI escape color codes... such as 35 for magenta-colored text\n");

		return 0;
	}

	else { return -1; }

	char *ptr = strstr(text, textToFind);

	if(ptr == NULL) {
		
		printf("STRING NOT FOUND\n");
		
		return -1;

	}

	else {

		while(ptr != NULL && ptr < (text + strlen(text))) {

			for(int i = 0; i < (ptr - text); i++) { printf("%c", text[i]); } //prints text all the way up to where textToFind was found

			//printf("%s : %s\n", text, ptr);
			
			ptr += strlen(textToFind);
			
			text = ptr; //sets the pointer pointing to the location of the text to be after where the instance of textToFind was found

			printf("%s", setTextColor(textToFind, color));

			ptr = strstr(text, textToFind);

		}

		printf("%s\n", text);

	}

	return 0;
}
