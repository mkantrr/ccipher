#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *caesar_encrypt(char *plain, char *key){
    int len = strlen(plain);
    int keyint = atoi(key);
    char newplain[len];
    int  newkey = keyint/26;
    newkey = keyint - (26*newkey);
    for(int i=0;i<len;i++){
        char el = plain[i];
        int newelint = el+newkey;
        if(newelint > 122){
            newelint = newelint - 122;
            newelint = newelint + 96;
        }
        char newel = newelint;
        newplain[i] = newel;
    } 
    plain = newplain;
    return plain;
}
char *caesar_decrypt(char *cipher, char *key){
    int len = strlen(cipher);
    int keyint = atoi(key);
    char newcipher[len];
    int newkey = keyint/26;
    newkey = keyint - (26*newkey);
    for(int i=0;i<len;i++){
        char el = cipher[i];
        int newelint = el-newkey;
        if(newelint < 97){
            newelint = newelint - 96;
            newelint = newelint + 122;
        }
        char newel = newelint;
        newcipher[i] = newel;
    }
    cipher = newcipher;
    return cipher;
}