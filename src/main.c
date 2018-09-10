/*
Minimal huffman compression program
Written by:
Nicolas Leão, Matheus Artur, Luis Cabus and Fábio Vinícius.
UFAL
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "binarytree.h"

#define DEBUG 0

// Function to compress a file.
void compress(FILE* file) {

	// Pointer to the linked list
	fnode_l *frequency_list = NULL;

	// Pointer to the huffman tree root
	huf_tree *huffman_tree = NULL;

	// Create a frequency list from the bytes in the file
	create_frequency_list(file, &frequency_list);

	// Sort the frequency list
	sort_frequency_list(&frequency_list);

	// Create the file's huffman tree
	// build_huffman_tree(&huf_tree, frequency_list);

	// Build the compressed file 
	// build_compressed_file(huf_tree, );

	// Debug loop to print the bytes in hexadecimal and their frequencies.
	while(frequency_list != NULL && DEBUG == 1) {
		printf("BYTE: %hhx / FREQ: %d\n", *((char *)frequency_list->value), frequency_list->freq);
		frequency_list = frequency_list->next;
	}
	puts("");
}

int main(int argc, char **argv) {
	/* 
	The command that will determine the operation to be executed is passed as the first argument (argv[1]).
	the available command/operation touples are: (-c, compress), (-e, extract) and (-h, help).
	The file that will be used is passed as the second argument (argv[2]) when the program is executed. 
	
	An example of the usage is: ./huffman -c picture.jpg, that will compress the file "picture.jpg"

	The file specified will be stored in the variable "file", as read-only to ensure that the original data is not
	altered in the compression process. 
	*/
	
	char cmd[10];
	char path[255];
	
	if(argv[1] == NULL) {
		printf("Invalid command specified, use ./program -h to see a list of available commands.\n");
	}
	else if(strcmp(argv[1], "-c") == 0) {
		strcpy(cmd, "-c");
		strcpy(path, argv[2]);
	}
	else if(strcmp(argv[1], "-e") == 0) {
		strcpy(cmd, "-e");
		strcpy(path, argv[2]);
	}

	printf("cmd: %s\n", cmd);

	if(strcmp(cmd, "-c") == 0) {
		FILE *file = fopen(path, "r");
		if(file == NULL) {
			// If the file cannot be accessed, the program exits with error code 1.
			printf("Error! File could not be loaded successfully.\nExiting...\n");
			return 1;
		}
		compress(file);
		fclose(file);
	} 
	else if(strcmp(cmd, "-e") == 0) {
		FILE *file = fopen(path, "r");
		if(file == NULL) {
			// If the file cannot be accessed, the program exits with error code 1.
			printf("Error! File could not be loaded successfully.\nExiting...\n");
			return 1;
		}
		char *current_byte = malloc(sizeof(char *));
		//fread will read one byte at a time from the "file" variable and store it in the "current_byte" variable.
		while(fread(current_byte, 1, 1, file)) {
			//TODO: extraction algorithm.
			//magic happens here.
		}
		fclose(file);
	}
	else if(strcmp(argv[1], "-h") == 0) {
		printf("The syntax to use the program is: ./program <command> <file>\n");
		printf("Available commands:\n");
		printf("-c, Compress the specified file.\n");
		printf("-e, Extract the specified file.\n");
		printf("Example usage: ./program -c myfile.png\n");
	}
	else {
		printf("Invalid command specified, use ./program -h to see a list of available commands.\n");
	}
	
	return 0;
}
