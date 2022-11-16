#include <stdio.h>
#include <string.h>

int charToAscii(char character);
char asciiToChar(int ascii);

int main (int argc, char* argv[]) {
    
    FILE *inputPtr = fopen(argv[1],"r");
    
    char bufferString[120];
    char buffer[120];
    int outChar;

    while(fgets(buffer, 120, inputPtr) != NULL){
                printf("\nCYCLE\n");
            memset(bufferString, 0, 120);
            printf("\nThe string length is: %d\n", strlen(buffer));
            for (int j = 0; j<=strlen(buffer)-1; j++){
                printf("Origin Val: %c\n", buffer[j]);
                
                if (outChar == 13) {
                    continue;
                }
                else if (buffer[j] == '\0'){
                    break;
                }
                else{
                    outChar = charToAscii(buffer[j])-16;
                    if (outChar <32) {
                        outChar = (outChar - 32) + 144;
                        char tempBuf[1];
                        tempBuf[0] = asciiToChar(outChar);
                        bufferString[j] = outChar;
                        //printf("tempBuf: %s\n", tempBuf);
                    }

                    else {
                        char tempBuf2[1];
                        tempBuf2[0] = asciiToChar(outChar);
                        printf("temp [%d]: %c\n", j, tempBuf2[0]);
                        printf("value before append: %c\n", bufferString[j]);
                        //strncat(bufferString, tempBuf2, 1);                       //DID NOT NEED
                        bufferString[j] = outChar;
                        printf("bufstring [%d]: %c\n\n", j, bufferString[j]);
                        printf("bufferString val:%s\n\n", bufferString);
                    }
                }

            }
        printf("%s\n", bufferString);
        printf("\nCYCLE OVER\n");
                
    }
}

int charToAscii(char character){
    int resultCharacter = character;
    return resultCharacter;
}

char asciiToChar(int ascii){
    char resultCharacter = ascii;
    return resultCharacter;
} 