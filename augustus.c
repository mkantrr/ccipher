#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Method used in decryption
Takes the current position of the letter for decryption and increments it
backwards. If incrementing will cause a wrap around, resets back at 26 value, or 'z'
*/

int wrapAround(int start, int key) {
    int wrap;
    int diff = start-key;
    if (diff < 0) {
        while (diff < 0) {
            diff = abs(diff-key);
        }
        wrap = 26 - diff;
    } else {
        wrap = start-key;
    }
    return wrap;
}

/*
Method takes a char and converts it into its appropriate caesaer encrypted char.
Uses decimal value from ASCII table, values may need changing if 
table is ever altered.
*/

char caesarConvert(char input, int key) {
    int newPos;
    char currentChar = input;
    if (currentChar > 64 && currentChar < 91) {
        newPos = currentChar-65;
        newPos = ((newPos+key)%26)+65;

    } else if (currentChar > 96 && currentChar < 123) {
        newPos = currentChar - 97;
        newPos = ((newPos+key)%26)+97;

    } else if (currentChar > 32 && currentChar < 59){
        newPos = currentChar - 33;
        newPos = ((newPos+key)%26)+33;

    } else if (currentChar == 32) {
        newPos = 32;
    }


    return newPos;
    
}

/*
Method takes a char input and reverts it from its encrypted form back to the original
message. Calls wrapAround method to handle any case where the letter may need to start over
from 'z'. Based off of ASCII values, again may need altered if values change.
*/

char caesarRevert(char input, int key) {
    int newPos;
    char currentChar = input;
    if (currentChar > 64 && currentChar < 91) {
        newPos = currentChar-65;
        newPos = wrapAround(newPos, key);
        newPos = ((newPos)%26)+65;

    } else if (currentChar > 96 && currentChar < 123) {
        newPos = currentChar - 97;
        newPos = wrapAround(newPos, key);
        newPos = ((newPos)%26)+97;

    } else if (currentChar > 32 && currentChar < 59){
        newPos = currentChar - 33;
        newPos = wrapAround(newPos, key); 
        newPos = ((newPos)%26)+33;

    } else if (currentChar == 32) {
        newPos = 32;
    }

    return newPos;
}

/*
Method takes char array input, for both the unencrypted message, as well as key

Conversion broken down into 2 steps, once for initial conversion, again for the unique 
augustus conversion
*/

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
        //Used to determine place in key string, 48 comes from ASCII table
        char temp;
        temp = key[i%keyLen];
        int val = temp - 48;

        newChar = caesarConvert(currentChar, val);
        encrypted[i] = newChar;        
    }
    return encrypted;

    
}

/*
Method takes char array input, for both encrypted message and key

Reversion broken into 2 steps as well, first reversion for augustus, second for caesar conversion
*/

char *augustus_decrypt(char *cipher, char *key) {
    int cipherLen = strlen(cipher);
    int keyLen = strlen(key);
    int intKey = atoi(key);
    char *decrypted= malloc(sizeof(cipher));

    for (int i = 0; i < cipherLen; i++) {
        char currentChar = cipher[i];
        char newChar;
        
        //Same as for augustus_encrypt, used to determine which place you are at in key string
        char temp;
        temp = key[i%keyLen];
        int val = temp - 48;



        newChar = caesarRevert(currentChar, val);
        decrypted[i] = newChar;

    }

    for (int i = 0; i < cipherLen; i++) {
        char currentChar = decrypted[i];
        char newChar;

        newChar = caesarRevert(currentChar, intKey);
        decrypted[i] = newChar;
    }

    return decrypted;
}