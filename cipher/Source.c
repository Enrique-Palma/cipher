#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//////////////////////////////////////////////////////////////////////////
//strlen funtion
unsigned int checkStringLength(const char* s);
// Checking for the correct arguments to run the program correctly
void argumentsCheck(int argc);
//file connection checker 
void fileConnectionCheck(FILE* keyText_ptr);
// Storing first character key
int storingKeyChars(FILE* keyText_ptr);
// Storing first character plainText
int storingPlainTextChars(FILE* plainText_ptr);
//array size 512
void charSize512(char* plainText);
// createNewKey
void createNewKey(char cipherKey[], char* keyReady, char plainText[]);
//print vigenere key
void printVigenereKey(int keyLength, char cipherKey[]);
//print plain text
void printPlainText(int plainTextSize, char plainText[]);
//print cipher
void printCipherText(int plainTextSize, char* ciphTxt);
////////////////////////////////////////////////////////////////////////////

//main
int main(int argc, char* argv[])
{
    //variable declaration
    char cipherKey[1500];
    char plainText[1500];
    int i = 0;
    int j = 0;
    int keyTextFile;
    int plainTextFile;
    int plainTextSize;
    int keyLength;

    //function call for arguments checker
    argumentsCheck(argc);

    ////File i/o
    FILE* keyText_ptr;
    FILE* plainText_ptr;
    keyText_ptr = fopen(argv[1], "r");
    plainText_ptr = fopen(argv[2], "r");

    //function call for file connection checker
    fileConnectionCheck(keyText_ptr);
    //function call to storingKeyChars     
    keyTextFile = storingKeyChars(keyText_ptr);
    // function call to storingPlainTextChars
    plainTextFile = storingPlainTextChars(plainText_ptr);

    // Storing full correct key chars        
    do
    {
        if (isalpha(keyTextFile))
        {
            cipherKey[i] = tolower(keyTextFile);
            i++;
        }
        keyTextFile = getc(keyText_ptr);
    } while (keyTextFile != EOF);
    cipherKey[i] = '\0';

    // Storing full correct Plaintext chars
    i = 0;
    do
    {
        if (isalpha(plainTextFile))
        {
            plainText[i] = tolower(plainTextFile);
            i++;
        }
        plainTextFile = getc(plainText_ptr);
    } while (plainTextFile != EOF);
    plainText[i] = '\0';

    // function calling length check  |from correct plain text and key characters    
    keyLength = checkStringLength(cipherKey);
    plainTextSize = checkStringLength(plainText);
    //function call for char size
    charSize512(plainText);

    //memory allocation
    char* ciphTxt = calloc(sizeof(ciphTxt), plainTextSize);
    char* keyReady = calloc(sizeof(keyReady), plainTextSize);

    // function calling length check 
    plainTextSize = checkStringLength(plainText);

    //function call for creating new Key
    createNewKey(cipherKey, keyReady, plainText);

    // encrypting
    for (i = 0; i < plainTextSize; i++)
    {
        ciphTxt[i] = (((plainText[i] - 'a') + (keyReady[i] - 'a')) % 26 + 'a');
    }
    ciphTxt[i] = '\0';

    // Print Vigenere Key   
    printVigenereKey(keyLength, cipherKey);
    // Print Plaintext    
    printPlainText(plainTextSize, plainText);
    // Print Cipher Text
    printCipherText(plainTextSize, ciphTxt);

    free(ciphTxt);
    free(keyReady);
    fclose(plainText_ptr);
    fclose(keyText_ptr);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////

//checkStringLength function
unsigned int checkStringLength(const char* s)
{
    unsigned int count = 0;
    while (*s != '\0')
    {
        count++;
        s++;
    }
    return count;
}
// Checking for the correct arguments to run the program correctly
void argumentsCheck(int argc)
{
    if (argc != 3)
    {
        fprintf(stdout, "To run this program please use the c file + k#.txt + p#.txt\n");
        exit(0);
    }
}
//file connection checker 
void fileConnectionCheck(FILE* keyText_ptr)
{
    if (keyText_ptr == NULL)
    {
        fprintf(stdout, "Cannot connect to the specified files.");
        exit(0);
    }
}
// Storing first character key
int storingKeyChars(FILE* keyText_ptr)
{
    int keyTextFile = getc(keyText_ptr);
    return keyTextFile;
}
// Storing first character plainText
int storingPlainTextChars(FILE* plainText_ptr)
{
    int plainTextFile = getc(plainText_ptr);
    return plainTextFile;
}
//array size 512
void charSize512(char* plainText)
{
    int i = 0;
    int plainLength = checkStringLength(plainText);

    if (plainLength < 512)
    {
        for (i = plainLength; i < 512; i++)
        {
            plainText[i] = 'x';
        }
        plainText[i] = '\0';
    }
    plainText[512] = '\0';
}

//
 // creating new Key
void createNewKey(char cipherKey[], char* keyReady, char plainText[])
{
    int j = 0;
    int i = 0;
    int keyLength;
    keyLength = checkStringLength(cipherKey);

    int plainTextSize;
    plainTextSize = checkStringLength(plainText);

    for (i = 0, j = 0; i < plainTextSize; i++)
    {
        if (j == keyLength)
        {
            j = 0;
        }
        keyReady[i] = cipherKey[j];
        j++;
    }
}

// Print Vigenere Key
void printVigenereKey(int keyLength, char cipherKey[])
{
    printf("\n\nVigenere Key:\n");
    int i = 0;
    for (i = 0; i < keyLength; i++)
    {
        if (i % 80 == 0)
        {
            printf("\n");
        }
        printf("%c", cipherKey[i]);
    }
}
// Print Plaintext
void printPlainText(int plainTextSize, char plainText[])
{
    printf("\n\n\nPlaintext:\n");
    int i = 0;
    for (i = 0; i < plainTextSize; i++)
    {
        if (i % 80 == 0)
        {
            printf("\n");
        }
        printf("%c", plainText[i]);
    }
}
// Print Ciphertext
void printCipherText(int plainTextSize, char* ciphTxt)
{
    printf("\n\n\nCiphertext:\n\n");
    int i = 0;
    for (i = 0; i < plainTextSize;)
    {
        printf("%c", ciphTxt[i]);
        i++;
        if (i % 80 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}
