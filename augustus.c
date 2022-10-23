#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int wrapAround(int start, int key) {
    int wrap;
    if ((start-key) < 0) {
        wrap = 26 - abs(start-key);
    } else {
        wrap = start-key;
    }
    return wrap;
}

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
        char temp;
        temp = key[i%keyLen];
        int val = temp - 48;

        newChar = caesarConvert(currentChar, val);
        encrypted[i] = newChar;        
    }
    return encrypted;

    
}

char *augustus_decrypt(char *cipher, char *key) {
    int cipherLen = strlen(cipher);
    int keyLen = strlen(key);
    int intKey = atoi(key);
    char *decrypted= malloc(sizeof(cipher));

    for (int i = 0; i < cipherLen; i++) {
        char currentChar = cipher[i];
        char newChar;
        
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
