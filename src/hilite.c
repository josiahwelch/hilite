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

int IntegerParse(char *charsToParse) {

	//returns a parsed integer from a char array with ASCII support
	
	int parsedInt = 0;

	int index;
	
	for(int i = strlen(charsToParse) - 1; i >= 0; i--) {

		index = strlen(charsToParse) - 1 - i; //sets the index of the char being parsed

		parsedInt += (charsToParse[index] - 48) * pow(10, i); //adds the char from the char array with ASCII conversion and decimal parsing

	}

	return parsedInt;

}

int main(int argc, char **argv) {
	
	//initializes variables and pointers
	int color;
	char *textToFind;
	char *text;

	//parses arguments
	if(argc = 5) {

		//handles background color
		if(strcmp(argv[1], "-b") || strcmp(argv[1], "--background")) {

			if(strcmp(argv[2], "black")) { color = 40; }

			if(strcmp(argv[2], "red")) { color = 41; }

			if(strcmp(argv[2], "green")) { color = 42; }

			if(strcmp(argv[2], "yellow")) { color = 43; }

			if(strcmp(argv[2], "blue")) { color = 44; }

			if(strcmp(argv[2], "white")) { color = 47; }

			if(isdigit(argv[3])) { color = IntegerParse(argv[3]); }

		}	

		//handles foreground color
		if(strcmp(argv[1], "-f") || strcmp(argv[1], "--foreground")) {

			if(strcmp(argv[2], "black")) { color = 30; }

			if(strcmp(argv[2], "red")) { color = 31; }

			if(strcmp(argv[2], "green")) { color = 32; }

			if(strcmp(argv[2], "yellow")) { color = 33; }

			if(strcmp(argv[2], "blue")) { color = 34; }

			if(strcmp(argv[2], "white")) { color = 37; }

			if(isdigit(argv[3])) { color = IntegerParse(argv[3]); }

		}	

		textToFind = argv[3];
		text = argv[4];

	}

	else if(argc = 3) {
		color = 43; //yellow background

		textToFind = argv[2];
		text = argv[3];
	}

	else if(argc = 2 && (strcmp(argv[1], "-h") || strcmp(argv[1], "--help"))) {

		printf("hilite [OPTIONS] TEXT_TO_HIGHLIGHT TEXT_TO_BE_HIGHLIGHTED\n\nOPTIONS:\n-h/--help\t\tProvides help with usage\n-b/--background {COLOR | COLOR_CODE}\t\tSets the background color to user specification\n-f/--foreground\t\tSets the color of the highlighted text\n\nCOLORS:\nblack\nred\ngreen\nyellow\nblue\nwhite\n\nCOLOR_CODE: ANSI escape color codes... such as 35 for magenta-colored text\n");

		return 0;
	}

	else { return -1; }

	char *ptr = strstr(text, textToFind);

	if(ptr == NULL) {
		
		printf("STRING NOT FOUND\n");
		
		return -1;

	}

	else {

		while(ptr != NULL) {

			for(int i = 0; i < (ptr - text); i++) { printf(text[i]); } //prints text all the way up to where textToFind was found
			
			text = (ptr + strlen(textToFind));

			printf(setTextColor(textToFind, color));

		}

	}

	return 0;
}
