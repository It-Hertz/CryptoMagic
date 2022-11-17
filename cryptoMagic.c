#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char *file);
void decrypt(char* file);
void asciiToHex(char* input, char* output);
void hexToAscii(char* input, char* output);

int main (int argc, char* argv[]) {
    char *option;
    char *file;
    FILE *inputPtr;
    // when nothing is passed through argument
    if(argc == 1) {
        printf("\nError: Command and File not entered\n");
        exit(1);
    // when only 1 argument is passed, perform encrypt if valid file name is passed
    } else if(argc == 2) {
        file = malloc(strlen(argv[1]) + 1);
        strcpy(file, argv[1]);
        inputPtr = fopen(file,"r");
        if (inputPtr == NULL) {
            printf("\nError: Command or File does not exist\n");
            exit(1);
        } else {
            encrypt(file);
        }
    // when both option and file name are passed
    } else if(argc == 3) {
        file = malloc(strlen(argv[2]) + 1);
        option = malloc(strlen(argv[1]) + 1);
        strcpy(option, argv[1]);
        strcpy(file, argv[2]);
        inputPtr = fopen(file,"r");
        if (inputPtr == NULL) {
            printf("\nError: File does not exist\n");
            exit(1);
        } else {
            char *opE = malloc(strlen(argv[1]) + 1);
            char *opD = malloc(strlen(argv[1]) + 1);
            opE = "-E";
            opD = "-D";
            if (strcmp(option, opE) == 0) {
                encrypt(file);
            } else if (strcmp(option, opD) == 0) {
                decrypt(file);
            } else {
                printf("\nError: Command does not exist\n");
                exit(1);
            }
        }
    } else {
        printf("\nError: Command or File does not exist\n");
        exit(1);
    }
    fclose(inputPtr);
    return 0;
}

void encrypt(char* file) {
    char newFileName[strlen(file)];
    char buffer[121];
    FILE *f = fopen(file, "r");
    // process the new file name
    int i = 0;
    while (i < strlen(file)){
        if (file[i] == '.') {
            strncpy(newFileName, file, i);
            break;
        }
        i++;
    }
    if (i == strlen(file)) {
        strcpy(newFileName, file);
    }
    char fileExten[10] = ".crp";
    strcat(newFileName, fileExten);
    FILE *outputPtr = fopen(newFileName, "w");
    // convert the content of each line
    while(fgets(buffer, 120, f) != NULL) {
        buffer[strlen(buffer)] = '\0';
        char *tempString = malloc((strlen(buffer) * 2) + 1);
        asciiToHex(buffer, tempString);
        fputs(tempString, outputPtr);
        fputs("\n", outputPtr);
    }
    fclose(outputPtr);
    fclose(f);
}

void asciiToHex(char* input, char* output) {
    int i = 0;
    int j = 0;

    while(input[i] != '\0') {
        if (input[i] == '\n') {
            break;
        }
        if (input[i] == 9) {
            char tempString[] = "TT";
            strcat(output, tempString);
        }
        char outChar = input[i] - 16;
        if(outChar < 32) {
            int t = (outChar - 32) + 144;
            sprintf((char*)(output+j),"%02X", t);
        } else {
            sprintf((char*)(output+j),"%02X", outChar);
        }
        i+=1;
        j+=2;
    }   
    output[j++] = '\0';
}

void decrypt(char* file) {
    char newFileName[strlen(file)];
    char buffer[121];
    FILE *f = fopen(file, "r");
    int i = 0;
    while (i < strlen(file)){
        if (file[i] == '.') {
            strncpy(newFileName, file, i);
            break;
        }
        i++;
    }
    if (i == strlen(file)) {
        strcpy(newFileName, file);
    }
    char fileExten[10] = ".txt";
    strcat(newFileName, fileExten);
    FILE *outputPtr = fopen(newFileName, "w");
    while(fgets(buffer, 120, f) != NULL) {
        buffer[strlen(buffer)] = '\0';
        char *tempString = malloc(strlen(buffer));
        hexToAscii(buffer, tempString);
        fputs(tempString, outputPtr);
        fputs("\n", outputPtr);
    }
    fclose(outputPtr);
    fclose(f);
}

void hexToAscii(char* input, char* output) {
    int i = 0;
    int j = 0;
    int temp = 0;

    while(input[i] != '\0') {
        if (input[i] == '\n') {
            break;
        }
        if (input[i] == 'T' && input[i+1] == 'T') {
            char tempString[] = "\t";
            strcat(output, tempString);
        }
        if ((input[i] >= '0' && input[i] <= '9') && (input[i+1] >= '0' && input[i+1] <= '9')) {
            temp = ((input[i] - '0') * 16) + (input[i+1] - '0') + 16;
        } else if ((input[i] >= '0' && input[i] <= '9') && (input[i+1] >= 'A' && input[i+1] <= 'F')) {
            temp = (input[i+1] - 'A' + 10) + ((input[i] - '0') * 16) + 16;
        } 
        if (temp > 127) {
            int t = (temp - 144) + 32;
            sprintf((char*)(output+j),"%c", t);
        } else {
            sprintf((char*)(output+j),"%c", (char) temp);
        }
        i+=2;
        j+=1;
    }
    output[j++] = '\0';
}