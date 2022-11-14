#include <stdio.h>
#include <string.h>

int charToAscii(char character);
void asciiToHex(char* outputDestination, int stringSize, int ascii);
char asciiToChar(int ascii);


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
            fclose(outputPtr);

            //read input file
            while(fgets(buffer, 120, inputPtr) != NULL){
                for (int j = 1; j<=strlen(buffer); j++){

                    //convert tab to TT
                    if (charToAscii(buffer[j]) == 9) {
                        char tempString[] = "TT";
                        strcat(bufferString, tempString);
                    }
                    
                    //convert char to hexadecimal then append to bufferString
                    else {
                        outChar = charToAscii(buffer[j])-16;
                        if (outChar <32) {
                            outChar = (outChar - 32) + 144;
                            char tempBuf[2];
                            int numsize = 2;
                            asciiToHex(tempBuf, numsize, outChar);
                            strcat(bufferString, tempBuf);
                        }

                        else {
                            char tempBuf2[2];
                            int numsize = 2;
                            asciiToHex(tempBuf2, numsize, outChar);
                            strcat(bufferString, tempBuf2);
                        }
                    }
                }

                //open file in append mode
                outputPtr = fopen(newFileName, "a");
                
                //print bufferString (encrypted line) to file
                fprintf(outputPtr, bufferString);
                fprintf(outputPtr, "\n");
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
            
            //creates decrypted file location and closes it
            outputPtr = fopen(newFileName, "w");
            fclose(outputPtr);

            //read input file
            while(fgets(buffer, 120, inputPtr) != NULL){
                for (int j = 1; j<=strlen(buffer); j=j+2){

                    //convert TT to tab
                    if (buffer[j] == 'T' && buffer[j+1] == 'T') {
                        char tempString[] = "\t"; //hopefully \t is the tab value
                        strcat(bufferString, tempString);
                    }
                    
                    //convert hexadecimal to char then append to bufferString
                    else {
                        outChar = (buffer[j]*16 + buffer[j+1]) + 16;
                        if (outChar >127) {
                            outChar = (outChar - 144) + 32;
                        }
                        char tempString[1];
                        tempString[0] = outChar;
                        strcat(bufferString, tempString);
                    }
                }

                //open file in append mode
                outputPtr = fopen(newFileName, "a");
                
                //print bufferString (encrypted line) to file
                fprintf(outputPtr, bufferString);
            }
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
    int divisnum;

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

    //debugging statements to print values for divisnum and remainder values
    #ifdef DEBUG
        printf("\n\nThe size of remainder :%d\n", strlen(remainders));
        for (int b = 0; b<=divisnum-1; b++){
            printf("\n\nremainder %d: %d\n", b, remainders[b]);
        }
        printf("\ndivisnum: %d\n", divisnum);
    #endif

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
    strncpy(outputDestination, asciiBuffer, stringSize);
}


char asciiToChar(int ascii){
    char resultCharacter = ascii;
    return resultCharacter;
}