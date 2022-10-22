#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char caesarConvert(char input, int key) {
    int newPos;
    char currentChar = input;
    if (currentChar > 64 && currentChar < 91) {
        newPos = currentChar-64;
        newPos = ((newPos+key)%26)+64;

    } else if (currentChar > 96 && currentChar < 123) {
        newPos = currentChar - 96;
        newPos = ((newPos+key)%26)+96;

    } else if (currentChar > 32 && currentChar < 59){
        newPos = currentChar - 32;
        newPos = ((newPos+key)%26)+32;

    } else if (currentChar == 32) {
        newPos = 32;
    }

    return newPos;
    
}

char caesarRevert(char input, int key) {
    int newPos;
    char currentChar = input;
    if (currentChar > 64 && currentChar < 91) {
        newPos = currentChar-64;
        newPos = ((newPos-key)%26)+64;

    } else if (currentChar > 96 && currentChar < 123) {
        newPos = currentChar - 96;
        newPos = ((newPos-key)%26)+96;

    } else if (currentChar > 32 && currentChar < 59){
        newPos = currentChar - 32;
        newPos = ((newPos-key)%26)+32;

    } else if (currentChar == 32) {
        newPos = 32;
    }

    return newPos;
}


char caesarRevert(char input, int key) {
    int newPos;
    char currentChar = input;
    if (currentChar > 64 && currentChar < 91) {
        newPos = currentChar-64;
        newPos = ((newPos+key)%26)+64;

    } else if (currentChar > 96 && currentChar < 123) {
        newPos = currentChar - 96;
        newPos = ((newPos+key)%26)+96;

    } else if (currentChar > 32 && currentChar < 59){
        newPos = currentChar - 32;
        newPos = ((newPos-key)%26)+32;

    } else if (currentChar == 32) {
        newPos = 32;
    }

    return newPos;
}

char *augustus_encrypt(char *plain, char *key) {
    int plainLen = strlen(plain);
    int keyLen = strlen(key);
    int intKey = atoi(key);
    char *encrypted= malloc(sizeof(plain));
    
    /*
    Step one, Caesar Conversion
    Using ASCII Table Decimal Values
    */

    for (int i = 0; i<plainLen; i++) {
        char currentChar = plain[i];
        char newChar;

        newChar = caesarConvert(currentChar, intKey);
        encrypted[i] = newChar;
    }

    //Step two, Augustus conversion

    for (int i = 0; i<plainLen; i++) {
        char currentChar = encrypted[i];
        char newChar;
        int curKey = atoi(key[i%keyLen]);

        newChar = caesarConvert(currentChar, curKey);
        encrypted[i] = newChar;        
    }

    
}

char *augustus_decrypt(char *cipher, char *key) {
    int cipherLen = strlen(cipher);
    int keyLen = strlen(key);
    int intKey = atoi(key);
    char *decrypted= malloc(sizeof(cipher));

    for (int i = 0; i < cipherLen; i++) {
        char currentChar = decrypted;
        char newChar;
        int curKey = atoi(key[i%keyLen]);

        newChar = caesarRevert(currentChar, curKey);
        decrypted[i] = newChar;

    }

    for (int i = 0; i < cipherLen; i++) {
        char currentChar = decrypted;
        char newChar;

        newChar = caesarRevert(currentChar, intKey);
        decrypted[i] = newChar;
}