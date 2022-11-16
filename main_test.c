#include <stdio.h>
#include <string.h>

int charToAscii(char character);
void asciiToHex(char* outputDestination, int stringSize, int ascii);
char asciiToChar(int ascii);


int main (void) {
    char option;
    char file[50]; //see later if you can make bigger and fix errors
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
            char newFileName[strlen(file)];
            for (int i = 0; i<=strlen(file)-1; i++){
                if (file[i] == '.') {
                    strncpy(newFileName,file, i);
                    break;
                }
                else if (i == strlen(file)-1){
                    strncpy(newFileName,file, i);
                    break;
                }
            }
            
            //appends file extension to base file name
            char fileExten[] = ".crp";
            strcat(newFileName, fileExten);
           
            // create new file and close it
            outputPtr = fopen(newFileName, "w");
            //fclose(outputPtr);
            
            //open file in append mode
              //  outputPtr = fopen(newFileName, "a");

            //read input file
            while(fgets(buffer, 120, inputPtr) != NULL){
                printf("\nCYCLE\n");
                for (int j = 0; j<=strlen(buffer)-1; j++){
                    printf("Origin Val: %c\n", buffer[j]);
                    //convert tab to TT
                  /*  
                    if (charToAscii(buffer[j]) == 9) {
                        char tempString[] = "TT";
                        strcat(bufferString, tempString);
                    }
                    
                    //convert char to hexadecimal then append to bufferString
                    */
                        outChar = charToAscii(buffer[j])-16;
                        if (outChar <32) {
                            outChar = (outChar - 32) + 144;
                            char tempBuf[1];
                            tempBuf[0] = asciiToChar(outChar);
                            //int numsize = 2;
                            //asciiToHex(tempBuf, numsize, outChar);
                            strcat(bufferString, tempBuf);
                            //printf("tempBuf: %s\n", tempBuf);
                        }

                        else {
                            //int numsize = 2;
                            char tempBuf2[1];
                            tempBuf2[0] = asciiToChar(outChar);
                            printf("temp [%d]: %c\n", j, tempBuf2[0]);
                            //asciiToHex(tempBuf2, numsize, outChar);
                            printf("value before append: %c\n", bufferString[j]);
                            strncat(bufferString, tempBuf2, 1);
                            //printf("Tempbuf2: %s", tempBuf2);
                            printf("bufstring [%d]: %c\n\n", j, bufferString[j]);
                        }
                }
                printf("%s\n", bufferString);
            
                
                //print bufferString (encrypted line) to file
                fprintf(outputPtr, bufferString);
                fprintf(outputPtr, "\n");  
            
            printf("\nCYCLES OVER\n");
                
            } 
            fprintf(outputPtr, "\n");   
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

//conversion functions

//char to ascii
int charToAscii(char character){
    int resultCharacter = character;
    return resultCharacter;
}

//ascii to hex
void asciiToHex(char* outputDestination, int stringSize, int ascii){
    int resultant = ascii;
    int tempResultant = ascii;
    int divisnum = 0;

    //# of times ascii can be divided by 16
    while (tempResultant != 0){
        tempResultant = tempResultant / 16;
        divisnum++;
    }

    //find hex numbers
    char remainders[divisnum];
    for (int k = 0; k <= divisnum-1; k++){
        remainders[k] = resultant % 16;
        resultant = resultant / 16;
    }


    //declare tempbuffer with size
    char asciiBuffer[divisnum];

    //order hex numbers in temp buffer string then append temp buffer to buffer
    for (int l = divisnum-1, m = 0; l>=0; l--, m++){
        if (remainders[l] <= 9){
            asciiBuffer[m] = 48 + remainders[l];
        }
        else {
            asciiBuffer[m] = 55 + remainders[l];
        }
    }
        //debugging statements to print values for divisnum and remainder values
        #ifdef DEBUG
        printf("\n\nThe size of asciibuffer :%d\n", sizeof(asciiBuffer));
        for (int b = 0; b<=divisnum-1; b++){
            printf("\n\nremainder %d: %c\n", b, asciiBuffer[b]);
        }
        printf("\ndivisnum: %d\n", divisnum);
        #endif

    //copy const string from function to string declared outside of function
    for (int a = 0; a<=strlen(asciiBuffer); a++){
        printf("%c", asciiBuffer[a]);
    }
    strncpy(outputDestination, asciiBuffer, stringSize);
}


char asciiToChar(int ascii){
    char resultCharacter = ascii;
    return resultCharacter;
} 