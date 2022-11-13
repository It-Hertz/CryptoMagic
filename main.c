#include <stdio.h>
#include <string.h>

int charToAscii();
int asciiToHex();
int hexToAscii();
int asciiToChar();


int main (void) {
    char option;
    char file[100]; //see later if you can make bigger and fix errors
    char buffer[120];
    char bufferString[120];
    int outChar;

    scanf("cryptoMagic -%c %s",&option, &file);
    
    //initialize pointers for files
    FILE *inputPtr = fopen(file,"r");
    FILE *outputPtr = NULL;

    //empty read file
    if (inputPtr == NULL) {
        printf("\nError: File does not exist\n");
    }
    
    //file OK
    else {
        
        //Encrypt Mode
        if (option == 'E') {
            
            //grabs the base file name
            char newFileName[100];
            for (int i = 1; i<=strlen(file); i++){
                if (file[i] == '.') {
                    strncpy(newFileName,file, i);
                    break;
                }
                else if (i == strlen(file)){
                    strncpy(newFileName,file, i);
                    break;
                }
            }
            
            //appends file extension to base file name
            char fileExten[] = ".crp";
            strcat(newFileName, fileExten);
           
            // create new file and close it
            outputPtr = fopen(newFileName, "w");
            fclose(outputPtr);

            //read input file
            while(fgets(buffer, 120, inputPtr) != NULL){
                for (int j = 1; j<=strlen(buffer); j++){
                    
                    // open new file in read mode while converting buffer line
                    outputPtr = fopen(newFileName, "r");

                    //convert tab to TT
                    if (chartoAscii(buffer[j]) == 9) {
                        char tempString[] = "TT";
                        strcat(bufferString, tempString);
                    }
                    
                    //convert char to hexadecimal then append to bufferString
                    else {
                        outChar = chartoAscii(buffer[j])-16;
                        if (outChar <32) {
                            outChar = (outChar - 32) + 144;
                            strcat(bufferString, AsciiToHex(outChar));
                        }

                        else {
                            strcat(bufferString, AsciiToHex(outChar));
                        }
                    }

                    //close file after done converting buffer line
                    fclose(newFileName);
                }

                //open file in append mode
                outputPtr = fopen(newFileName, "a");
                
                //print bufferString (encrypted line) to file
                fprintf(newFileName, bufferString);
            }
        }
        
        //Decrypt Mode
        else if (option == 'D'){
            
             //grabs the base file name
            char newFileName[100];
            for (int i = 1; i<=strlen(file); i++){
                if (file[i] == '.') {
                    strncpy(newFileName,file, i);
                    break;
                }
                else if (i == strlen(file)){
                    strncpy(newFileName,file, i);
                    break;
                }
            }
            
            
            //appends file extension to base file name
            char fileExten[] = ".txt";
            strcat(newFileName, fileExten);
            outputPtr = fopen(newFileName, "w");

        }
        
        //Invalid Input
        else {
            printf("Error: Invalid input");
        }
    }
    
    fclose(inputPtr);
    fclose(outputPtr);
    return 0;
}