/*
 * This is a driver to test pass1 and the Label Table functions.
 *
 * Author: Alyce Brady
 * Date: 2/18/99
 * Modified by: Caitlin Braun and Giancarlo Anemone to test pass2 of the assembler.
 */


// Date: 2/21/2022
// Author: Li Jiaqi
// modified file extension to .cpp file to make project consistent
// modified to use std::string to represent c-strings

#include <string> 
#include <cstdio>
#include "labelTable.h"
#include "phase1.h"
#include "phase2.h"



int compare_files(FILE* fp1, FILE* fp2)
{

	char char1 = fgetc(fp1);
	char char2 = fgetc(fp2);

	while(char1 != EOF && char2 != EOF){
		if(char1 != char2){
			return -1;
		}
        char1 = fgetc(fp1);
        char2 = fgetc(fp2);
	}
	return 0;
}

int main (int argc, char * argv[])
{   
    if(argc < 4)
    {
        printf("Please enter an input file, an output file, and expected output file \n");
        return 0;
    }
    
    std::string infileName = argv[1];
    std::string outfileName = argv[2];
    std::string tempfileName = "_temp.txt";     // a temporary file will be generated in Phase1 and reused in Phase2
    // the temporary file will contain instructions with their addresses
    
    LabelTable table = Phase1::pass1(infileName, tempfileName);
    Phase2::pass2(outfileName, table, tempfileName); 

    FILE* fp1;
    FILE* fp2;
    fp1 = fopen(argv[3], "r");
    fp2 = fopen(argv[2], "r");

    if(fp1 == NULL || fp2 == NULL){
    	printf("Error: Files are not open correctly \n");
    }

    int res = compare_files(fp1, fp2);

    if(res == 0){
    	printf("ALL PASSED! CONGRATS :) \n");
    }else{
    	printf("YOU DID SOMETHING WRONG :( \n");
    }

    fclose(fp1);
    fclose(fp2);
    
    return 0;
}


